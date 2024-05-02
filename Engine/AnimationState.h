#pragma once
#include "AnimationClip.h"

namespace McCol
{
    class AnimationState
    {
    public:
        AnimationState();
        AnimationState(const std::vector<AnimationClip>& clips);

    public:
        std::vector<AnimationClip> Clips;
        bool IsLoop;
    };
}


