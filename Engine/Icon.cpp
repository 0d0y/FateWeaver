#include "pch.h"
#include "Icon.h"

McCol::Icon::Icon(std::wstring_view name)
    : UI(name)
{
    AddUITexture();
    AddUIText();
}

McCol::Icon::~Icon()
{
}

void McCol::Icon::Initialize()
{
    UI::Initialize();
}

void McCol::Icon::Update(const float& deltaTime)
{
    UI::Update(deltaTime);
}

void McCol::Icon::FixedUpdate(const float& deltaTime)
{
    UI::FixedUpdate(deltaTime);
}

void McCol::Icon::Render(McCol::D2DRender* renderer)
{
    UI::Render(renderer);
}

void McCol::Icon::HandleCollisionEnter(McCol::Collider* otherCollider)
{
    if (!m_IsInteractable)
        return;

    UI::HandleCollisionEnter(otherCollider);
}

void McCol::Icon::HandleCollisionStay(McCol::Collider* otherCollider)
{
    if (!m_IsInteractable)
        return;

    UI::HandleCollisionStay(otherCollider);
}

void McCol::Icon::HandleCollisionExit(McCol::Collider* otherCollider)
{
    if (!m_IsInteractable)
        return;

    UI::HandleCollisionExit(otherCollider);
}

void McCol::Icon::ReserveIconOnEvent(std::wstring_view evtID)
{
    m_IconOnEvents.push_back(evtID);
}

void McCol::Icon::ReserveIconOutEvent(std::wstring_view evtID)
{
    m_IconOutEvents.push_back(evtID);
}

void McCol::Icon::SetIconPanelOffset(const float& xOffset)
{
    m_IconPanelOffsetX = xOffset;
}

