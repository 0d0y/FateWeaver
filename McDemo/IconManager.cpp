#include "../Engine/pch.h"
#include "IconManager.h"
#include "../Engine/Scene.h"
#include "../Engine/Icon.h"

IconManager::IconManager()
    : m_Icon(nullptr)
{
    // TODO : new Icon stateIcon에 해당하는 것들 다 해놓기
}

void IconManager::Initialize()
{
}

void IconManager::Finialize()
{
}

void IconManager::Resgister(McCol::Icon* icon)
{
    m_Icon = icon;
    m_Icons.push_back(icon);

    // TODO : 이거 아이콘 매니저 클래스에서 하면 Scene::Exit할때 오류 남..
    //McCol::Scene::EventCreateOBJ(icon);
}
