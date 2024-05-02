#pragma once
#include "UI.h"

enum class State;

namespace McCol
{
    class Icon : public UI
    {
    public:
        Icon(std::wstring_view name);
        ~Icon() override;

    protected:
        std::vector<std::wstring_view> m_IconOnEvents;
        std::vector<std::wstring_view> m_IconOutEvents;

        float m_IconPanelOffsetX;

    public:
        void Initialize() override;
        void Update(const float& deltaTime) override;
        void FixedUpdate(const float& deltaTime) override;
        void Render(McCol::D2DRender* renderer) override;

        void HandleCollisionEnter(McCol::Collider* otherCollider) override;
        void HandleCollisionStay(McCol::Collider* otherCollider) override;
        void HandleCollisionExit(McCol::Collider* otherCollider) override;

        void ReserveIconOnEvent(std::wstring_view evtID);
        void ReserveIconOutEvent(std::wstring_view evtID);

        void SetIconPanelOffset(const float& xOffset);
    };
}

