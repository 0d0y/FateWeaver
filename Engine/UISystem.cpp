#include "pch.h"
#include "UISystem.h"
#include "UI.h"

McCol::UISystem* McCol::UISystem::m_Instance = nullptr;

McCol::UISystem::UISystem()
    : m_FocusedUI(nullptr)
{
}

void McCol::UISystem::Initialize()
{
}

void McCol::UISystem::Update(const float& deltaTime)
{
}

void McCol::UISystem::SetFocusedUI(UI* ui)
{
}

void McCol::UISystem::GetFocusedUI()
{
}

void McCol::UISystem::RegisterUI(const std::wstring_view& uiName, McCol::UI* ui)
{
    
}
