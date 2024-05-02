#include "pch.h"
#include "CrackButton.h"

#include "InputSystem.h"
#include "../McDemo/GameManager.h"

McCol::CrackButton::CrackButton(std::wstring_view name, int stageIndex)
    : MapButton(name)
{
    m_IconType = MapIconType::Tbreak;
    m_StageIndex = stageIndex;

    AddUITexture();
    LoadUITexture(L"../Resource/icon/UI_Map_Tbreak.png", L"UI_Map_Tbreak");
}

McCol::CrackButton::~CrackButton()
{
}

void McCol::CrackButton::Initialize()
{
    MapButton::Initialize();
}

void McCol::CrackButton::Update(const float& deltaTime)
{
    MapButton::Update(deltaTime);
}

void McCol::CrackButton::FixedUpdate(const float& deltaTime)
{
    MapButton::FixedUpdate(deltaTime);
}

void McCol::CrackButton::Render(McCol::D2DRender* renderer)
{
    MapButton::Render(renderer);
}

void McCol::CrackButton::HandleCollisionEnter(McCol::Collider* otherCollider)
{
    if (!m_IsInteractable)
        return;

    MapButton::HandleCollisionEnter(otherCollider);
}

void McCol::CrackButton::HandleCollisionStay(McCol::Collider* otherCollider)
{
    if (!m_IsInteractable)
        return;

    MapButton::HandleCollisionStay(otherCollider);

    if (InputSystem::GetInstance()->IsKeyDown(VK_LBUTTON))
    {
        DEBUGPRINT("Crack Button On\n");

        EventSystem::GetInstance()->PublishEvent(L"Crack Button Down");
        GameManager::GetInstance()->SetMapIndex(m_StageIndex);
    }
}

void McCol::CrackButton::HandleCollisionExit(McCol::Collider* otherCollider)
{
    if (!m_IsInteractable)
        return;

    MapButton::HandleCollisionExit(otherCollider);
}
