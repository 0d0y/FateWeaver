#pragma once
#include "../Engine/BaseRenderer.h"

namespace McCol
{
    class TextRenderer;
}

enum class HpType
{
    SHORT,
    MIDDLE,
    LONG
};

class HpRenderer : public McCol::BaseRenderer
{
public:
    HpRenderer(McCol::GameObject* owner);
    ~HpRenderer() override;

private:
    ID2D1Bitmap* m_HpFrame;
    ID2D1Bitmap* m_BlackBar;
    ID2D1Bitmap* m_OrangeBar;
    ID2D1Bitmap* m_RedBar;

    float m_MaxHp;
    float m_CurHp;
    float m_PrevHp;

    float m_InitWidth;
    float m_RedWidth;
    float m_OrangeWidth;

    D2D1_RECT_F m_HpFrameSrcRect;
    D2D1_RECT_F m_BlackBarSrcRect;
    D2D1_RECT_F m_OrangeBarSrcRect;
    D2D1_RECT_F m_RedBarSrcRect;

    D2D1_RECT_F m_HpFrameDstRect;
    D2D1_RECT_F m_BlackBarDstRect;
    D2D1_RECT_F m_OrangeBarDstRect;
    D2D1_RECT_F m_RedBarDstRect;

    bool m_IsShrink;

    float m_HpProgressTime;

    McCol::TextRenderer* m_HpText;

public:
    void Initialize() override;
    void FixedUpdate(const float& deltaTime) override;
    void Render(McCol::D2DRender* renderer) override;

    void LoadTexture(HpType hpType);

    void SetTextureScale(const float& scale);

    void ModifyHpBar(int maxHp, int curHp, int damage);

    McCol::TextRenderer* GetHpText();

private:
    void SetStartHp(int hp);

};

