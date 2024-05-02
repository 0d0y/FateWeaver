#pragma once
#include "Collider.h"

namespace McCol
{
    class AABB : public Collider
    {
    public:
        AABB(GameObject* owner);
        ~AABB() override;

    public:
        virtual void Initialize() override;
        virtual void FixedUpdate(const float& deltaTime) override;

        bool CheckCollision(Collider* other) override;
    };
}