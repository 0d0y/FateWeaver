#include "pch.h"
#include "RandomButton.h"

#include "InputSystem.h"
#include "../McDemo/GameManager.h"

McCol::RandomButton::RandomButton(std::wstring_view name, int stageIndex)
    : MapButton(name)
{
    m_IconType = MapIconType::Secret;
    m_StageIndex = stageIndex;

    AddUITexture();
    LoadUITexture(L"../Resource/icon/UI_Map_Secret.png", L"UI_Map_Secret");
}

McCol::RandomButton::~RandomButton()
{
}

void McCol::RandomButton::Initialize()
{
    MapButton::Initialize();
}

void McCol::RandomButton::Update(const float& deltaTime)
{
    MapButton::Update(deltaTime);
}

void McCol::RandomButton::FixedUpdate(const float& deltaTime)
{
    MapButton::FixedUpdate(deltaTime);
}

void McCol::RandomButton::Render(McCol::D2DRender* renderer)
{
    MapButton::Render(renderer);
}

void McCol::RandomButton::HandleCollisionEnter(McCol::Collider* otherCollider)
{
    if (!m_IsInteractable)
        return;

    MapButton::HandleCollisionEnter(otherCollider);
}

void McCol::RandomButton::HandleCollisionStay(McCol::Collider* otherCollider)
{
    if (!m_IsInteractable)
        return;

    MapButton::HandleCollisionStay(otherCollider);

    if (InputSystem::GetInstance()->IsKeyDown(VK_LBUTTON))
    {
        DEBUGPRINT("·£´ý ¸Ê ¹öÆ° ´­¸²\n");

        EventSystem::GetInstance()->PublishEvent(L"Random Button Down");
        GameManager::GetInstance()->SetMapIndex(m_StageIndex);
    }
}

void McCol::RandomButton::HandleCollisionExit(McCol::Collider* otherCollider)
{
    if (!m_IsInteractable)
        return;

    MapButton::HandleCollisionExit(otherCollider);
}
