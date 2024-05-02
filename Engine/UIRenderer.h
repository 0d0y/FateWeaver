#pragma once
#include "BaseRenderer.h"
#include "Vector2.h"

namespace McCol
{
    class UI;
    class Transform;

    class TextRenderer;
    class TextureRenderer;
    class Animation;
    class PrimitiveRenderer;

    class UIRenderer :
        public BaseRenderer
    {
    public:
        UIRenderer(GameObject* owner);
        ~UIRenderer() override;

    private:
        UI* m_UI;
        Transform* m_UITransform;

        TextRenderer* m_UIText;
        TextureRenderer* m_UITexture;
        Animation* m_UIAnimation;
        PrimitiveRenderer* m_UIPrimitive;

        bool m_IsUIText;
        bool m_IsUITexture;
        bool m_IsUIAnimation;
        bool m_IsPrimitive;

        D2D1_RECT_F m_UIAreaRect;
        Vector2 m_UIOffset;

    public:
        void Initialize() override;
        void FixedUpdate(const float& deltaTime) override;
        void Render(D2DRender* renderer) override;

        TextRenderer* GetUIText();
        TextureRenderer* GetUITexture();
        Animation* GetUIAnimation();
        PrimitiveRenderer* GetUIPrimitive();

        void AddUIText();
        void AddUITexture();
        void AddUIAnimation();
        void AddUIPrimitive();

        bool IsUITest();
        bool IsUITexture();
        bool IsUIAnimation();
        bool IsUIPrimitive();

        void SetUIAreaRect();
    };
}

