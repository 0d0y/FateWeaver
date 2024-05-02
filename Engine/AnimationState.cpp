#include "pch.h"
#include "AnimationState.h"

McCol::AnimationState::AnimationState()
    : IsLoop(true)
{
}

McCol::AnimationState::AnimationState(const std::vector<AnimationClip>& clips)
    : IsLoop(true)
    , Clips(clips)
{
}
