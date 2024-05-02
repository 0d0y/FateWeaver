#include "pch.h"
#include "UIRenderer.h"

#include "UI.h"
#include "Transform.h"

#include "TextRenderer.h"
#include "TextureRenderer.h"
#include "Animation.h"
#include "PrimitiveRenderer.h"


McCol::UIRenderer::UIRenderer(GameObject* owner)
    : BaseRenderer(owner)
    , m_UI(nullptr)
    , m_UITransform(nullptr)
    , m_UIText(nullptr)
    , m_UITexture(nullptr)
    , m_UIAnimation(nullptr)
    , m_UIPrimitive(nullptr)
    , m_IsUIText(false)
    , m_IsUITexture(false)
    , m_IsUIAnimation(false)
    , m_IsPrimitive(false)
    , m_UIAreaRect{}
    , m_UIOffset{}
{
    m_UITransform = m_Owner->GetComponent<Transform>();
    m_UI = dynamic_cast<UI*>(m_Owner);
}

McCol::UIRenderer::~UIRenderer()
{
}

void McCol::UIRenderer::Initialize()
{
    BaseRenderer::Initialize();
}

void McCol::UIRenderer::FixedUpdate(const float& deltaTime)
{
    BaseRenderer::FixedUpdate(deltaTime);
    if (m_IsUIAnimation)
    {
        m_UIAnimation->FixedUpdate(deltaTime);
    }
}

void McCol::UIRenderer::Render(D2DRender* renderer)
{
    BaseRenderer::Render(renderer);
    SetUIAreaRect();

    if (m_IsUIText)
    {
        m_UIText->Render(renderer);
    }

    if (m_IsUITexture)
    {
        m_UITexture->Render(renderer);
    }

    if (m_IsUIAnimation)
    {
        m_UIAnimation->Render(renderer);
    }

    if (m_IsPrimitive)
    {
        m_UIPrimitive->Render(renderer);
    }
}

McCol::TextRenderer* McCol::UIRenderer::GetUIText()
{
    m_IsUIText = true;
    return m_UIText;
}

McCol::TextureRenderer* McCol::UIRenderer::GetUITexture()
{
    m_IsUITexture = true;
    return m_UITexture;
}

McCol::Animation* McCol::UIRenderer::GetUIAnimation()
{
    m_IsUIAnimation = true;
    return m_UIAnimation;
}

McCol::PrimitiveRenderer* McCol::UIRenderer::GetUIPrimitive()
{
    m_IsPrimitive = true;
    return m_UIPrimitive;
}

void McCol::UIRenderer::AddUIText()
{
    m_UIText = AddComponent<TextRenderer>();
}

void McCol::UIRenderer::AddUITexture()
{
    m_UITexture = AddComponent<TextureRenderer>();
}

void McCol::UIRenderer::AddUIAnimation()
{
    m_UIAnimation = AddComponent<Animation>();
}

void McCol::UIRenderer::AddUIPrimitive()
{
    m_UIPrimitive = AddComponent<PrimitiveRenderer>();
}

bool McCol::UIRenderer::IsUITest()
{
    return m_IsUIText;
}

bool McCol::UIRenderer::IsUITexture()
{
    return m_IsUITexture;
}

bool McCol::UIRenderer::IsUIAnimation()
{
    return m_IsUIAnimation;
}

bool McCol::UIRenderer::IsUIPrimitive()
{
    return m_IsPrimitive;
}

void McCol::UIRenderer::SetUIAreaRect()
{
    //m_UIAreaRect = m_UI->GetUIAreaRect();

    if (m_IsUIText)
    {
        GetUIText()->SetLayoutRect(m_UIAreaRect.right - m_UIAreaRect.left, m_UIAreaRect.top - m_UIAreaRect.bottom);
    }

    if (m_IsUITexture)
    {
        // Texture의 경우, TextureRenderer안에서 Offset이 조정되기 때문에 UILayout을 적용해줄 필요 없음
    }

    if (m_IsUIAnimation)
    {
        // Animation도 Texture와 동일함
    }

    if (m_IsPrimitive)
    {
        GetUIPrimitive()->SetPmRectangle(m_UIAreaRect.right - m_UIAreaRect.left, m_UIAreaRect.top - m_UIAreaRect.bottom);
    }
}


