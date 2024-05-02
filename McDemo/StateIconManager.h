//TODO : vector<Icon*> m_Icons에 해당하는 state 들어오면 push_back
// Receive State, RepeatNum 받아서 RepeatNum 0일때 vector에서 erase하고 한칸씩 땡김
// 한칸씩 땡긴 이후에, SetXOffset으로 위치 설정

#pragma once

#include <vector>

namespace McCol
{
    class StateIcon;
}

enum class State;

class StateIconManager
{
public:
    StateIconManager();
    ~StateIconManager() = default;

private:
    float startX;
    float startY;

    std::vector<McCol::StateIcon*> m_Icons;

public:
    void Initialize(float x, float y);
    void Finialize();

    void ModifyState(State state, const int& repeatCount);
    void OffRender();

private:
    void AddState(State state, const int& repeatCount);

};

