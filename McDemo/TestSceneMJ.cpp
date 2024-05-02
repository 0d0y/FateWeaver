#include "TestSceneMJ.h"

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
#include "Mouse.h"

using namespace McCol;

TestSceneMJ::~TestSceneMJ()
{

}

void TestSceneMJ::Enter()
{
	///Background
	m_BgObj = new GameObject(L"배경");
	m_BgObj->AddComponent<TextureRenderer>();
	m_BgObj->AddComponent<Transform>();
	m_BgObj->GetComponent<Transform>()->SetPosition({ 0.f, 0.f });
	m_BgObj->GetComponent<Transform>()->SetScale({ 1.0f, 1.0f });
	m_BgObj->GetComponent<TextureRenderer>()->SetBitmap(D2DTextureSystem::GetInstance()->LoadTexture(L"../Resource/2560X1440.png", L"background"));
	m_BgObj->GetComponent<TextureRenderer>()->SetTextureScale(0.75f);
	m_BgObj->GetComponent<TextureRenderer>()->SetOpacity(1.0f);

	///Animation
	m_DeathObj = new GameObject(L"사람");
	m_DeathObj->AddComponent<Animation>();
	m_DeathObj->AddComponent<Transform>();
	m_DeathObj->GetComponent<Transform>()->SetPosition({ -500.f, 0.f });
	m_DeathObj->GetComponent<Transform>()->SetScale({ 1.0f, 1.0f });
	m_DeathObj->GetComponent<Animation>()->Load(L"../Resource/FW1_Death_x2.png", L"idle");

	std::vector<AnimationClip> IdleClips;
	IdleClips.push_back({ 490.f * 0, 590.f * 0, 490.f * 1, 590.f * 1, FRAME(4) });
	IdleClips.push_back({ 490.f * 0, 590.f * 1, 490.f * 1, 590.f * 2, FRAME(11) });
	IdleClips.push_back({ 490.f * 0, 590.f * 2, 490.f * 1, 590.f * 3, FRAME(4) });
	IdleClips.push_back({ 490.f * 0, 590.f * 3, 490.f * 1, 590.f * 4, FRAME(11) });
	AnimationState animstate = AnimationState(IdleClips);

	m_DeathObj->GetComponent<Animation>()->AddAnimState(L"Death", animstate);
	m_DeathObj->GetComponent<Animation>()->SetAnimState(L"Death");
	m_DeathObj->GetComponent<Animation>()->SetSpeed(1.f);
	m_DeathObj->GetComponent<Animation>()->SetFlip(true);
	m_DeathObj->GetComponent<Animation>()->SetAnimScale(0.5f);
	m_DeathObj->GetComponent<Animation>()->SetAnimScale(0.5f);

    ///Primitive
    m_CameraObj = new GameObject(L"카메라 오브젝트");
    m_CameraObj->AddComponent<PrimitiveRenderer>();
    m_CameraObj->AddComponent<Transform>();
    m_CameraObj->AddComponent<Camera>();
    m_CameraObj->GetComponent<Transform>()->SetPosition({ 0.f, 0.f });
    m_CameraObj->GetComponent<Transform>()->SetScale({ 1.f, 1.f });
    m_CameraObj->GetComponent<PrimitiveRenderer>()->SetPmRectangle(200.f, 200.f);
    m_CameraObj->GetComponent<PrimitiveRenderer>()->SetPmScale(1.0f);
    m_CameraObj->GetComponent<PrimitiveRenderer>()->SetPmBrushColor(D2D1::ColorF::Red);

    ///Battle Scene UI
    m_UIObj = new UI(L"UI 오브젝트");
	m_UIObj->SetUIAreaRect(1920.f, 70.f);
	m_UIObj->LoadUITexture(L"../Resource/UI_POPUP_Button.png", L"UI_POPUP_BUTTON");

    auto UITransform = m_UIObj->GetUITransform();
	UITransform->SetPosition({ 0.f, 300.f });

    auto UIPrimitive = m_UIObj->GetUIPrimitive();
    UIPrimitive->SetPmScale(1.0f);
    UIPrimitive->SetPmBrushColor(D2D1::ColorF::Orange);

    auto UIText = m_UIObj->GetUIText();
    UIText->ShowLayoutRect(true);
    UIText->SetFontName(L"광양햇살체");
    UIText->SetFontWeight(FontWeight::BOLD);
    UIText->SetFontStyle(FontStyle::NORMAL);
    UIText->SetFontSize(24.f);
    UIText->SetFontRange(0, 10);
    UIText->SetSrcText(L"UI 테스트입니다");

	m_ButtonObj = new Button(L"버튼 오브젝트");
	m_ButtonObj->SetUIAreaRect(90.f, 90.f);
	m_ButtonObj->LoadUITexture(L"../Resource/UI_Icon_Pgrave.png", L"UI_Icon_Pgrave");

	auto ButtonTransform = m_ButtonObj->GetUITransform();
	ButtonTransform->SetPosition({ 0.f, 0.f });

	auto ButtonPrimitive = m_ButtonObj->GetUIPrimitive();
	ButtonPrimitive->SetPmScale(1.0f);
	ButtonPrimitive->SetPmBrushColor(D2D1::ColorF::White);

    Scene::EventCreateOBJ(m_BgObj);
    Scene::EventCreateOBJ(m_DeathObj);
    Scene::EventCreateOBJ(m_CameraObj);
    Scene::EventCreateOBJ(m_UIObj);
    Scene::EventCreateOBJ(m_ButtonObj);
}

void TestSceneMJ::Exit()
{
	Scene::Exit();
}

// 민정) DebugPrint용 Time 설정할때 필요한 코드
float debugProgressTime = 0.f;

void TestSceneMJ::Update(const float& deltaTime)
{
	const float debugTime = 1.0f;

    if (debugProgressTime > debugTime)
    {
        debugProgressTime -= debugTime;
        /*DEBUGPRINT("Mouse Pos X : %f / Mouse Pos Y : %f \n", InputSystem::GetInstance()->GetMousePos().x, InputSystem::GetInstance()->GetMousePos().y);*/
    }

	debugProgressTime += deltaTime;

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

	// Scale
	if (InputSystem::GetInstance()->IsKeyHold('Z'))
	{
		m_CameraObj->GetComponent<Transform>()->SetScale({ float(m_CameraObj->GetComponent<Transform>()->GetScale().x + 0.1), float(m_CameraObj->GetComponent<Transform>()->GetScale().y + 0.1) });
	}

	if (InputSystem::GetInstance()->IsKeyHold('C'))
	{
		m_CameraObj->GetComponent<Transform>()->SetScale({ float(m_CameraObj->GetComponent<Transform>()->GetScale().x - 0.1), float(m_CameraObj->GetComponent<Transform>()->GetScale().y - 0.1) });
	}

	// Rotation
	if (InputSystem::GetInstance()->IsKeyHold('R'))
	{
		m_CameraObj->GetComponent<Transform>()->Rotate(1);
	}

	// Fade In Test
	if (InputSystem::GetInstance()->IsKeyHold('I'))
	{
		m_BgObj->GetComponent<TextureRenderer>()->SetFadeIn(1.0f);
	}

	// Fade Out Test
	if (InputSystem::GetInstance()->IsKeyHold('O'))
	{
		m_BgObj->GetComponent<TextureRenderer>()->SetFadeOut(1.0f);
	}

	MouseCollisionSystem::GetInstance()->Update(deltaTime);

	Scene::Update(deltaTime);
}

void TestSceneMJ::FixedUpdate(const float& deltaTime)
{
	Scene::FixedUpdate(deltaTime);
}

void TestSceneMJ::LateUpdate(const float& deltaTime)
{
	Scene::LateUpdate(deltaTime);
}

void TestSceneMJ::Render(McCol::D2DRender* renderer)
{
	Scene::Render(renderer);
}

void TestSceneMJ::Test(std::any any)
{
	DEBUGPRINT("Button Subscribe Down Test \n");
	m_ButtonObj->GetUITexture()->SetBitmap(D2DTextureSystem::GetInstance()->LoadTexture(L"../Resource/UI_Icon_Pdeck.png", L"UI_Icon_Pdeck"));
}

void TestSceneMJ::Test2(std::any any)
{
	DEBUGPRINT("Button Subscribe Up Test \n");
	m_ButtonObj->GetUITexture()->SetBitmap(D2DTextureSystem::GetInstance()->LoadTexture(L"../Resource/UI_Icon_Pgrave.png", L"UI_Icon_Pgrave"));
}
