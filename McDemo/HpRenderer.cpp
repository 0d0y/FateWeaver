#include "../Engine/pch.h"
#include "HpRenderer.h"

#include "../Engine/Transform.h"
#include "../Engine/CameraSystem.h"
#include "../Engine/TextRenderer.h"

#include "../RenderEngine/D2DRender.h"
#include "../RenderEngine/D2DTextureSystem.h"

using namespace McCol;

HpRenderer::HpRenderer(McCol::GameObject* owner)
    : BaseRenderer(owner)
    , m_IsShrink(false)
    , m_MaxHp(0)
{
    m_Name = stringToWstring(typeid(*this).name());

    // Hp Text 추가
    m_HpText = new TextRenderer(owner);
    m_HpText->SetLayoutRect(100.f, 100.f);
    m_HpText->SetTextAttribute(L"0/0", 17.f, FontWeight::BOLD);
    m_HpText->SetBrushColor(D2D1::ColorF::White);
}

HpRenderer::~HpRenderer()
{
    delete m_HpText;
}

void HpRenderer::Initialize()
{
    BaseRenderer::Initialize();
    m_HpText->Initialize();
}

void HpRenderer::FixedUpdate(const float& deltaTime)
{
    if (m_IsShrink)
    {
        // 곱해주는 숫자가 커질수록 줄어드는 속도가 느려짐
        m_PrevHp -= deltaTime * 40;

        if (m_PrevHp < m_CurHp)
        {
            m_PrevHp = m_CurHp;
            m_IsShrink = false;
        }

        if (m_OrangeWidth <= m_InitWidth)
            m_OrangeWidth = (m_PrevHp / m_MaxHp) * m_InitWidth;

        m_HpProgressTime += deltaTime;
    }
}

void HpRenderer::Render(McCol::D2DRender* renderer)
{
    const auto& textureScale = D2D1::Matrix3x2F::Scale(m_TextureScale.x, m_TextureScale.y);

    renderer->GetContext()->SetTransform(textureScale * m_pTransform->GetMatrix() * CameraSystem::GetInstance()->GetCameraMatrix());

    m_HpFrameDstRect = {
        m_Offset.x,
        m_Offset.y,
        m_Offset.x + (m_HpFrameSrcRect.right - m_HpFrameSrcRect.left),
        m_Offset.y - (m_HpFrameSrcRect.bottom - m_HpFrameSrcRect.top) };
    m_BlackBarDstRect = {
            m_Offset.x,
        m_Offset.y,
        m_Offset.x + (m_BlackBarSrcRect.right - m_BlackBarSrcRect.left),
        m_Offset.y - (m_BlackBarSrcRect.bottom - m_BlackBarSrcRect.top) };
    m_OrangeBarDstRect = {
               m_Offset.x,
       m_Offset.y,
       m_Offset.x + m_OrangeWidth,
       m_Offset.y - (m_OrangeBarSrcRect.bottom - m_OrangeBarSrcRect.top) };
    m_RedBarDstRect = {
        m_Offset.x,
        m_Offset.y,
        m_Offset.x + m_RedWidth,
        m_Offset.y - (m_RedBarSrcRect.bottom - m_RedBarSrcRect.top) };

    renderer->GetContext()->DrawBitmap(m_BlackBar, m_BlackBarDstRect, m_Opacity);
    renderer->GetContext()->DrawBitmap(m_OrangeBar, m_OrangeBarDstRect, m_Opacity);
    renderer->GetContext()->DrawBitmap(m_RedBar, m_RedBarDstRect, m_Opacity);
    //renderer->GetContext()->DrawBitmap(m_HpFrame, m_HpFrameDstRect, m_Opacity);

    m_HpText->Render(renderer);
}

void HpRenderer::LoadTexture(HpType hpType)
{
    switch (hpType)
    {
    case HpType::SHORT:
    {
        m_HpFrame = D2DTextureSystem::GetInstance()->LoadTexture(L"../Resource/UI/UI_HP_Short_Frame.png", L"UI_HP_Short_Frame");
        m_BlackBar = D2DTextureSystem::GetInstance()->LoadTexture(L"../Resource/UI/UI_HP_Short_Damaged.png", L"UI_HP_Short_Damaged");
        m_OrangeBar = D2DTextureSystem::GetInstance()->LoadTexture(L"../Resource/UI/UI_HP_Short_Lose.png", L"UI_HP_Short_Lose");
        m_RedBar = D2DTextureSystem::GetInstance()->LoadTexture(L"../Resource/UI/UI_HP_Short_Full.png", L"UI_HP_Short_Full");
        m_InitWidth = m_RedWidth = m_OrangeWidth = 139.f;
        break;
    }
    case HpType::MIDDLE:
    {
        m_HpFrame = D2DTextureSystem::GetInstance()->LoadTexture(L"../Resource/UI/UI_HP_Frame_middle.png", L"UI_HP_Frame_middle");
        m_BlackBar = D2DTextureSystem::GetInstance()->LoadTexture(L"../Resource/UI/UI_HP_middle_Damaged.png", L"UI_HP_middle_Damaged");
        m_OrangeBar = D2DTextureSystem::GetInstance()->LoadTexture(L"../Resource/UI/UI_HP_middle_lose .png", L"UI_HP_middle_lose ");
        m_RedBar = D2DTextureSystem::GetInstance()->LoadTexture(L"../Resource/UI/UI_HP_middlel.png", L"UI_HP_middlel");
        m_InitWidth = m_RedWidth = m_OrangeWidth = 241.f;
        break;
    }
    case HpType::LONG:
    {
        m_HpFrame = D2DTextureSystem::GetInstance()->LoadTexture(L"../Resource/UI/UI_HP_Long_Frame.png", L"UI_HP_Long_Frame");
        m_BlackBar = D2DTextureSystem::GetInstance()->LoadTexture(L"../Resource/UI/UI_HP_Long_Damaged.png", L"UI_HP_Long_Damaged");
        m_OrangeBar = D2DTextureSystem::GetInstance()->LoadTexture(L"../Resource/UI/UI_HP_Long_Lose.png", L"UI_HP_Long_Lose");
        m_RedBar = D2DTextureSystem::GetInstance()->LoadTexture(L"../Resource/UI/UI_HP_Long_Full.png", L"UI_HP_Long_Full");
        m_InitWidth = m_RedWidth = m_OrangeWidth = 360.f;
        break;
    }
    }

    m_HpFrameSrcRect = { 0.f, 0.f, m_HpFrame->GetSize().width, m_HpFrame->GetSize().height };
    m_BlackBarSrcRect = { 0.f, 0.f, m_BlackBar->GetSize().width, m_BlackBar->GetSize().height };
    m_OrangeBarSrcRect = { 0.f, 0.f, m_OrangeBar->GetSize().width, m_OrangeBar->GetSize().height };
    m_RedBarSrcRect = { 0.f, 0.f, m_RedBar->GetSize().width, m_RedBar->GetSize().height };
}

void HpRenderer::SetTextureScale(const float& scale)
{
    m_TextureScale = { scale, scale };
}

void HpRenderer::ModifyHpBar(int maxHp, int curHp, int damage)
{
    std::wstring temp = std::to_wstring(curHp) + L"/" + std::to_wstring(maxHp);
    m_HpText->SetSrcText(temp);
    m_HpText->SetFontWeight(FontWeight::BOLD);

    if (curHp > maxHp)
    {
        return;
    }

    if (m_MaxHp == 0)
    {
        SetStartHp(maxHp);
    }

    if (curHp < 0)
    {
        curHp = 0;
    }
    else if (maxHp < curHp)
    {
        curHp = maxHp;
    }

    if (m_PrevHp <= curHp)
    {
        m_IsShrink = false;
        m_PrevHp = curHp; // Update m_PrevHp immediately when curHp increases
    }
    else
    {
        m_IsShrink = true;
    }

    m_MaxHp = maxHp;
    m_CurHp = curHp;

    m_RedWidth = (static_cast<float>(curHp) / maxHp) * m_InitWidth;
}

TextRenderer* HpRenderer::GetHpText()
{
    return m_HpText;
}


// 시작 체력(체력의 Max)
void HpRenderer::SetStartHp(int hp)
{
    m_MaxHp = m_CurHp = m_PrevHp = hp;
}
