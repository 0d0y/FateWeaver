#include "pch.h"
#include "Button.h"

#include "EventSystem.h"
#include "InputSystem.h"

#include "Transform.h"

McCol::Button::Button(std::wstring_view name)
    : UI(name)
    //, m_IsInteractive(true)
{
}

McCol::Button::~Button()
{
    m_ButtonOnEvents.clear();
    m_ButtonClickEvents.clear();
    m_ButtonOutEvents.clear();
}

void McCol::Button::Initialize()
{
    UI::Initialize();
}

void McCol::Button::Update(const float& deltaTime)
{
    UI::Update(deltaTime);
}

void McCol::Button::FixedUpdate(const float& deltaTime)
{
    UI::FixedUpdate(deltaTime);
}

void McCol::Button::Render(McCol::D2DRender* renderer)
{
    UI::Render(renderer);
}

void McCol::Button::HandleCollisionEnter(McCol::Collider* otherCollider)
{
    if (!m_IsInteractable)
        return;

    DEBUGPRINT("HandleCollisionEnter\n");
    for (auto& evtID : m_ButtonOnEvents)
    {
        McCol::EventSystem::GetInstance()->PublishEvent(evtID, this);
    }
}

void McCol::Button::HandleCollisionStay(McCol::Collider* otherCollider)
{
    if (!m_IsInteractable)
        return;

    if (InputSystem::GetInstance()->IsKeyDown(VK_LBUTTON))
    {
        DEBUGPRINT("HandleCollisionStay\n");
        for (auto& evtID : m_ButtonClickEvents)
        {
            McCol::EventSystem::GetInstance()->PublishEvent(evtID, this);
        }
    }
}

void McCol::Button::HandleCollisionExit(McCol::Collider* otherCollider)
{
    if (!m_IsInteractable)
        return;

    DEBUGPRINT("%f, %f\n", GetComponent<Transform>()->GetPosition().x, GetComponent<Transform>()->GetPosition().y);
    for (auto& evtID : m_ButtonOutEvents)
    {
        McCol::EventSystem::GetInstance()->PublishEvent(evtID, this);
    }
}

void McCol::Button::ReserveButtonClickEvent(std::wstring_view evtID)
{
    m_ButtonClickEvents.push_back(evtID);
}

void McCol::Button::ReserveButtonOnEvent(std::wstring_view evtID)
{
    m_ButtonOnEvents.push_back(evtID);
}

void McCol::Button::ReserveButtonOutEvent(std::wstring_view evtID)
{
    m_ButtonOutEvents.push_back(evtID);
}

