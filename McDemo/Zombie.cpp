#include "Zombie.h"

#include "HpRenderer.h"
#include "../Engine/Animation.h"
#include "../Engine/TextRenderer.h"

using namespace McCol;

Zombie::Zombie(CharacterIndex battleIndex)
	: Character(L"Zombie", battleIndex, CharacterType::ZOMBIE)
{
	auto anim = GetComponent<Animation>();
	anim->Load(L"../Resource/sprite/Zombie_Idle_1.png", L"Zombie");

	AnimationState idle;
	idle.IsLoop = true;

	idle.Clips.emplace_back(600 * 0, 525 * 0, 600 * 1, 525 * 1, FRAME(6));
	idle.Clips.emplace_back(600 * 1, 525 * 0, 600 * 2, 525 * 1, FRAME(6));
	idle.Clips.emplace_back(600 * 2, 525 * 0, 600 * 3, 525 * 1, FRAME(6));
	idle.Clips.emplace_back(600 * 3, 525 * 0, 600 * 4, 525 * 1, FRAME(6));
	idle.Clips.emplace_back(600 * 4, 525 * 0, 600 * 5, 525 * 1, FRAME(6));

	anim->AddAnimState(L"Zombie Idle", idle);
	anim->SetAnimState(L"Zombie Idle");
	anim->SetAnimScale(0.5f);

	m_HpRenderer->LoadTexture(HpType::SHORT);
	m_MaxHealth = 18;
	m_Health = 18;
	m_HpRenderer->ModifyHpBar(m_MaxHealth, m_Health, 0);
	m_HpRenderer->SetOffset(-95, 150);
	m_HpRenderer->GetHpText()->SetOffset(-26, 142);
}
