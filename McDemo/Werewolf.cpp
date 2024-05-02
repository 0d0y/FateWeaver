#include "Werewolf.h"

#include "HpRenderer.h"
#include "../Engine/Animation.h"
#include "../Engine/TextRenderer.h"

#include "../Engine/Transform.h"
#include "StateIconManager.h"

using namespace McCol;

Werewolf::Werewolf(CharacterIndex battleIndex)
	: Character(L"Werewolf", battleIndex, CharacterType::WEREWOLF)
{
	auto anim = GetComponent<Animation>();
	anim->Load(L"../Resource/sprite/Wolf_Idle_1.png", L"Werewolf");

	AnimationState idle;
	idle.IsLoop = true;

	idle.Clips.emplace_back(700 * 0, 700 * 0, 700 * 1, 700 * 1, FRAME(6));
	idle.Clips.emplace_back(700 * 1, 700 * 0, 700 * 2, 700 * 1, FRAME(6));
	idle.Clips.emplace_back(700 * 2, 700 * 0, 700 * 3, 700 * 1, FRAME(6));
	idle.Clips.emplace_back(700 * 3, 700 * 0, 700 * 4, 700 * 1, FRAME(6));
	idle.Clips.emplace_back(700 * 4, 700 * 0, 700 * 5, 700 * 1, FRAME(6));

	anim->AddAnimState(L"Werewolf Idle", idle);
	anim->SetAnimState(L"Werewolf Idle");
	anim->SetAnimScale(0.5f);

	m_HpRenderer->LoadTexture(HpType::MIDDLE);
	m_MaxHealth = 38;
	m_Health = 38;
	m_HpRenderer->ModifyHpBar(m_MaxHealth, m_Health, 0);
	m_HpRenderer->SetOffset(-150, 190);
	m_HpRenderer->GetHpText()->SetOffset(-30, 182);
}

void Werewolf::Initialize()
{
	Character::Initialize();
	auto trans = GetComponent<Transform>();
	m_StateIconManager->Initialize(trans->GetPosition().x - 130, trans->GetPosition().y - 205);
}
