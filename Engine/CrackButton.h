#pragma once
#include "MapButton.h"

namespace McCol
{
    class CrackButton : public MapButton
    {
    public:
        CrackButton(std::wstring_view name, int stageIndex);
        ~CrackButton() override;

    private:
        int m_StageIndex;

    public:
        void Initialize() override;
        void Update(const float& deltaTime) override;
        void FixedUpdate(const float& deltaTime) override;
        void Render(McCol::D2DRender* renderer) override;

        void HandleCollisionEnter(McCol::Collider* otherCollider) override;
        void HandleCollisionStay(McCol::Collider* otherCollider) override;
        void HandleCollisionExit(McCol::Collider* otherCollider) override;
    };
}

