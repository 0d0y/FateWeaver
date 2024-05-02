#pragma once
#include "Vector2.h"

namespace McCol
{
    class AnimationClip
    {
    public:
        Vector2 m_LT;
        Vector2 m_RB;
        Vector2 m_Pivot;
        float m_Length;

    public:
        AnimationClip() :m_Length(0) {}

        AnimationClip(const float& left, const float& top, const float& right, const float& bottom, const float& length)
        {
            m_LT = { left, top };
            m_RB = { right, bottom };
            m_Pivot = { ((right - left) / 2), ((bottom - top) / 2) };
            m_Length = length;
        }

        AnimationClip(const Vector2& lt, const Vector2& rb, const float& length)
        {
            m_LT = lt;
            m_RB = rb;
            m_Pivot = { ((rb.x - lt.x ) / 2), ((rb.y - lt.y) / 2) };
            m_Length = length;
        }

        AnimationClip(const D2D1_RECT_F& rect, const float& length)
        {
            m_LT = { rect.left, rect.top };
            m_RB = { rect.right, rect.bottom };
            m_Pivot = { ((rect.right - rect.left) / 2), ((rect.bottom - rect.top) / 2) };
            m_Length = length;
        }
    };
}

