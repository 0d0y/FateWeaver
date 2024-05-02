#include "pch.h"
#include "BattleButton.h"

#include "EventSystem.h"
#include "InputSystem.h"

#include "Transform.h"

#include "../McDemo/Elements.h"
#include "../McDemo/GameManager.h"

McCol::BattleButton::BattleButton(std::wstring_view name, BattleIconType type, BattleStageType stageType, int stageIndex)
    : MapButton(name)
{
    m_StageType = stageType;
    m_StageIndex = stageIndex;

    switch(type)
    {
    case BattleIconType::Monster:
    {
        m_IconType = MapIconType::Monster;
        break;
    }
    case BattleIconType::Elite:
    {
        m_IconType = MapIconType::Elite;
        break;
    }
    case BattleIconType::Boss:
    {
        m_IconType = MapIconType::Boss;
        break;
    }
    }

    AddUITexture();

    if (type == BattleIconType::Monster)
    {
        LoadUITexture(L"../Resource/icon/UI_Map_Monster.png", L"UI_Map_Monster");
    }
    else if (type == BattleIconType::Elite)
    {
        LoadUITexture(L"../Resource/icon/UI_Map_Elite.png", L"UI_Map_Elite");
    }
    else if (type == BattleIconType::Boss)
    {
        LoadUITexture(L"../Resource/icon/UI_Map_Boss01.png", L"UI_Map_Boss01");
    }

}

McCol::BattleButton::~BattleButton()
{
}

void McCol::BattleButton::Initialize()
{
    MapButton::Initialize();
}

void McCol::BattleButton::Update(const float& deltaTime)
{
    MapButton::Update(deltaTime);
}

void McCol::BattleButton::FixedUpdate(const float& deltaTime)
{
    MapButton::FixedUpdate(deltaTime);
}

void McCol::BattleButton::Render(McCol::D2DRender* renderer)
{
    MapButton::Render(renderer);
}

void McCol::BattleButton::HandleCollisionEnter(McCol::Collider* otherCollider)
{
    if (!m_IsInteractable)
        return;

    MapButton::HandleCollisionEnter(otherCollider);
}

void McCol::BattleButton::HandleCollisionStay(McCol::Collider* otherCollider)
{
    if (!m_IsInteractable)
        return;

    MapButton::HandleCollisionStay(otherCollider);

    if (InputSystem::GetInstance()->IsKeyDown(VK_LBUTTON))
    {
        DEBUGPRINT("%f, %f\n", GetComponent<Transform>()->GetPosition().x, GetComponent<Transform>()->GetPosition().y);

        EventSystem::GetInstance()->PublishEvent(L"Battle Button Down", m_StageType);
        GameManager::GetInstance()->SetMapIndex(m_StageIndex);
    }
}

void McCol::BattleButton::HandleCollisionExit(McCol::Collider* otherCollider)
{
    if (!m_IsInteractable)
        return;

    MapButton::HandleCollisionExit(otherCollider);
}
