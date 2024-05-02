#pragma once
#include "BaseRenderer.h"

namespace McCol
{
    class TextureRenderer : public McCol::BaseRenderer
    {
    public:
        TextureRenderer(GameObject* owner);
        ~TextureRenderer() override;

    private:
        ID2D1Bitmap* m_d2dBitmap;

    public:
        void Initialize() override;
        void Render(D2DRender* renderer) override;

        D2D1_SIZE_F GetRenderSize();
        ID2D1Bitmap* GetBitmap();
        void SetBitmap(ID2D1Bitmap* bitmap);    // 해당 비트맵의 사이즈로 SrcRect 사이즈 설정
        void LoadTexture(std::wstring_view filePath, std::wstring_view key);
        void GetTexture(std::wstring_view key);

        void SetTextureScale(const float& scale);
    };
}

