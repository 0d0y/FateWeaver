#pragma once
#include "BaseRenderer.h"
#include "IFixedUpdatable.h"
#include "AnimationState.h"
#include <unordered_map>

namespace McCol
{
    class AnimationRenderer :
        public McCol::BaseRenderer
    {
    public:
        AnimationRenderer(GameObject* owner);
        ~AnimationRenderer() override;

    private:
        std::unordered_map<std::string, AnimationState*> m_States;
        AnimationState* m_CurAnimState;
        ID2D1Bitmap* m_d2dBitmap;
        int m_ClipIndex;
        int m_PlaySpeed;
        float m_ProgressTime;
        bool IsFlipX;

        std::vector<std::pair<int, int>> m_FrameInfo;

    public:
        void Initialize() override;
        void FixedUpdate(const float& deltaTime) override;
        void Render(D2DRender* renderer) override;

        void Play(const std::string& name);
        void Stop();
        int GetSpeed();
        void SetSpeed(const float& speed);
        void SetFlip();
        void SetFrameInfo(ID2D1Bitmap1* bitmap, const float& frameWidth, const float& frameHeight);

        ID2D1Bitmap* GetBitmap();
        void SetBitmap(ID2D1Bitmap* bitmap);
        void SetAnimState(AnimationState* animstate);
    };
}


