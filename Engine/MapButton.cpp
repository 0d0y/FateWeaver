#include "pch.h"
#include "MapButton.h"

#include "TextureRenderer.h"

McCol::MapButton::MapButton(std::wstring_view name)
    : Button(name)
    , m_IsHighlight(false)
{
    m_HighlightTexture = new TextureRenderer(this);
    UIInteractiveOff(nullptr);
}

McCol::MapButton::~MapButton()
{
    delete m_HighlightTexture;
}

void McCol::MapButton::Initialize()
{
    Button::Initialize();
    m_HighlightTexture->Initialize();
}

void McCol::MapButton::Update(const float& deltaTime)
{
    Button::Update(deltaTime);
}

void McCol::MapButton::FixedUpdate(const float& deltaTime)
{
    Button::FixedUpdate(deltaTime);
}

void McCol::MapButton::Render(McCol::D2DRender* renderer)
{
    if(m_IsHighlight)
    {
        m_HighlightTexture->Render(renderer);
    }

    Button::Render(renderer);
}

void McCol::MapButton::HandleCollisionEnter(McCol::Collider* otherCollider)
{
    if (m_IsHighlight)
    {
        GetUITexture()->SetTextureScale(1.35f);
        m_HighlightTexture->SetTextureScale(1.35f);
    }

    Button::HandleCollisionEnter(otherCollider);
}

void McCol::MapButton::HandleCollisionStay(McCol::Collider* otherCollider)
{
    Button::HandleCollisionStay(otherCollider);
}

void McCol::MapButton::HandleCollisionExit(McCol::Collider* otherCollider)
{
    if (m_IsHighlight)
    {
        GetUITexture()->SetTextureScale(1.0f);
        m_HighlightTexture->SetTextureScale(1.0f);
    }

    Button::HandleCollisionExit(otherCollider);
}

void McCol::MapButton::MakeHighlight()
{
    m_IsHighlight = true;

    UIInteractiveOn(this);

    switch(m_IconType)
    {
    case MapIconType::Monster:
    {
        m_HighlightTexture->LoadTexture(L"../Resource/icon/UI_Map_Monster_effect.png", L"UI_Map_Monster_effect");
        break;
    }
    case MapIconType::Elite:
    {
        m_HighlightTexture->LoadTexture(L"../Resource/icon/UI_Map_Elite_effect.png", L"UI_Map_Elite_effect");
        break;
    }
    case MapIconType::Boss:
    {
        m_HighlightTexture->LoadTexture(L"../Resource/icon/UI_Map_Boss01_effect.png", L"UI_Map_Boss01_effect");
        break;
    }
    case MapIconType::Secret:
    {
        m_HighlightTexture->LoadTexture(L"../Resource/icon/UI_Map_Secret_effect.png", L"UI_Map_Secret_effect");
        break;
    }
    case MapIconType::Tbreak:
    {
        m_HighlightTexture->LoadTexture(L"../Resource/icon/UI_Map_Tbreak_effect.png", L"UI_Map_Tbreak_effect");
        break;
    }
    }
}
