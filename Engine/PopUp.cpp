#include "pch.h"
#include "PopUp.h"

McCol::PopUp::PopUp(std::wstring_view name)
    : UI(name)
{
}

McCol::PopUp::~PopUp()
{
}

void McCol::PopUp::Initialize()
{
    UI::Initialize();
}

void McCol::PopUp::Update(const float& deltaTime)
{
    UI::Update(deltaTime);
}

void McCol::PopUp::FixedUpdate(const float& deltaTime)
{
    UI::FixedUpdate(deltaTime);
}

void McCol::PopUp::Render(McCol::D2DRender* renderer)
{
    UI::Render(renderer);
}

void McCol::PopUp::HandleCollisionEnter(McCol::Collider* otherCollider)
{
    UI::HandleCollisionEnter(otherCollider);
}

void McCol::PopUp::HandleCollisionStay(McCol::Collider* otherCollider)
{
    UI::HandleCollisionStay(otherCollider);
}

void McCol::PopUp::HandleCollisionExit(McCol::Collider* otherCollider)
{
    UI::HandleCollisionExit(otherCollider);
}

void McCol::PopUp::SetTutorialIndex(const int& index)
{
    m_CurTutorialIndex = index;
}

int McCol::PopUp::GetTutorialIndex()
{
    return m_CurTutorialIndex;
}
