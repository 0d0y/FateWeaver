#include "pch.h"
#include "StateIcon.h"

#include "EventSystem.h"
#include "InputSystem.h"
#include "TextureRenderer.h"
#include "Transform.h"

#include "../McDemo/Elements.h"
#include "../McDemo/StateIconManager.h"

McCol::StateIcon::StateIcon(std::wstring_view name)
    : Icon(name)
    , m_StateIconOffsetX(0)
    , m_RepeatCount(0)
    , m_IconState(State::NONE)
{
    AddUIText();
}

McCol::StateIcon::~StateIcon()
{
}

void McCol::StateIcon::Initialize()
{
    Icon::Initialize();
}

void McCol::StateIcon::Update(const float& deltaTime)
{
    Icon::Update(deltaTime);
}

void McCol::StateIcon::FixedUpdate(const float& deltaTime)
{
    Icon::FixedUpdate(deltaTime);
}

void McCol::StateIcon::Render(McCol::D2DRender* renderer)
{
    if (!m_IsAble)
        return;

    Icon::Render(renderer);
}

void McCol::StateIcon::HandleCollisionEnter(McCol::Collider* otherCollider)
{
    if (!m_IsInteractable)
        return;

    Icon::HandleCollisionEnter(otherCollider);

    IconInfo iconInfo = { this, m_IconState, m_IconPanelOffsetX, m_RepeatCount };

    for (auto& evtID : m_IconOnEvents)
    {
        McCol::EventSystem::GetInstance()->PublishEvent(evtID, iconInfo);
    }
}

void McCol::StateIcon::HandleCollisionStay(McCol::Collider* otherCollider)
{
    if (!m_IsInteractable)
        return;

    Icon::HandleCollisionStay(otherCollider);
}

void McCol::StateIcon::HandleCollisionExit(McCol::Collider* otherCollider)
{
    if (!m_IsInteractable)
        return;

    Icon::HandleCollisionExit(otherCollider);

    for (auto& evtID : m_IconOutEvents)
    {
        McCol::EventSystem::GetInstance()->PublishEvent(evtID, this);
    }
}

void McCol::StateIcon::SetIconOffset(const int& xOffset)
{
    m_StateIconOffsetX = 40.f * xOffset;

    GetUITransform()->SetPosition({ m_StateIconPosX + m_StateIconOffsetX, m_StateIconPosY });
}

void McCol::StateIcon::SetIconTransform(const float x, const float y)
{
    m_StateIconPosX = x;
    m_StateIconPosY = y;

    GetUITransform()->SetPosition({ m_StateIconPosX, m_StateIconPosY });
}

void McCol::StateIcon::SetIconState(State iconState)
{
    m_IconState = iconState;

    switch (m_IconState)
    {
    case State::QUICK:
        GetUITexture()->LoadTexture(L"../Resource/icon/Agillity.png", L"QUICK");
        break;

    case State::DISRUPTION:
        GetUITexture()->LoadTexture(L"../Resource/icon/Falling.png", L"DISRUPTION");
        break;

    case State::CONFUSION:
        GetUITexture()->LoadTexture(L"../Resource/icon/Confuse.png", L"CONFUSION");
        break;

    case State::ENCHANTMENT:
        GetUITexture()->LoadTexture(L"../Resource/icon/Charge.png", L"ENCHANTMENT");
        break;

    case State::STUNNED:
        GetUITexture()->LoadTexture(L"../Resource/icon/Stun.png", L"STUNNED");
        break;

    case State::IMPENDING_RUIN:
        GetUITexture()->LoadTexture(L"../Resource/icon/Prophecy.png", L"IMPENDING_RUIN");
        break;

    case State::WILL_OF_RUIN:
        GetUITexture()->LoadTexture(L"../Resource/icon/Will.png", L"WILL_OF_RUIN");
        break;

    case State::ENGINE_OVERLOAD:
        GetUITexture()->LoadTexture(L"../Resource/icon/UI_Icon_Overload.png", L"ENGINE_OVERLOAD_EFFECT");
        GetUITexture()->SetTextureScale(0.5f);
        break;
    case State::DEFENSE:
        GetUITexture()->LoadTexture(L"../Resource/icon/Shield.png", L"DEFENSE");
        break;
    }

    auto kk = GetUITexture()->GetBitmap();
}

void McCol::StateIcon::SetIconRepeatCount(const int& repeatCount)
{
    m_RepeatCount = repeatCount;
    GetUIText()->SetLayoutRect(60.f, 30.f);
    GetUIText()->SetTextAttribute(std::to_wstring(repeatCount), 20.f, FontWeight::BOLD);
    GetUIText()->SetOffset(10.f, 10.f);
    GetUIText()->SetBrushColor(D2D1::ColorF::PowderBlue);
}

int McCol::StateIcon::GetIconRepeatCount()
{

    return m_RepeatCount;
}

State McCol::StateIcon::GetIconState()
{
    return m_IconState;
}
