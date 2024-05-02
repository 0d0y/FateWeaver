#include "TestBattleScene.h"

#include "../Engine/Macro.h"

#include "../Engine/UISystem.h"
#include "../Engine/InputSystem.h"
#include "../Engine/MouseCollisionSystem.h"
#include "../RenderEngine/D2DTextureSystem.h"

#include "../Engine/GameObject.h"
#include "../Engine/Transform.h"
#include "../Engine/Camera.h"

#include "../Engine/BaseRenderer.h"
#include "../Engine/TextureRenderer.h"
#include "../Engine/PrimitiveRenderer.h"
#include "../Engine/TextRenderer.h"
#include "../Engine/Animation.h"
#include "../Engine/AnimationClip.h"
#include "../Engine/AnimationState.h"

#include "../Engine/UI.h"
#include "../Engine/Button.h"
#include "../Engine/Panel.h"
#include "../Engine/StateIcon.h"

#include "Mouse.h"

#include "StateIconManager.h"

#include "Elements.h"

#include "HpRenderer.h"

using namespace McCol;

TestBattleScene::TestBattleScene()
    : Scene(L"UI 테스트용 배틀 씬")
    , m_CameraObj(nullptr)
    , m_BgObj(nullptr)
    , m_IdleObj(nullptr)
    , UIUpperSector(nullptr)
{
    ///UI Upper Button Event
    McCol::EventSystem::GetInstance()->Subscribe(L"UI_TUTORIAL_BUTTON_DOWN", MakeListenerInfo(&TestBattleScene::UpperTutorialOn));
    McCol::EventSystem::GetInstance()->Subscribe(L"UI_UPPER_FDECK_BUTTON_DOWN", MakeListenerInfo(&TestBattleScene::UpperFdeckOn));
    McCol::EventSystem::GetInstance()->Subscribe(L"UI_UPPER_PDECK_DOWN", MakeListenerInfo(&TestBattleScene::UpperPdeckOn));
    McCol::EventSystem::GetInstance()->Subscribe(L"UI_UPPER_EXIT_DOWN", MakeListenerInfo(&TestBattleScene::UpperExitOn));
    McCol::EventSystem::GetInstance()->Subscribe(L"UI_LOWER_PDECK_DOWN", MakeListenerInfo(&TestBattleScene::LowerPdeckOn));
    McCol::EventSystem::GetInstance()->Subscribe(L"UI_LOWER_FDECK_DOWN", MakeListenerInfo(&TestBattleScene::LowerFdeckOn));
    McCol::EventSystem::GetInstance()->Subscribe(L"UI_LOWER_PGRAVE_DOWN", MakeListenerInfo(&TestBattleScene::LowerPgraveOn));
    McCol::EventSystem::GetInstance()->Subscribe(L"UI_LOWER_FGRAVE_DOWN", MakeListenerInfo(&TestBattleScene::LowerFgraveOn));

    ///Panel Event
    McCol::EventSystem::GetInstance()->Subscribe(L"UI_PANEL_TEST_ON", MakeListenerInfo(&TestBattleScene::PanelTestOn));
    McCol::EventSystem::GetInstance()->Subscribe(L"UI_PANEL_TEST_OUT", MakeListenerInfo(&TestBattleScene::PanelTestOut));

    ///PopUp Event
    McCol::EventSystem::GetInstance()->Subscribe(L"UI_POPUP_BUTTON_TEST_ON", MakeListenerInfo(&TestBattleScene::PopUpTestOn));

    ///Icon Event
    McCol::EventSystem::GetInstance()->Subscribe(L"UI_STATE_ICON_ON", MakeListenerInfo(&TestBattleScene::IconTestOn));
    McCol::EventSystem::GetInstance()->Subscribe(L"UI_STATE_ICON_OUT", MakeListenerInfo(&TestBattleScene::IconTestOut));
}

TestBattleScene::~TestBattleScene()
{
}

void TestBattleScene::Enter()
{
    TestIconManager = new StateIconManager();

    ///Background
    m_BgObj = new GameObject(L"배경");

    m_BgObj->AddComponent<Transform>();
    m_BgObj->GetComponent<Transform>()->SetPosition({ 0.f, 0.f });
    m_BgObj->GetComponent<Transform>()->SetScale({ 1.0f, 1.0f });

    m_BgObj->AddComponent<TextureRenderer>();
    m_BgObj->GetComponent<TextureRenderer>()->SetBitmap(D2DTextureSystem::GetInstance()->LoadTexture(L"../Resource/2560X1440.png", L"background"));
    m_BgObj->GetComponent<TextureRenderer>()->SetTextureScale(0.75f);

    ///Camera
    m_CameraObj = new GameObject(L"카메라 오브젝트");

    m_CameraObj->AddComponent<Camera>();

    m_CameraObj->AddComponent<Transform>();
    m_CameraObj->GetComponent<Transform>()->SetPosition({ 0.f, 0.f });
    m_CameraObj->GetComponent<Transform>()->SetScale({ 1.f, 1.f });

    m_CameraObj->AddComponent<PrimitiveRenderer>();
    m_CameraObj->GetComponent<PrimitiveRenderer>()->SetPmRectangle(200.f, 200.f);
    m_CameraObj->GetComponent<PrimitiveRenderer>()->SetPmScale(1.0f);
    m_CameraObj->GetComponent<PrimitiveRenderer>()->SetPmBrushColor(D2D1::ColorF::Red);

    ///Idle
    m_IdleObj = new GameObject(L"플레이어");

    m_IdleObj->AddComponent<Transform>();
    m_IdleObj->GetComponent<Transform>()->SetPosition({ -477.f, -67.5f });
    m_IdleObj->GetComponent<Transform>()->SetScale({ 1.0f, 1.0f });

    m_IdleObj->AddComponent<Animation>();
    m_IdleObj->GetComponent<Animation>()->Load(L"../Resource/FW1_Idle.png", L"FW1_Idle");

    std::vector<AnimationClip> IdleClips;
    IdleClips.push_back({ 490.f * 0, 590.f * 0, 490.f * 1, 590.f * 1, FRAME(10) });
    IdleClips.push_back({ 490.f * 1, 590.f * 0, 490.f * 2, 590.f * 1, FRAME(10) });
    IdleClips.push_back({ 490.f * 2, 590.f * 0, 490.f * 3, 590.f * 1, FRAME(10) });
    IdleClips.push_back({ 490.f * 3, 590.f * 0, 490.f * 4, 590.f * 1, FRAME(10) });
    IdleClips.push_back({ 490.f * 4, 590.f * 0, 490.f * 5, 590.f * 1, FRAME(10) });
    IdleClips.push_back({ 490.f * 5, 590.f * 0, 490.f * 6, 590.f * 1, FRAME(10) });
    AnimationState animstate = AnimationState(IdleClips);

    m_IdleObj->GetComponent<Animation>()->AddAnimState(L"FW1_Idle", animstate);
    m_IdleObj->GetComponent<Animation>()->SetAnimState(L"FW1_Idle");
    m_IdleObj->GetComponent<Animation>()->SetFlip(false);
    m_IdleObj->GetComponent<Animation>()->SetSpeed(1.0f);
    m_IdleObj->GetComponent<Animation>()->SetAnimScale(0.5f);

    ///UI Upper
    UIUpperSector = new UI(L"UI 상단바");
    UIUpperSector->AddUITexture();
    UIUpperSector->SetUIAreaRect(1920.f, 70.f);
    UIUpperSector->LoadUITexture(L"../Resource/UI/UI_UpperSector.png", L"UI_UpperSector");
    UIUpperSector->GetUITransform()->SetPosition({ 0.f, 505.f });

    UIUpperIconLogo = new UI(L"UI 상단바 로고");
    UIUpperIconLogo->AddUITexture();
    UIUpperIconLogo->SetUIAreaRect(170.f, 65.f);
    UIUpperIconLogo->LoadUITexture(L"../Resource/UI/UI_Upperlogo.png", L"UI_Upperlogo");
    UIUpperIconLogo->GetUITexture()->SetTextureScale(1.0f);
    UIUpperIconLogo->GetUITransform()->SetPosition({ -875.f, 505.f });

    UIUpperIconHP = new UI(L"UI 상단바 HP");
    UIUpperIconHP->AddUITexture();
    UIUpperIconHP->SetUIAreaRect(45.f, 40.f);
    UIUpperIconHP->LoadUITexture(L"../Resource/icon/UI_Upper_Icon_HP.png", L"UI_Upper_Icon_HP");
    UIUpperIconHP->GetUITransform()->SetPosition({ -677.5f, 505.f });

    UIUpperHPText = new UI(L"UI 상단바 HP 텍스트");
    UIUpperHPText->AddUIText();
    UIUpperHPText->SetUIAreaRect(75.f, 19.f);
    UIUpperHPText->SetUIText(L"80 / 80", 18.f, FontWeight::BOLD, D2D1::ColorF::White);
    UIUpperHPText->GetUITransform()->SetPosition({ -597.5f, 505.f });

    UIUpperIconNowFloor = new UI(L"UI 상단바 층");
    UIUpperIconNowFloor->AddUITexture();
    UIUpperIconNowFloor->SetUIAreaRect(55.f, 55.f);
    UIUpperIconNowFloor->LoadUITexture(L"../Resource/icon/UI_Upper_Icon_NowFloor.png", L"UI_Upper_Icon_NowFloor");
    UIUpperIconNowFloor->GetUITransform()->SetPosition({ 242.5f, 502.5f });

    UIUpperFloorText = new UI(L"UI 상단바 층 텍스트");
    UIUpperFloorText->AddUIText();
    UIUpperFloorText->SetUIAreaRect(46.f, 25.f);
    UIUpperFloorText->SetUIText(L"4층", 18.f, FontWeight::BOLD, D2D1::ColorF::White);
    UIUpperFloorText->GetUITransform()->SetPosition({ 298.f, 502.5f });

    UIUpperTutorial = new Button(L"UI 상단바 튜토리얼");
    UIUpperTutorial->AddUITexture();
    UIUpperTutorial->SetUIAreaRect(55.f, 55.f);
    UIUpperTutorial->LoadUITexture(L"../Resource/icon/UI_Upper_Tutorial.png", L"UI_Upper_Tutorial");
    UIUpperTutorial->GetUITransform()->SetPosition({ 482.5f, 502.5f });
    UIUpperTutorial->ReserveButtonClickEvent(L"UI_TUTORIAL_BUTTON_DOWN");
    UIUpperTutorial->SetUIActivate(false);

    UIUpperFdeck = new Button(L"UI 상단바 운명카드 덱");
    UIUpperFdeck->AddUITexture();
    UIUpperFdeck->SetUIAreaRect(65.f, 55.f);
    UIUpperFdeck->LoadUITexture(L"../Resource/icon/UI_Upper_Fdeck.png", L"UI_Upper_Fdeck");
    UIUpperFdeck->GetUITransform()->SetPosition({ 732.5f, 502.5f });
    UIUpperFdeck->ReserveButtonClickEvent(L"UI_UPPER_FDECK_BUTTON_DOWN");
    UIUpperFdeck->SetUIActivate(false);

    UIUpperPdeck = new Button(L"UI 상단바 플레이카드 덱");
    UIUpperPdeck->AddUITexture();
    UIUpperPdeck->SetUIAreaRect(65.f, 55.f);
    UIUpperPdeck->LoadUITexture(L"../Resource/icon/UI_Upper_Pdeck.png", L"UI_Upper_Pdeck");
    UIUpperPdeck->GetUITransform()->SetPosition({ 812.5f, 502.5f });
    UIUpperPdeck->ReserveButtonClickEvent(L"UI_UPPER_PDECK_DOWN");
    UIUpperPdeck->SetUIActivate(false);

    UIUpperExit = new Button(L"UI 상단바 게임종료");
    UIUpperExit->AddUITexture();
    UIUpperExit->SetUIAreaRect(55.f, 55.f);
    UIUpperExit->LoadUITexture(L"../Resource/icon/UI_Upper_Exit.png", L"UI_Upper_Exit");
    UIUpperExit->GetUITransform()->SetPosition({ 907.5f, 502.5f });
    UIUpperExit->ReserveButtonClickEvent(L"UI_UPPER_EXIT_DOWN");
    UIUpperExit->SetUIActivate(false);

    ///UI InGame
    UIFutureTerritory = new UI(L"UI 미래영역");
    UIFutureTerritory->AddUITexture();
    UIFutureTerritory->SetUIAreaRect(1327.f, 120.f);
    UIFutureTerritory->LoadUITexture(L"../Resource/UI/UI_FutureTerritory.png", L"UI_FutureTerritory");
    UIFutureTerritory->GetUITransform()->SetPosition({ 1.5f, 390.f });

    UIHPProgressBar = new UI(L"UI 체력 바");
    UIHPProgressBar->AddUIPrimitive();
    UIHPProgressBar->SetUIAreaRect(250.f, 15.f);
    UIHPProgressBar->GetUITransform()->SetPosition({ -515.f, -232.5f });

    UIPlayerDefense = new UI(L"UI 방어도 위치");
    UIPlayerDefense->AddUIPrimitive();
    UIPlayerDefense->SetUIAreaRect(35.f, 35.f);
    UIPlayerDefense->GetUITransform()->SetPosition({ -647.5f, -232.5f });
    UIPlayerDefense->AddUIText();
    UIPlayerDefense->SetUIText(L"0", 18.f, FontWeight::BOLD, D2D1::ColorF::White);

    ///UI Lower
    UILowerIconEnergy = new UI(L"UI 에너지 아이콘");
    UILowerIconEnergy->AddUITexture();
    UILowerIconEnergy->SetUIAreaRect(120.f, 120.f);
    UILowerIconEnergy->LoadUITexture(L"../Resource/icon/UI_Icon_Energy.png", L"UI_Icon_Energy");
    UILowerIconEnergy->GetUITransform()->SetPosition({ -770.f, -315.f });

    UILowerIconPdeck = new Button(L"UI 하단 플레이 덱");
    UILowerIconPdeck->AddUITexture();
    UILowerIconPdeck->SetUIAreaRect(90.f, 90.f);
    UILowerIconPdeck->LoadUITexture(L"../Resource/icon/UI_Icon_Pdeck.png", L"UI_Icon_Pdeck");
    UILowerIconPdeck->GetUITransform()->SetPosition({ -895.f, -360.f });
    UILowerIconPdeck->ReserveButtonClickEvent(L"UI_LOWER_PDECK_DOWN");

    UILowerIconFdeck = new Button(L"UI 하단 운명 덱");
    UILowerIconFdeck->AddUITexture();
    UILowerIconFdeck->SetUIAreaRect(90.f, 90.f);
    UILowerIconFdeck->LoadUITexture(L"../Resource/icon/UI_Icon_Pdeck.png", L"UI_Icon_Pdeck");
    UILowerIconFdeck->GetUITransform()->SetPosition({ -875.f, -485.f });
    UILowerIconFdeck->ReserveButtonClickEvent(L"UI_LOWER_FDECK_DOWN");

    UILowerIconOverload = new UI(L"UI 과부하 리스트");
    UILowerIconOverload->AddUITexture();
    UILowerIconOverload->SetUIAreaRect(60.f, 60.f);
    UILowerIconOverload->LoadUITexture(L"../Resource/icon/UI_Icon_Overload.png", L"UI_Icon_Overload");
    UILowerIconOverload->GetUITransform()->SetPosition({ 910.f, -250.f });

    UILowerIconPgrave = new Button(L"UI 하단 버린 플레이 덱");
    UILowerIconPgrave->AddUITexture();
    UILowerIconPgrave->SetUIAreaRect(90.f, 90.f);
    UILowerIconPgrave->LoadUITexture(L"../Resource/icon/UI_Icon_Fdeck.png", L"UI_Icon_Fdeck");
    UILowerIconPgrave->GetUITransform()->SetPosition({ 895.f, -360.f });
    UILowerIconPgrave->ReserveButtonClickEvent(L"UI_LOWER_PGRAVE_DOWN");

    UILowerIconFgrave = new Button(L"UI 하단 버린 운명 덱");
    UILowerIconFgrave->AddUITexture();
    UILowerIconFgrave->SetUIAreaRect(90.f, 90.f);
    UILowerIconFgrave->LoadUITexture(L"../Resource/icon/UI_Icon_Fgrave.png", L"UI_Icon_Fgrave");
    UILowerIconFgrave->GetUITransform()->SetPosition({ 875.f, -485.f });
    UILowerIconFgrave->ReserveButtonClickEvent(L"UI_LOWER_FGRAVE_DOWN");

    /// UI Panel Test
    UIPanelTest = new Panel(L"패널 테스트");
    UIPanelTest->AddUITexture();
    UIPanelTest->SetUIAreaRect(150.f, 150.f);
    UIPanelTest->LoadUITexture(L"../Resource/icon/Effect_Charge.png", L"Effect_Charge");
    UIPanelTest->GetUITransform()->SetPosition({ -100.f, 0.f });
    UIPanelTest->ReservePanelOnEvent(L"UI_PANEL_TEST_ON");
    UIPanelTest->ReservePanelOutEvent(L"UI_PANEL_TEST_OUT");
    UIPanelTest->SetPanelOffset(150.f, 0.f);

    UIPanelTest2 = new Panel(L"패널 팝업 테스트");
    UIPanelTest2->AddUITexture();
    UIPanelTest2->SetUIAreaRect(150.f, 150.f);
    UIPanelTest2->LoadUITexture(L"../Resource/icon/Effect_Agillity.png", L"Effect_Agillity");
    UIPanelTest2->GetUITransform()->SetPosition({ 0.f, 0.f });
    UIPanelTest2->SetAble(false);

    UIPanelTest3 = new Panel(L"패널 테스트2");
    UIPanelTest3->AddUITexture();
    UIPanelTest3->SetUIAreaRect(150.f, 150.f);
    UIPanelTest3->LoadUITexture(L"../Resource/icon/Effect_Prophecy.png", L"Effect_Prophecy");
    UIPanelTest3->GetUITransform()->SetPosition({ 200.f, 0.f });
    UIPanelTest3->ReservePanelOnEvent(L"UI_PANEL_TEST_ON");
    UIPanelTest3->ReservePanelOutEvent(L"UI_PANEL_TEST_OUT");
    UIPanelTest3->SetPanelOffset(200.f, 0.f);

    UIPanelTest4 = new Panel(L"패널 팝업 테스트2");
    UIPanelTest4->AddUITexture();
    UIPanelTest4->SetUIAreaRect(150.f, 150.f);
    UIPanelTest4->LoadUITexture(L"../Resource/MINI_POPUP_TEST.png", L"MINI_POPUP_TEST");
    UIPanelTest4->GetUITransform()->SetPosition({ 0.f, 0.f });
    UIPanelTest4->SetAble(false);

    UIPopUpTest = new UI(L"팝업 테스트");
    UIPopUpTest->AddUITexture();
    UIPopUpTest->SetUIAreaRect(1797.f, 799.f);
    UIPopUpTest->LoadUITexture(L"../Resource/UI/UI_POPUP_Body.png", L"UI_POPUP_Body");
    UIPopUpTest->GetUITransform()->SetPosition({ 0.f, 0.f });
    UIPopUpTest->SetAble(false);

    UIPopUpButtonTest = new Button(L"팝업 테스트 버튼");
    UIPopUpButtonTest->AddUITexture();
    UIPopUpButtonTest->SetUIAreaRect(856.f, 73.f);
    UIPopUpButtonTest->LoadUITexture(L"../Resource/UI/UI_POPUP_Button.png", L"UI_POPUP_Button");
    UIPopUpButtonTest->GetUITransform()->SetPosition({ 0.f, -300.f });
    UIPopUpButtonTest->ReserveButtonClickEvent(L"UI_POPUP_BUTTON_TEST_ON");
    UIPopUpButtonTest->SetAble(false);

    ///UI 상태이상 Icon Test
    TestIconManager->ModifyState(State::QUICK, 400);
    TestIconManager->ModifyState(State::DISRUPTION, 3);
    TestIconManager->ModifyState(State::CONFUSION, 2);
    TestIconManager->ModifyState(State::ENGINE_OVERLOAD, 2);

    UIIconPopUp = new UI(L"아이콘 패널");
    UIIconPopUp->AddUITexture();
    UIIconPopUp->LoadUITexture(L"../Resource/MINI_POPUP_TEST.png", L"MINI_POPUP_TEST");
    UIIconPopUp->SetAble(false);

    ///Hp Bar
    m_HpBar = new GameObject(L"플레이어 체력 바");
    m_HpBar->AddComponent<Transform>();
    //m_HpBar->GetComponent<Transform>()->SetPosition({ -715.f, -382.5f });
    m_HpBar->GetComponent<Transform>()->SetPosition({ 0.f, -200.f });
    m_HpBar->GetComponent<Transform>()->SetScale({ 1.0f, 1.0f });
    m_HpBar->AddComponent<HpRenderer>();
    m_HpBar->GetComponent<HpRenderer>()->LoadTexture(HpType::MIDDLE);


    ///Mouse
    m_MouseObj = new Mouse(L"마우스");
    


    ///Object
    Scene::EventCreateOBJ(m_BgObj);
    Scene::EventCreateOBJ(m_CameraObj);
    Scene::EventCreateOBJ(m_IdleObj);
    Scene::EventCreateOBJ(m_MouseObj);

    ///UI
    Scene::EventCreateOBJ(UIUpperSector);
    Scene::EventCreateOBJ(UIUpperIconLogo);
    Scene::EventCreateOBJ(UIUpperIconHP);
    Scene::EventCreateOBJ(UIUpperHPText);
    Scene::EventCreateOBJ(UIUpperIconNowFloor);
    Scene::EventCreateOBJ(UIUpperFloorText);
    Scene::EventCreateOBJ(UIUpperTutorial);
    Scene::EventCreateOBJ(UIUpperFdeck);
    Scene::EventCreateOBJ(UIUpperPdeck);
    Scene::EventCreateOBJ(UIUpperExit);

    Scene::EventCreateOBJ(UIFutureTerritory);
    Scene::EventCreateOBJ(UIHPProgressBar);
    Scene::EventCreateOBJ(UIPlayerDefense);

    Scene::EventCreateOBJ(UILowerIconEnergy);
    Scene::EventCreateOBJ(UILowerIconOverload);
    Scene::EventCreateOBJ(UILowerIconPdeck);
    Scene::EventCreateOBJ(UILowerIconFdeck);
    Scene::EventCreateOBJ(UILowerIconPgrave);
    Scene::EventCreateOBJ(UILowerIconFgrave);

    Scene::EventCreateOBJ(UIPanelTest);
    Scene::EventCreateOBJ(UIPanelTest2);

    Scene::EventCreateOBJ(UIPanelTest3);
    Scene::EventCreateOBJ(UIPanelTest4);

    Scene::EventCreateOBJ(UIPopUpTest);
    Scene::EventCreateOBJ(UIPopUpButtonTest);

    Scene::EventCreateOBJ(UIIconPopUp);

    Scene::EventCreateOBJ(m_HpBar);


}

void TestBattleScene::Exit()
{
    //SAFE_DELETE(TestIconManager)
    Scene::Exit();
}

void TestBattleScene::Update(const float& deltaTime)
{
    Scene::Update(deltaTime);

    MouseCollisionSystem::GetInstance()->Update(deltaTime);

    // Translation
    if (InputSystem::GetInstance()->IsKeyHold(VK_RIGHT))
    {
        m_CameraObj->GetComponent<Transform>()->SetPosition({ m_CameraObj->GetComponent<Transform>()->GetPosition().x + 10, m_CameraObj->GetComponent<Transform>()->GetPosition().y });
    }

    if (InputSystem::GetInstance()->IsKeyHold(VK_LEFT))
    {
        m_CameraObj->GetComponent<Transform>()->SetPosition({ m_CameraObj->GetComponent<Transform>()->GetPosition().x - 10, m_CameraObj->GetComponent<Transform>()->GetPosition().y });
    }

    if (InputSystem::GetInstance()->IsKeyHold(VK_DOWN))
    {
        m_CameraObj->GetComponent<Transform>()->SetPosition({ m_CameraObj->GetComponent<Transform>()->GetPosition().x, m_CameraObj->GetComponent<Transform>()->GetPosition().y - 10 });
    }

    if (InputSystem::GetInstance()->IsKeyHold(VK_UP))
    {
        m_CameraObj->GetComponent<Transform>()->SetPosition({ m_CameraObj->GetComponent<Transform>()->GetPosition().x, m_CameraObj->GetComponent<Transform>()->GetPosition().y + 10 });
    }

    if (InputSystem::GetInstance()->IsKeyDown('1'))
    {
        TestIconManager->ModifyState(State::QUICK, 0);
    }

    if (InputSystem::GetInstance()->IsKeyDown('2'))
    {
        TestIconManager->ModifyState(State::DISRUPTION, 0);
    }

    static int curhp = 100;

    if (InputSystem::GetInstance()->IsKeyDown('3'))
    {
        curhp-=10;
        if (curhp < 0)
            curhp = 0;
        m_HpBar->GetComponent<HpRenderer>()->ModifyHpBar(100, curhp, 50);
    }

    if (InputSystem::GetInstance()->IsKeyDown('4'))
    {
        curhp+=10;
        if (curhp > 100)
            curhp = 100;
        m_HpBar->GetComponent<HpRenderer>()->ModifyHpBar(100, curhp, 50);
    }
}

void TestBattleScene::FixedUpdate(const float& deltaTime)
{
    Scene::FixedUpdate(deltaTime);
}

void TestBattleScene::LateUpdate(const float& deltaTime)
{
    Scene::LateUpdate(deltaTime);
}

void TestBattleScene::Render(McCol::D2DRender* renderer)
{
    Scene::Render(renderer);
}

void TestBattleScene::UpperTutorialOn(std::any any)
{
    DEBUGPRINT("UpperTutorialOn\n");
}

void TestBattleScene::UpperFdeckOn(std::any any)
{
    DEBUGPRINT("UpperFdeckOn\n");
}

void TestBattleScene::UpperPdeckOn(std::any any)
{
    DEBUGPRINT("UpperPdeckOn\n");
}

void TestBattleScene::UpperExitOn(std::any any)
{
    DEBUGPRINT("UpperExitOn\n");
}

void TestBattleScene::LowerPdeckOn(std::any any)
{
    DEBUGPRINT("LowerPdeckOn\n");
}

void TestBattleScene::LowerFdeckOn(std::any any)
{
    DEBUGPRINT("LowerFdeckOn\n");
}

void TestBattleScene::LowerPgraveOn(std::any any)
{
    DEBUGPRINT("LowerPgraveOn\n");
}

void TestBattleScene::LowerFgraveOn(std::any any)
{
    DEBUGPRINT("LowerFgraveOn\n");
}

void TestBattleScene::PanelTestOn(std::any any)
{
    // UI Panel On 예시
    DEBUGPRINT("PanelTestOn\n");

    auto panelInfo = std::any_cast<PanelInfo>(any);

    if (panelInfo.Panel == UIPanelTest)
    {
        UIPanelTest2->GetUITexture()->SetOffset({ panelInfo.Panel->GetUITransform()->GetPosition().x + panelInfo.OffsetX,  panelInfo.Panel->GetUITransform()->GetPosition().y + panelInfo.OffsetY });
        UIPanelTest2->SetAble(true);
    }

    if (panelInfo.Panel == UIPanelTest3)
    {
        UIPanelTest4->GetUITexture()->SetOffset({ panelInfo.Panel->GetUITransform()->GetPosition().x + panelInfo.OffsetX,  panelInfo.Panel->GetUITransform()->GetPosition().y + panelInfo.OffsetY });
        UIPanelTest4->SetAble(true);
    }
}

void TestBattleScene::PanelTestOut(std::any any)
{
    // UI Panel Out 예시
    DEBUGPRINT("PanelTestOut\n");

    auto panelInfo = std::any_cast<Panel*>(any);

    if (panelInfo == UIPanelTest)
    {
        UIPanelTest2->SetAble(false);
    }

    if (panelInfo == UIPanelTest3)
    {
        UIPanelTest4->SetAble(false);
    }
}

void TestBattleScene::PopUpTestOn(std::any any)
{
    // UI Interactable Out 예시
    DEBUGPRINT("PopUpTestOn\n");

    UIPopUpTest->SetAble(false);
    UIPopUpButtonTest->SetAble(false);
    McCol::EventSystem::GetInstance()->PublishEvent(L"UI_INTERACTIVE_TRUE", nullptr);
}

void TestBattleScene::IconTestOn(std::any any)
{
    // UI Icon On 예시
    DEBUGPRINT("IconTestOn\n");

    auto iconInfo = std::any_cast<IconInfo>(any);

    //switch(iconInfo.StateIcon)
    //{
    //    case 
    //}

    UIIconPopUp->GetUITransform()->SetPosition({ iconInfo.StateIcon->GetUITransform()->GetPosition().x + iconInfo.OffsetX + 150.5f, iconInfo.StateIcon->GetUITransform()->GetPosition().y });
    switch (iconInfo.PlayerState)
    {
    case State::QUICK:
    {
        UIIconPopUp->GetUITexture()->LoadTexture(L"../Resource/MiniPopupGuide/UI_MiniPOPUP_CC_Agillity.png", L"UI_MiniPOPUP_CC_Agillity");
        UIIconPopUp->SetAble(true);
        break;
    }
    case State::DISRUPTION:
    {
        UIIconPopUp->GetUITexture()->LoadTexture(L"../Resource/MiniPopupGuide/UI_MiniPOPUP_Falling.png", L"UI_MiniPOPUP_Falling");
        UIIconPopUp->SetAble(true);
        break;
    }
    case State::CONFUSION:
    {
        UIIconPopUp->GetUITexture()->LoadTexture(L"../Resource/MiniPopupGuide/UI_MiniPOPUP_Confuse.png", L"UI_MiniPOPUP_Confuse");
        UIIconPopUp->SetAble(true);
        break;
    }
    case State::ENCHANTMENT:
    {
        UIIconPopUp->GetUITexture()->LoadTexture(L"../Resource/MiniPopupGuide/UI_MiniPOPUP__Charge.png", L"UI_MiniPOPUP__Charge");
        UIIconPopUp->SetAble(true);
        break;
    }
    case State::STUNNED:
    {
        UIIconPopUp->GetUITexture()->LoadTexture(L"../Resource/MiniPopupGuide/UI_MiniPOPUP_Stun.png", L"UI_MiniPOPUP_Stun");
        UIIconPopUp->SetAble(true);
        break;
    }
    case State::IMPENDING_RUIN:
    {
        UIIconPopUp->GetUITexture()->LoadTexture(L"../Resource/MiniPopupGuide/UI_MiniPOPUP_Pridict.png", L"UI_MiniPOPUP_Pridict");
        UIIconPopUp->SetAble(true);
        break;
    }
    case State::WILL_OF_RUIN:
    {
        UIIconPopUp->GetUITexture()->LoadTexture(L"../Resource/MiniPopupGuide/UI_MiniPOPUP_Will.png", L"UI_MiniPOPUP_Will");
        UIIconPopUp->SetAble(true);
        break;
    }
    case State::ENGINE_OVERLOAD:
    {
        UIIconPopUp->GetUITexture()->LoadTexture(L"../Resource/MiniPopupGuide/UI_MiniPOPUP_Will.png", L"UI_MiniPOPUP_Will");
        UIIconPopUp->SetAble(true);
        break;
    }
    }
}

void TestBattleScene::IconTestOut(std::any any)
{
    // UI Icon Out 예시
    DEBUGPRINT("IconTestOut\n");

    UIIconPopUp->SetAble(false);
}





