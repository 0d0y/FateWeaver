#pragma once
#include "BaseRenderer.h"
#include "IFixedUpdatable.h"
#include "AnimationState.h"
#include <unordered_map>

#define FRAME(CNT) ((1.f / 60.f) * (CNT))

namespace McCol
{
    class Animation : public McCol::BaseRenderer
    {
    public:
        Animation(GameObject* owner);
        ~Animation() override;

    private:
        std::unordered_map<std::wstring_view, AnimationState> m_States;
        AnimationState* m_CurState;
        ID2D1Bitmap* m_d2dBitmap;
        int m_ClipIndex;
        int m_PlaySpeed;
        bool m_IsFlipX;
        float m_AnimScale;

        std::vector<std::pair<int, int>> m_FrameInfo;

    public:
        void Initialize() override;
        void FixedUpdate(const float& deltaTime) override;
        void Render(D2DRender* renderer) override;

        int GetSpeed();
        void SetSpeed(const float& speed);
        void SetFlip(bool flipX);
        /*void SetFrameInfo(ID2D1Bitmap1* bitmap, const float& frameWidth, const float& frameHeight);*/

        void Load(const std::wstring& strFilePath, std::wstring_view bitmapkey);
        void SetAnimState(std::wstring_view stateKey);
        void AddAnimState(std::wstring_view stateKey, const AnimationState& state);
        void SetAnimScale(const float& scale);
    };
}


