#include "Fanatic.h"

#include "HpRenderer.h"
#include "StateManager.h"
#include "../Engine/Animation.h"
#include "../Engine/TextRenderer.h"
#include "../Engine/Transform.h"
#include "StateIconManager.h"

using namespace McCol;

int Fanatic::m_ImpendingCount = 0;
int Fanatic::m_WillCount = 0;

Fanatic::Fanatic(CharacterIndex battleIndex)
	: Character(L"Fanatic", battleIndex, CharacterType::FANATIC)
{
	auto anim = GetComponent<Animation>();
	anim->Load(L"../Resource/sprite/Cult_Idle_1.png", L"Fanatic");

	AnimationState idle;
	idle.IsLoop = true;

	idle.Clips.emplace_back(560 * 0, 560 * 0, 560 * 1, 560 * 1, FRAME(6));
	idle.Clips.emplace_back(560 * 1, 560 * 0, 560 * 2, 560 * 1, FRAME(6));
	idle.Clips.emplace_back(560 * 2, 560 * 0, 560 * 3, 560 * 1, FRAME(6));
	idle.Clips.emplace_back(560 * 3, 560 * 0, 560 * 4, 560 * 1, FRAME(6));
	idle.Clips.emplace_back(560 * 4, 560 * 0, 560 * 5, 560 * 1, FRAME(6));

	anim->AddAnimState(L"Fanatic Idle", idle);
	anim->SetAnimState(L"Fanatic Idle");
	anim->SetAnimScale(0.5f);

	GetComponent<StateManager>()->SetState(State::IMPENDING_RUIN, m_ImpendingCount);
	GetComponent<StateManager>()->SetState(State::WILL_OF_RUIN, m_WillCount);

	m_MaxHealth = 45;
	m_Health = 45;
	m_MaxHealth += m_WillCount * 10;
	m_Health += m_WillCount * 10;

	m_HpRenderer->LoadTexture(HpType::MIDDLE);
	m_HpRenderer->ModifyHpBar(m_MaxHealth, m_Health, 0);
	m_HpRenderer->SetOffset(-130, 160);
	m_HpRenderer->GetHpText()->SetOffset(-7, 152);
}

void Fanatic::Initialize()
{
	Character::Initialize();
	auto trans = GetComponent<Transform>();
	m_StateIconManager->Initialize(trans->GetPosition().x - 110, trans->GetPosition().y - 180);
}

void Fanatic::GetImpending(int count)
{
	m_ImpendingCount += count;
}

void Fanatic::GetWill(int count)
{
	m_WillCount += count;
	m_MaxHealth += 10;
	m_Health += 10;
	m_HpRenderer->ModifyHpBar(m_MaxHealth, m_Health, 0);
}
