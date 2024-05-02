#include "StateManager.h"

#include "../Engine/Transform.h"

#include "Character.h"
#include "Fanatic.h"
#include "Golem.h"
#include "StateIconManager.h"

#include "../Engine/EventSystem.h"
#include "../Engine/SoundSystem.h"

using namespace McCol;

StateManager::StateManager(McCol::GameObject* owner)
	: Component(owner)
	, m_CharacterStates{}
{
}

StateManager::~StateManager()
{
}

void StateManager::Initialize()
{
	for (auto& state : m_CharacterStates)
		state = 0;

	McCol::EventSystem::GetInstance()->Subscribe(L"UI_LOWER_END_TURN_DOWN", MakeListenerInfo(&StateManager::EndTurn));
}

void StateManager::Render(McCol::D2DRender* renderer)
{

}

void StateManager::SendCard(CardInfo& info)
{
	if (m_CharacterStates[SIZE(State::ENCHANTMENT)])
	{
		info.Attributes[SIZE(Attribute::DAMAGE)] += 3;
	}
	if (m_CharacterStates[SIZE(State::IMPENDING_RUIN)])
	{
		info.Attributes[SIZE(Attribute::DAMAGE)] += 2;
	}
	if (m_CharacterStates[SIZE(State::CONFUSION)])
	{
		info.Attributes[SIZE(Attribute::DAMAGE)]
			= static_cast<int>(ceil(static_cast<float>
				(info.Attributes[SIZE(Attribute::DAMAGE)]) * 0.7f));
	}

	// 파멸의 예언 : 카드 데미지 +2 다음 전투 때의 광신도 카드도 강화를 받은 상태
	// 파멸의 의지 : 자신 체력 +10  다음 전투 때의 광신도가 강화를 받은 상태
	// 엔진과부하 : 카드 데미지 +2 버프 영구 제공(파멸의 예언의 보스 버전)
}

//void StateManager::ReceiveCard(CardInfo& info)
//{
//	if (info.States[SIZE(State::QUICK)])
//	{
//		if (info.Attributes[SIZE(Attribute::DAMAGE)] > 0)
//		{
//			info.Attributes[SIZE(Attribute::DAMAGE)] -= 3;
//
//			if (info.Attributes[SIZE(Attribute::DAMAGE)] < 0)
//				info.Attributes[SIZE(Attribute::DAMAGE)] = 0;
//
//			m_CharacterStates[SIZE(State::QUICK)]--;
//		}
//	}
//
//	if (info.States[SIZE(State::STUNNED)])
//	{
//		// todo : 기절 이벤트
//	}
//
//	if (info.States[SIZE(State::DISRUPTION)])
//	{
//		// todo : 흐트러짐 이벤트
//	}
//
//	AddState(info);
//}

bool StateManager::IsState(State state)
{
	if (m_CharacterStates[SIZE(state)])
		return true;

	return false;
}

void StateManager::SetState(State state, int count)
{
	m_CharacterStates[SIZE(state)] = count;
}

void StateManager::TakeState(CardInfo& info)
{
	AddState(info);
}

void StateManager::ApplyQuickState(int& damage)
{
	if (m_CharacterStates[SIZE(State::QUICK)])
	{
		if (damage > 0)
		{
			damage -= 3;

			if (m_CharacterStates[SIZE(Attribute::DAMAGE)] < 0)
				damage = 0;

			m_CharacterStates[SIZE(State::QUICK)]--;
			dynamic_cast<Character*>(m_Owner)->GetIconManager()->ModifyState(State::QUICK, m_CharacterStates[SIZE(State::QUICK)]);
			// todo : 재빠름 감소 이펙트
		}
	}
}

void StateManager::AddState(const CardInfo& info)
{
	for (size_t i = 0; i < SIZE(State::END); i++)
	{

		State curState = State::NONE;

		if (info.States[i] > 0)
			curState = static_cast<State>(i);
		else
			continue;

		EffectInfo effInfo;
		effInfo.Type = EffectType::END;

		switch (curState)
		{
		case State::QUICK:
		{
			effInfo.Type = EffectType::재빠름시작;
			SoundSystem::GetInstance()->Replay("FX_Buff");
			break;
		}
		case State::CONFUSION:
		{
			effInfo.Type = EffectType::혼란시작;
			SoundSystem::GetInstance()->Replay("FX_CC");
			break;
		}
		case State::DISRUPTION:
		{
			effInfo.Type = EffectType::흐트러짐시작;
			SoundSystem::GetInstance()->Replay("FX_CC");
			break;
		}
		case State::ENCHANTMENT:
		{
			effInfo.Type = EffectType::마력충전시작;
			SoundSystem::GetInstance()->Replay("FX_Buff");
			break;
		}
		case State::IMPENDING_RUIN:
		{
			auto character = dynamic_cast<Fanatic*>(m_Owner);
			if (character == nullptr)
				continue;

			character->GetImpending(info.States[i]);
			SoundSystem::GetInstance()->Replay("FX_Buff");
			effInfo.Type = EffectType::파멸의예언시작;
			break;
		}
		case State::WILL_OF_RUIN:
		{
			auto character = dynamic_cast<Fanatic*>(m_Owner);
			if (character == nullptr)
				continue;

			character->GetWill(info.States[i]);
			SoundSystem::GetInstance()->Replay("FX_Buff");
			effInfo.Type = EffectType::파멸의의지시작;
			break;
		}
		case State::ENGINE_OVERLOAD:
		{
			auto character = dynamic_cast<Golem*>(m_Owner);
			if (character == nullptr)
				continue;

			character->GetWill(info.States[i]);
			SoundSystem::GetInstance()->Replay("FX_Buff");
			effInfo.Type = EffectType::엔진과부하시작;
			break;
		}
		}

		// 이펙트 출력 이벤트
		if (effInfo.Type != EffectType::END)
		{
			effInfo.X = GetComponent<Transform>()->GetPosition().x;
			effInfo.Y = GetComponent<Transform>()->GetPosition().y + 50;
			EventSystem::GetInstance()->PublishEvent(L"EFFECT", effInfo);
		}

		if (curState == State::ENGINE_OVERLOAD)
			curState = State::IMPENDING_RUIN;

		m_CharacterStates[i] += info.States[i];
		dynamic_cast<Character*>(m_Owner)->GetIconManager()->ModifyState(curState, m_CharacterStates[i]);
	}
}

void StateManager::EndTurn(std::any publisher)
{
	for (size_t i = 0; i < SIZE(State::END); i++)
	{
		if (m_CharacterStates[i] <= 0)
			continue;

		if (i == SIZE(State::QUICK))
			continue;

		if (i == SIZE(State::IMPENDING_RUIN))
			continue;

		if (i == SIZE(State::WILL_OF_RUIN))
			continue;

		if (i == SIZE(State::ENGINE_OVERLOAD))
			continue;

		if (i == SIZE(State::DEFENSE))
			continue;
		

		m_CharacterStates[i]--;
		dynamic_cast<Character*>(m_Owner)->GetIconManager()->ModifyState(static_cast<State>(i), m_CharacterStates[i]);
	}
}
