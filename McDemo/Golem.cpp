#include "Golem.h"

#include "HpRenderer.h"
#include "StateIconManager.h"
#include "StateManager.h"

#include "../Engine/Transform.h"
#include "../Engine/Animation.h"
#include "../Engine/TextRenderer.h"

using namespace McCol;

int Golem::m_GolemImpending = 0;

Golem::Golem(CharacterIndex battleIndex)
: Character(L"Golem", battleIndex, CharacterType::GOLEM)
{
	auto anim = GetComponent<Animation>();
	anim->Load(L"../Resource/sprite/GD_Idle_1.png", L"Golem");

	AnimationState idle;
	idle.IsLoop = true;

	idle.Clips.emplace_back(1000 * 0, 1000 * 0, 1000 * 1, 1000 * 1, FRAME(6));
	idle.Clips.emplace_back(1000 * 1, 1000 * 0, 1000 * 2, 1000 * 1, FRAME(6));
	idle.Clips.emplace_back(1000 * 2, 1000 * 0, 1000 * 3, 1000 * 1, FRAME(6));
	idle.Clips.emplace_back(1000 * 3, 1000 * 0, 1000 * 4, 1000 * 1, FRAME(6));
	idle.Clips.emplace_back(1000 * 4, 1000 * 0, 1000 * 5, 1000 * 1, FRAME(6));

	anim->AddAnimState(L"Golem Idle", idle);
	anim->SetAnimState(L"Golem Idle");
	anim->SetAnimScale(0.5f);

	GetComponent<StateManager>()->SetState(State::IMPENDING_RUIN, m_GolemImpending);

	m_HpRenderer->LoadTexture(HpType::LONG);
	m_MaxHealth = 280;
	m_Health = 280;
	m_HpRenderer->ModifyHpBar(m_MaxHealth, m_Health, 0);
	m_HpRenderer->SetOffset(-250, 260);
	m_HpRenderer->GetHpText()->SetOffset(-60, 252);
}

void Golem::Initialize()
{
	Character::Initialize();
	auto trans = GetComponent<Transform>();
	m_StateIconManager->Initialize(trans->GetPosition().x - 230, trans->GetPosition().y - 280);
}

void Golem::GetWill(int count)
{
	m_GolemImpending += 2;
}
