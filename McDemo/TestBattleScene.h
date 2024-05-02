#pragma once
#include "../Engine/Scene.h"

namespace McCol
{
    class UI;
    class Button;
    class Panel;
    class PopUp;
    class StateIcon;
    class EventSystem;
}

class StateIconManager;
class Mouse;

class HpRenderer;

class TestBattleScene : public McCol::Scene
{
public:
    TestBattleScene();
    ~TestBattleScene() override;

public:
    void Enter() override;
    void Exit() override;
    void Update(const float& deltaTime) override;
    void FixedUpdate(const float& deltaTime) override;
    void LateUpdate(const float& deltaTime) override;
    void Render(McCol::D2DRender* renderer) override;

private:
    McCol::GameObject* m_CameraObj;
    McCol::GameObject* m_BgObj;
    McCol::GameObject* m_IdleObj;

    // UI 상단
    McCol::UI* UIUpperSector;
    McCol::UI* UIUpperIconLogo;
    McCol::UI* UIUpperIconHP;
    McCol::UI* UIUpperHPText;
    McCol::UI* UIUpperIconNowFloor;
    McCol::UI* UIUpperFloorText;
    McCol::Button* UIUpperTutorial;
    McCol::Button* UIUpperFdeck;
    McCol::Button* UIUpperPdeck;
    McCol::Button* UIUpperExit;

    // UI 인게임
    McCol::UI* UIFutureTerritory;
    McCol::UI* UIHPProgressBar;
    McCol::UI* UIPlayerDefense;


    // UI 하단
    McCol::UI* UILowerIconEnergy;
    McCol::UI* UILowerIconOverload;
    McCol::Button* UILowerIconPdeck;
    McCol::Button* UILowerIconFdeck;
    McCol::Button* UILowerIconPgrave;
    McCol::Button* UILowerIconFgrave;

    McCol::Panel* UIPanelTest;
    McCol::Panel* UIPanelTest2;

    McCol::Panel* UIPanelTest3;
    McCol::Panel* UIPanelTest4;

    McCol::UI* UIPopUpTest;
    McCol::Button* UIPopUpButtonTest;

    McCol::UI* UIIconPopUp;

    // 상태이상 아이콘 UI
    StateIconManager* TestIconManager;

    Mouse* m_MouseObj;

    // 체력 바 렌더러
    HpRenderer* m_HpRenderer;
    McCol::GameObject* m_HpBar;

public:
    // UI Event SubScribe용 함수
    void UpperTutorialOn(std::any any);
    void UpperFdeckOn(std::any any);
    void UpperPdeckOn(std::any any);
    void UpperExitOn(std::any any);
    void LowerPdeckOn(std::any any);
    void LowerFdeckOn(std::any any);
    void LowerPgraveOn(std::any any);
    void LowerFgraveOn(std::any any);

    void PanelTestOn(std::any any);
    void PanelTestOut(std::any any);

    void PopUpTestOn(std::any any);

    void IconTestOn(std::any any);
    void IconTestOut(std::any any);
};

