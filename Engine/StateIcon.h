#pragma once
#include "Icon.h"

namespace McCol
{
    class StateIcon : public Icon
    {
    public:
        StateIcon(std::wstring_view name);
        ~StateIcon() override;

    private:
        float m_StateIconOffsetX;
        int m_RepeatCount;
        State m_IconState;

        float m_StateIconPosX;
        float m_StateIconPosY;

    public:
        void Initialize() override;
        void Update(const float& deltaTime) override;
        void FixedUpdate(const float& deltaTime) override;
        void Render(McCol::D2DRender* renderer) override;

        void HandleCollisionEnter(McCol::Collider* otherCollider) override;
        void HandleCollisionStay(McCol::Collider* otherCollider) override;
        void HandleCollisionExit(McCol::Collider* otherCollider) override;

        void SetIconOffset(const int& xOffset);
        void SetIconTransform(const float x, const float y);

        void SetIconState(State iconState);
        State GetIconState();

        void SetIconRepeatCount(const int& repeatCount);
        int GetIconRepeatCount();
    };
}


