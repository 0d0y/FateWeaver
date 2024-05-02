#include "pch.h"
#include "Mengine.h"

#include "EventSystem.h"
#include "InputSystem.h"
#include "TimeSystem.h"
#include "../RenderEngine/D2DTextureSystem.h"
#include "SceneSystem.h"
#include "SoundSystem.h"
#include "CameraSystem.h"
#include "MouseCollisionSystem.h"
#include "RandomGenerator.h"

extern LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

#ifdef _DEBUG
	#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#endif

McCol::Mengine::Mengine()
	: m_hWnd()
	, m_Msg()
	, m_Renderer(nullptr)
	, m_TimeSystem(nullptr)
	, m_SceneSystem(nullptr)
    , m_IsLoop(true)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtDumpMemoryLeaks();
}

McCol::Mengine::~Mengine()
{
}

// 커서 아이콘 변경
//LPCWSTR wideString = L"../Resource/FW_Cursor.png";

HRESULT McCol::Mengine::Initialize(HINSTANCE hInst, const char* appName)
{
	//m_CustomCursor = LoadCursorFromFile(LPCSTR(wideString));

	/*윈도우 클래스 생성*/
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInst;
	wndclass.hIcon = LoadIcon(hInst, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	//wndclass.hCursor = m_CustomCursor;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = appName;

	/*윈도우 클래스 등록*/
	RegisterClassA(&wndclass);

	/*윈도우 생성*/
	m_hWnd = CreateWindowA(
		appName,
		appName,
		WS_POPUP,
		100, 100, ResolutionWidth, ResolutionHeight,
		NULL, NULL, hInst, NULL);


	if (!m_hWnd) return S_FALSE;

	/*윈도우 화면에 띄우기*/
	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	UpdateWindow(m_hWnd);

	/*시스템 초기화*/

	//Graphics
	m_Renderer = new D2DRender;
	m_Renderer->Initialize(m_hWnd);

	//Time
	m_TimeSystem = new TimeSystem;
	m_TimeSystem->Initialize();

	//Scene
	m_SceneSystem = new SceneSystem;
	m_SceneSystem->Initialize();


	/*싱글톤 시스템 초기화*/

	//Input
	InputSystem::GetInstance()->Initialize();

	//Event
	EventSystem::GetInstance()->Initialize();

	//Texture
	D2DTextureSystem::GetInstance()->Initialize(m_Renderer->GetContext());

	//Sound
	SoundSystem::GetInstance()->Initialize();

	//Camera
	CameraSystem::GetInstance()->Initialize();

	//CollisionSystem

	//RandomGenerator
	RandomGenerator::GetInstance();

	McCol::EventSystem::GetInstance()->Subscribe(L"GAME_EXIT", MakeListenerInfo(&Mengine::EndLoop));

	MouseCollisionSystem::GetInstance()->Initialize();

	return S_OK;
}

void McCol::Mengine::BeginRender()
{
	
	m_Renderer->GetContext()->BeginDraw();
	m_Renderer->GetContext()->Clear(D2D1::ColorF(D2D1::ColorF::Green));
}

void McCol::Mengine::EndRender()
{
	m_Renderer->GetContext()->EndDraw();
	m_Renderer->GetSwapChain()->Present(1, 0);
}

void McCol::Mengine::Loop()
{
	while (m_IsLoop)
	{
		if (PeekMessage(&m_Msg, NULL, 0, 0, PM_REMOVE))
		{
			if (m_Msg.message == WM_QUIT) break;

			DispatchMessage(&m_Msg);
		}
		else
		{
			UpdateAll(m_deltaTime);


			BeginRender();
			RenderAll();
			EndRender();
		}
	}
}

void McCol::Mengine::Finalize()
{
	m_SceneSystem->Finalize();
	SAFE_DELETE(m_SceneSystem)
	m_TimeSystem->Finalize();
	SAFE_DELETE(m_TimeSystem)
	m_Renderer->Finalize();
	SAFE_DELETE(m_Renderer)

	D2DTextureSystem::GetInstance()->Finalize();
	EventSystem::GetInstance()->Finalize();
	InputSystem::GetInstance()->Finalize();
	SoundSystem::GetInstance()->Finalize();
	CameraSystem::GetInstance()->Finalize();
	MouseCollisionSystem::GetInstance()->Finalize();
	RandomGenerator::GetInstance()->Finalize();

	delete this;
}

void McCol::Mengine::UpdateAll(const float& deltaTime)
{
	// System Update
	m_TimeSystem->Update();
	m_deltaTime = m_TimeSystem->GetDeltaTime();

	InputSystem::GetInstance()->Update();
	m_SceneSystem->Update(m_deltaTime);
	SoundSystem::GetInstance()->Update();

	// System FixedUpdate (Physics, Animation)
	m_SceneSystem->FixedUpdate(m_deltaTime);

	// System LateUpdate (Camera, UI, Event)
	MouseCollisionSystem::GetInstance()->Update(m_deltaTime);
	m_SceneSystem->LateUpdate(m_deltaTime);

	EventSystem::GetInstance()->Update(m_deltaTime);
}

void McCol::Mengine::RenderAll()
{
	// System Render
	m_SceneSystem->Render(m_Renderer);
}

void McCol::Mengine::EndLoop(std::any any)
{
	m_IsLoop = false;
}
