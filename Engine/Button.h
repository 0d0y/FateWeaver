#pragma once
#include "UI.h"

namespace McCol
{
    class Button : public UI
    {
    public:
        Button(std::wstring_view name);
        ~Button() override;

    private:
        std::vector<std::wstring_view> m_ButtonClickEvents;
        std::vector<std::wstring_view> m_ButtonOnEvents;
        std::vector<std::wstring_view> m_ButtonOutEvents;

        //bool m_IsInteractive;

    public:
        void Initialize() override;
        void Update(const float& deltaTime) override;
        void FixedUpdate(const float& deltaTime) override;
        void Render(McCol::D2DRender* renderer) override;

        void HandleCollisionEnter(McCol::Collider* otherCollider) override;
        void HandleCollisionStay(McCol::Collider* otherCollider) override;
        void HandleCollisionExit(McCol::Collider* otherCollider) override;

        void ReserveButtonClickEvent(std::wstring_view evtID);
        void ReserveButtonOnEvent(std::wstring_view evtID);
        void ReserveButtonOutEvent(std::wstring_view evtID);

        //void IsMapIconInteractive();
    };
}

