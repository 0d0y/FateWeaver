#pragma once
#include "../Engine/Scene.h"

namespace McCol
{
    class UI;
    class Button;
    class EventSystem;
}

class TestSceneMJ : public McCol::Scene
{
public:
    TestSceneMJ()
        : Scene(L"¹ÎÁ¤ÀÌÀÇ Å×½ºÆ® ¾À")
        , m_CameraObj(nullptr)
        , m_BgObj(nullptr)
        , m_DeathObj(nullptr)
    {
        McCol::EventSystem::GetInstance()->Subscribe(L"UI_BUTTON_DOWN", MakeListenerInfo(&TestSceneMJ::Test));
        McCol::EventSystem::GetInstance()->Subscribe(L"UI_BUTTON_UP", MakeListenerInfo(&TestSceneMJ::Test2));
    }

    ~TestSceneMJ() override;
    void Enter() override;
    void Exit() override;
    void Update(const float& deltaTime) override;
    void FixedUpdate(const float& deltaTime) override;
    void LateUpdate(const float& deltaTime) override;
    void Render(McCol::D2DRender* renderer) override;

    McCol::GameObject* m_CameraObj;
    McCol::GameObject* m_BgObj;
    McCol::GameObject* m_DeathObj;
    McCol::UI* m_UIObj;
    McCol::Button* m_ButtonObj;

    void Test(std::any any);
    void Test2(std::any any);
};

