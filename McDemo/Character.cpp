#include "Character.h"

// Component
#include "../Engine/Animation.h"
#include "../Engine/Transform.h"
#include "../Engine/SoundSystem.h"
#include "StateManager.h"
#include "StateIconManager.h"
#include "HpRenderer.h"

using namespace McCol;

Character::Character(std::wstring_view name, CharacterIndex battleIndex, CharacterType type)
	: GameObject(name, Layer::CHARACTER)
	, m_MaxHealth(0)
	, m_Health(0)
	, m_Defense(0)
	, m_BattleIndex(battleIndex)
	, m_Type(type)
	, m_IsAlive(true)
{
	AddComponent<Transform>();
	AddComponent<StateManager>();
	AddComponent<Animation>();
	m_StateIconManager = new StateIconManager;
	m_HpRenderer = AddComponent<HpRenderer>();

	EventSystem::GetInstance()->Subscribe(L"TURN_START", MakeListenerInfo(&Character::StartTurn));
}

Character::~Character()
{
	delete m_StateIconManager;
}

void Character::Initialize()
{
	GameObject::Initialize();
	auto trans = GetComponent<Transform>();
	m_StateIconManager->Initialize(trans->GetPosition().x - 100, trans->GetPosition().y - 200);
}

void Character::FixedUpdate(const float& deltaTime)
{
	GameObject::FixedUpdate(deltaTime);

	ApplyDelayedDamage(deltaTime);
}

void Character::ApplyOwnerState(CardInfo& info)
{
	GetComponent<StateManager>()->SendCard(info);
}

void Character::SetMaxHealth(int maxHealth)
{
	m_MaxHealth = maxHealth;
	m_HpRenderer->ModifyHpBar(m_MaxHealth, m_Health, 0);
}

void Character::SetCurrentHealth(int curHealth)
{
	m_Health = curHealth;
	m_HpRenderer->ModifyHpBar(m_MaxHealth, m_Health, 0);
}

void Character::Heal(int heal)
{
	m_Health += heal;

	if (m_Health > m_MaxHealth)
		m_Health = m_MaxHealth;

	m_HpRenderer->ModifyHpBar(m_MaxHealth, m_Health, 0);
}

//void Character::ReceiveCard(CardInfo info)
//{
//	GetComponent<StateManager>()->ReceiveCard(info);
//
//	// 방어력 얻기
//	if (info.Attributes[SIZE(Attribute::DEFENSE)])
//	{
//		m_Defense += info.Attributes[SIZE(Attribute::DEFENSE)];
//		// todo : 방어력이 쌓이는 이펙트 추가
//	}
//
//	// 데미지 받기
//	for (int i = 0; i < info.Attributes[SIZE(Attribute::ATTACK_COUNT)]; i++)
//	{
//		int damage = info.Attributes[SIZE(Attribute::DAMAGE)];
//		ApplyDefense(damage);
//		// todo : 공격 받는 이펙트 추가
//	}
//
//	if (info.Attributes[SIZE(Attribute::ATTACK_COUNT)] == 0 || info.Attributes[SIZE(Attribute::DAMAGE)] > 0)
//	{
//		int damage = info.Attributes[SIZE(Attribute::DAMAGE)];
//		ApplyDefense(damage);
//	}
//}

int Character::GetHealth()
{
	return m_Health;
}

int Character::GetMaxHealth()
{
	return m_MaxHealth;
}

void Character::SetDefense(int def)
{
	if (!m_IsAlive)
		return;

	m_Defense = def;
	m_StateIconManager->ModifyState(State::DEFENSE, m_Defense);
}

void Character::QueuedDamage(CardInfo& info)
{
	if (!m_IsAlive)
		return;

	// 데미지큐에 넣기
	for (int i = 0; i < info.Attributes[SIZE(Attribute::ATTACK_COUNT)]; i++)
	{
		int damage = info.Attributes[SIZE(Attribute::DAMAGE)];
		m_DamagedQueue.push(damage);
	}

	// 공격횟수가 0 이지만 데미지가 있는 경우 예외 처리
	if (info.Attributes[SIZE(Attribute::ATTACK_COUNT)] == 0 || info.Attributes[SIZE(Attribute::DAMAGE)] > 0)
	{
		int damage = info.Attributes[SIZE(Attribute::DAMAGE)];
		m_DamagedQueue.push(damage);
	}
}

void Character::ApplyDelayedDamage(const float& deltaTime)
{
	// 저장된 데미지를 상태이상을 고려하여 적용한다
	// 변화된 데미지를 일정 시간마다 하나씩 빼면서 실제 수치에 적용한다
	// 변화된 상태에 따라 이벤트를 발행한다(체력, 상태이상 정보 등)

	m_ProgressTime += deltaTime;

	while (!m_DamagedQueue.empty())
	{
		if (m_ProgressTime < m_DelayedTime)
			return;

		m_ProgressTime -= m_DelayedTime;

		int damage = m_DamagedQueue.front();
		m_DamagedQueue.pop();
		GetComponent<StateManager>()->ApplyQuickState(damage);
		ApplyDefense(damage);

		if (damage > 0)
		{
			// effect
			EffectInfo info;
			info.Type = EffectType::SLASH_1;
			info.X = GetComponent<Transform>()->GetPosition().x; //TODO: 덱 아이콘 좌표로 수정
			info.Y = GetComponent<Transform>()->GetPosition().y;
			info.Value = damage;
			EventSystem::GetInstance()->PublishEvent(L"EFFECT", info);

			// sound
			SoundSystem::GetInstance()->Replay("Hit_Slash");
			SoundSystem::GetInstance()->SetVolume("HIT", 0.5f);

			m_Health -= damage;
			m_HpRenderer->ModifyHpBar(m_MaxHealth, m_Health, 0);

			if (m_Health <= 0 && m_IsAlive)
			{
				EventSystem::GetInstance()->PublishEvent(L"B_CHARACTER_DEATH", m_BattleIndex);
				SoundSystem::GetInstance()->Replay("Hit_Gun_01");
				m_StateIconManager->OffRender();
				SetAble(false);
				m_IsAlive = false;
			}
		}
	}
}

void Character::ApplyCardInfo(CardInfo& info)
{
	if (!m_IsAlive)
		return;

	// 카드 정보에 저장된 상태이상, 방어도 등을 적용시킴

	GetComponent<StateManager>()->TakeState(info);

	if (info.Attributes[SIZE(Attribute::DEFENSE)])
	{
		// 빈틈 포착 예외처리
		if(info.Attributes[SIZE(Attribute::DRAW_NUMBER)] == -9999)
		{
			SetDefense(0);
		}

		m_Defense += info.Attributes[SIZE(Attribute::DEFENSE)];
		m_StateIconManager->ModifyState(State::DEFENSE, m_Defense);

		// effect
		EffectInfo info;
		info.Type = EffectType::방어도아이콘;
		info.X = GetComponent<Transform>()->GetPosition().x;
		info.Y = GetComponent<Transform>()->GetPosition().y;
		EventSystem::GetInstance()->PublishEvent(L"EFFECT", info);

		// sound
		SoundSystem::GetInstance()->Replay("FX_Shield");
	}
}

CharacterIndex Character::GetBattleIndex()
{
	return m_BattleIndex;
}

CharacterType Character::GetType()
{
	return m_Type;
}

StateIconManager* Character::GetIconManager()
{
	return m_StateIconManager;
}

void Character::ApplyDefense(int& damage)
{
	if (m_Defense > 0)
	{
		m_Defense -= damage;

		if (m_Defense > 0)
		{
			damage = 0;
			m_StateIconManager->ModifyState(State::DEFENSE, m_Defense);
			// todo : 방어 막기 사운드 추가
		}
		else
		{
			damage = -m_Defense;
			m_Defense = 0;
			m_StateIconManager->ModifyState(State::DEFENSE, 0);
		}
	}
}

void Character::StartTurn(std::any param)
{
	SetDefense(0);
}
