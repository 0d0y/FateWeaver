#include "pch.h"
#include "Panel.h"

#include "EventSystem.h"
#include "InputSystem.h"

#include "../McDemo/Elements.h"

McCol::Panel::Panel(std::wstring_view name)
    : UI(name)
{
}

McCol::Panel::~Panel()
{
}

void McCol::Panel::Initialize()
{
    UI::Initialize();
}

void McCol::Panel::Update(const float& deltaTime)
{
    UI::Update(deltaTime);
}

void McCol::Panel::FixedUpdate(const float& deltaTime)
{
    UI::FixedUpdate(deltaTime);
}

void McCol::Panel::Render(McCol::D2DRender* renderer)
{
    UI::Render(renderer);
}

void McCol::Panel::HandleCollisionEnter(McCol::Collider* otherCollider)
{
    if (!m_IsInteractable)
        return;

    UI::HandleCollisionEnter(otherCollider);

    PanelInfo panelInfo = { this, m_PanelOffsetX, m_PanelOffsetY };

    for (auto& evtID : m_PanelOnEvents)
    {
        McCol::EventSystem::GetInstance()->PublishEvent(evtID, panelInfo);
    }
}

void McCol::Panel::HandleCollisionStay(McCol::Collider* otherCollider)
{
    if (!m_IsInteractable)
        return;

    UI::HandleCollisionStay(otherCollider);
}

void McCol::Panel::HandleCollisionExit(McCol::Collider* otherCollider)
{
    if (!m_IsInteractable)
        return;

    UI::HandleCollisionExit(otherCollider);

    for (auto& evtID : m_PanelOutEvents)
    {
        McCol::EventSystem::GetInstance()->PublishEvent(evtID, this);
    }
}

void McCol::Panel::ReservePanelOnEvent(std::wstring_view evtID)
{
    m_PanelOnEvents.push_back(evtID);
}

void McCol::Panel::ReservePanelOutEvent(std::wstring_view evtID)
{
    m_PanelOutEvents.push_back(evtID);
}

void McCol::Panel::SetPanelOffset(const float& xOffset, const float& yOffset)
{
    m_PanelOffsetX = xOffset;
    m_PanelOffsetY = yOffset;
}
