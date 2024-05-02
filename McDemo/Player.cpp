#include "Player.h"

#include "HpRenderer.h"
#include "../Engine/Animation.h"
#include "../Engine/Transform.h"
#include "GameManager.h"
#include "../Engine/TextRenderer.h"
#include "StateIconManager.h"

using namespace McCol;

Player::Player(CharacterIndex battleIndex)
	: Character(L"Player", battleIndex, CharacterType::PLAYER)
{
    std::vector<AnimationClip> IdleClips;
    IdleClips.emplace_back( 490.f * 0, 590.f * 0, 490.f * 1, 590.f * 1, FRAME(5) );
    IdleClips.emplace_back( 490.f * 1, 590.f * 0, 490.f * 2, 590.f * 1, FRAME(5) );
    IdleClips.emplace_back( 490.f * 2, 590.f * 0, 490.f * 3, 590.f * 1, FRAME(5) );
    IdleClips.emplace_back( 490.f * 3, 590.f * 0, 490.f * 4, 590.f * 1, FRAME(5) );
    IdleClips.emplace_back( 490.f * 4, 590.f * 0, 490.f * 5, 590.f * 1, FRAME(5) );
    IdleClips.emplace_back( 490.f * 5, 590.f * 0, 490.f * 6, 590.f * 1, FRAME(5) );

    const auto anim = GetComponent<Animation>();
    anim->Load(L"../Resource/FW1_Idle.png", L"Player Sprite");
    anim->AddAnimState(L"Player Idle", IdleClips);
    anim->SetAnimState(L"Player Idle");
    anim->SetAnimScale(0.5f);

    m_HpRenderer->LoadTexture(HpType::MIDDLE);
    m_MaxHealth = GameManager::GetInstance()->GetMaxHealth();
    m_Health = GameManager::GetInstance()->GetCurHealth();
    m_HpRenderer->ModifyHpBar(m_MaxHealth, m_Health, 0);
    m_HpRenderer->SetOffset(-150, 170);
    m_HpRenderer->GetHpText()->SetOffset(-29, 162);


    McCol::EventSystem::GetInstance()->Subscribe(L"UI_LOWER_END_TURN_DOWN", MakeListenerInfo(&Player::EndTurn));
}

Player::~Player()
{
}

void Player::Initialize()
{
	Character::Initialize();
    auto trans = GetComponent<Transform>();
    m_StateIconManager->Initialize(trans->GetPosition().x - 125, trans->GetPosition().y - 190);
}

void Player::SetFateEnergy(int number)
{
    m_FateEnergy = number;
}

int Player::GetFateEnergy()
{
    return m_FateEnergy;
}

void Player::EndTurn(std::any param)
{
    m_FateEnergy = 3;
}
