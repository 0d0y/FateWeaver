#include "pch.h"
#include "CameraSystem.h"

#include "Camera.h"
#include "Transform.h"
#include "Mengine.h"

McCol::CameraSystem* McCol::CameraSystem::m_Instance = nullptr;

McCol::CameraSystem::CameraSystem()
    : m_Camera(nullptr)
{
}

void McCol::CameraSystem::Initialize()
{
}

void McCol::CameraSystem::Finalize()
{
    SAFE_DELETE(m_Instance)
}

void McCol::CameraSystem::Register(Camera* camera)
{
    m_Camera = camera;
}

D2D1_MATRIX_3X2_F McCol::CameraSystem::GetCameraMatrix()
{
    D2D1_MATRIX_3X2_F cameraMatrix = m_Camera->GetWorldMatrix();

    D2D1InvertMatrix(&cameraMatrix);

    cameraMatrix.dx += static_cast<float>(Mengine::ResolutionWidth) / 2;
    cameraMatrix.dy += static_cast<float>(Mengine::ResolutionHeight) / 2;

    return cameraMatrix;
}

