#pragma once
#include "Button.h"

enum class MapIconType
{
    Monster,
    Elite,
    Boss,
    Secret,
    Tbreak
};

namespace McCol
{
    class TextureRenderer;

    class MapButton : public Button
    {
    public:
        MapButton(std::wstring_view name);
        ~MapButton() override;

    private:
        TextureRenderer* m_HighlightTexture;
        bool m_IsHighlight;

    protected:
        MapIconType m_IconType;

    public:
        void Initialize() override;
        void Update(const float& deltaTime) override;
        void FixedUpdate(const float& deltaTime) override;
        void Render(McCol::D2DRender* renderer) override;

        void HandleCollisionEnter(McCol::Collider* otherCollider) override;
        void HandleCollisionStay(McCol::Collider* otherCollider) override;
        void HandleCollisionExit(McCol::Collider* otherCollider) override;

        void MakeHighlight();
    };
}

