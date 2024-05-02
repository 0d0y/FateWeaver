#pragma once
#include "Component.h"

namespace McCol
{
    class Transform;

    class Camera final : public McCol::Component
    {
    public:
        Camera(GameObject* owner);
        ~Camera() override = default;

    private:
        GameObject* m_TargetObject;                     // 카메라 컴포넌트를 지닌 타겟 오브젝트
        Transform* m_Transform;                         // 타겟 오브젝트의 트랜스폼

    public:
        void Initialize() override;

        D2D1_MATRIX_3X2_F GetWorldMatrix() const;       // 카메라 컴포넌트를 지닌 타겟 오브젝트의 WorldMatrix 반환
        void SetTargetObject(GameObject* targetObject); // 타겟 오브젝트 설정
    };
}
