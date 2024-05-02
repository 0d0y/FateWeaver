#pragma once
#include "Collider.h"

namespace McCol
{
    class OBB : public Collider
    {
    public:
        OBB(GameObject* owner);
        ~OBB() override;

    public:
        virtual void Initialize() override;
        virtual void FixedUpdate(const float& deltaTime) override;

        bool CheckCollision(Collider* other) override;
        Vector2 GetVertex(int index) const;
    };
}