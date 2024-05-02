#pragma once
#include "UI.h"
namespace McCol
{
    class PopUp : public UI
    {
    public:
        PopUp(std::wstring_view name);
        ~PopUp() override;

    private:
        int m_CurTutorialIndex;

    public:
        void Initialize() override;
        void Update(const float& deltaTime) override;
        void FixedUpdate(const float& deltaTime) override;
        void Render(McCol::D2DRender* renderer) override;
        void HandleCollisionEnter(McCol::Collider* otherCollider) override;
        void HandleCollisionStay(McCol::Collider* otherCollider) override;
        void HandleCollisionExit(McCol::Collider* otherCollider) override;

        void SetTutorialIndex(const int& index);
        int GetTutorialIndex();
    };
}