#pragma once
#include "Vector2.h"

namespace McCol
{
    class Camera;
    class CameraSystem
    {
    public:
        CameraSystem();
        ~CameraSystem() = default;

    public:
        static CameraSystem* GetInstance()
        {
            if (m_Instance == nullptr)
                m_Instance = new CameraSystem();

            return m_Instance;
        }

    private:
        static CameraSystem* m_Instance;
        Camera* m_Camera;

    public:
        void Initialize();
        void Finalize();
        void Register(Camera* camera);          // 카메라 시스템에 카메라 등록
        D2D1_MATRIX_3X2_F GetCameraMatrix();    // 카메라 역행렬 반환
    };
}

