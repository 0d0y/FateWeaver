#pragma once
#include "UI.h"

namespace McCol
{
    class Panel : public UI
    {
    public:
        Panel(std::wstring_view name);
        ~Panel() override;

    private:
        std::vector<std::wstring_view> m_PanelOnEvents;
        std::vector<std::wstring_view> m_PanelOutEvents;

        float m_PanelOffsetX;
        float m_PanelOffsetY;

    public:
        void Initialize() override;
        void Update(const float& deltaTime) override;
        void FixedUpdate(const float& deltaTime) override;
        void Render(McCol::D2DRender* renderer) override;

        void HandleCollisionEnter(McCol::Collider* otherCollider) override;
        void HandleCollisionStay(McCol::Collider* otherCollider) override;
        void HandleCollisionExit(McCol::Collider* otherCollider) override;

        void ReservePanelOnEvent(std::wstring_view evtID);
        void ReservePanelOutEvent(std::wstring_view evtID);

        void SetPanelOffset(const float& xOffset, const float& yOffset);
    };
}

