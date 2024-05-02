//TODO : vector<Icon*> m_Icons에 해당하는 state 들어오면 push_back
// Receive State, RepeatNum 받아서 RepeatNum 0일때 vector에서 erase하고 한칸씩 땡김
// 한칸씩 땡긴 이후에, SetXOffset으로 위치 설정

#pragma once

#include <vector>

namespace McCol
{
    class Icon;
}

class IconManager
{
public:
    IconManager();
    ~IconManager() = default;

private:
    McCol::Icon* m_Icon;
    std::vector<McCol::Icon*> m_Icons;

public:
    void Initialize();
    void Finialize();
    void Resgister(McCol::Icon* icon);
};

