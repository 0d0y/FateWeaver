#include "pch.h"
#include "Camera.h"
#include "GameObject.h" 
#include "Transform.h"
#include "CameraSystem.h"

McCol::Camera::Camera(GameObject* owner)
    : Component(owner)
    , m_TargetObject(owner)
    , m_Transform(nullptr)
{
    m_Name = stringToWstring(typeid(*this).name());
}

void McCol::Camera::Initialize()
{
    if (GetOwner() == nullptr)
        return;

    m_Transform = m_TargetObject->GetComponent<Transform>();

    if (m_Transform == nullptr)
        return;

    CameraSystem::GetInstance()->Register(this); 
}

D2D1_MATRIX_3X2_F McCol::Camera::GetWorldMatrix() const
{
    return m_Transform->GetMatrix(); 
}

void McCol::Camera::SetTargetObject(GameObject* targetObject)
{
    m_TargetObject = targetObject;
}




