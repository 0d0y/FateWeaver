#include "Stalker.h"

#include "HpRenderer.h"
#include "../Engine/Animation.h"
#include "../Engine/TextRenderer.h"
#include "../Engine/Transform.h"
#include "StateIconManager.h"

using namespace McCol;

Stalker::Stalker(CharacterIndex battleIndex)
	: Character(L"Stalker", battleIndex, CharacterType::STALKER)
{
	auto anim = GetComponent<Animation>();
	anim->Load(L"../Resource/sprite/Chaser_Idle.png", L"Stalker");

	AnimationState idle;
	idle.IsLoop = true;

	idle.Clips.emplace_back(200 * 0, 570 * 0, 200 * 1, 570 * 1, FRAME(7));
	idle.Clips.emplace_back(200 * 1, 570 * 0, 200 * 2, 570 * 1, FRAME(7));
	idle.Clips.emplace_back(200 * 2, 570 * 0, 200 * 3, 570 * 1, FRAME(8));
	idle.Clips.emplace_back(200 * 3, 570 * 0, 200 * 4, 570 * 1, FRAME(8));

	anim->AddAnimState(L"Stalker Idle", idle);
	anim->SetAnimState(L"Stalker Idle");
	anim->SetAnimScale(0.5f);

	m_HpRenderer->LoadTexture(HpType::MIDDLE);
	m_MaxHealth = 60;
	m_Health = 60;
	m_HpRenderer->ModifyHpBar(m_MaxHealth, m_Health, 0);
	m_HpRenderer->SetOffset(-120, 160);
	m_HpRenderer->GetHpText()->SetOffset(0, 152);
}

void Stalker::Initialize()
{
	Character::Initialize();
	auto trans = GetComponent<Transform>();
	m_StateIconManager->Initialize(trans->GetPosition().x - 100, trans->GetPosition().y - 180);
}
