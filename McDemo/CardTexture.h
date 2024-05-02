#pragma once
#include "../Engine/BaseRenderer.h"
#include "../Engine/EventHandler.h"

namespace McCol
{
	class TextureRenderer;
	class TextRenderer;
}

enum class FrameEffectInfo
{
    NONE,
    FRAME_GREEN,
    FRAME_YELLOW,
    FRAME_RED,
    END
};

class CardTexture : public McCol::BaseRenderer, public McCol::EventHandler
{
public:
    CardTexture(McCol::GameObject* owner);
    ~CardTexture() override;

private:
    std::vector<McCol::TextureRenderer*> m_CardTextures;
    std::vector<McCol::TextRenderer*> m_CardTexts;
    McCol::TextureRenderer* m_FrameEffectTextures;
    McCol::TextureRenderer* m_MiniFrameEffectTextures;
    bool m_IsHighlighted;
    bool m_IsOnFuture;
    bool m_IsCardRender;

public:
    void Initialize() override;
    void FixedUpdate(const float& deltaTime) override;
    void Render(McCol::D2DRender* renderer) override;

private:
    void CardRender(McCol::D2DRender* renderer);     // 기본 렌더링
    void FutureRender(McCol::D2DRender* renderer);      // 미래 영역 아이콘 렌더링

public:
    //void SetIllustration(std::wstring_view filePath, std::wstring_view key);
    void SetIllustration(std::wstring_view key);
    ID2D1Bitmap* GetIllustration();
    ID2D1Bitmap* GetFrame();

    void SetIsFutureRender(bool isFutureRender);
    void SetIsCardRender(bool isCardRender);

    void SetTextureScale(const float& scale);
    D2D1_SIZE_F GetRenderSize();

    void RenewalString();
    void IsFremeEffect(bool isFrameEffectRender, FrameEffectInfo effectInfo = FrameEffectInfo::NONE);
};