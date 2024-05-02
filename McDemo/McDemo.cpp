#include "McDemo.h"

#include "TestSceneSH.h"
#include "TestSceneMJ.h"
#include "TestSceneGY.h"
#include "TestBattleScene.h"
#include "TestMain.h"
#include "TestMap.h"
#include "RewardScene.h"

#include "EffectManager.h"
#include "BattleScene.h"

#include "../Engine/SceneSystem.h"
#include "../RenderEngine/D2DTextureSystem.h"
#include "../Engine/Macro.h"

#include "Elements.h"

#include "../Engine/Mengine.h"

using namespace McCol;

McDemo::McDemo()
{
}

McDemo::~McDemo()
{
}

HRESULT McDemo::Initialize(HINSTANCE hInst, const char* appName)
{
	Mengine::Initialize(hInst, appName);

	// EffectManager Init
	m_EffectManager = new EffectManager;
	m_EffectManager->Initialize();

	D2DTextureSystem* TextureSystem = D2DTextureSystem::GetInstance();

	//TestSceneSH* testSH = new TestSceneSH;
	//m_SceneSystem->AddScene(testSH);
	//EventSystem::GetInstance()->PublishEvent(L"CHANGE_SCENE", std::wstring(L"상학이의 테스트 씬"));

    TestMap* testMap = new TestMap;
	m_SceneSystem->AddScene(testMap);
	//EventSystem::GetInstance()->PublishEvent(L"CHANGE_SCENE", std::wstring(L"UI 테스트용 맵 씬"));

	BattleScene* testBattle = new BattleScene;
	m_SceneSystem->AddScene(testBattle);
	//EventSystem::GetInstance()->PublishEvent(L"CHANGE_SCENE", std::wstring(L"Battle Scene"));

	std::vector<CharacterType> typeArrange;
	typeArrange.push_back(CharacterType::PLAYER);
	typeArrange.push_back(CharacterType::WEREWOLF);
	typeArrange.push_back(CharacterType::GOLEM);
	typeArrange.push_back(CharacterType::FANATIC);
	typeArrange.push_back(CharacterType::STALKER);
	EventSystem::GetInstance()->PublishEvent(L"SET_MONSTER", typeArrange);

	//TestBattleScene* testBattleScene = new TestBattleScene;
	//m_SceneSystem->AddScene(testBattleScene);
	//EventSystem::GetInstance()->PublishEvent(L"CHANGE_SCENE", std::wstring(L"UI 테스트용 배틀 씬"));

	TestMain* testMain = new TestMain;
	m_SceneSystem->AddScene(testMain);
	EventSystem::GetInstance()->PublishEvent(L"CHANGE_SCENE", std::wstring(L"UI 테스트용 메인 씬"));

	RewardScene* rewardScene = new RewardScene;
	m_SceneSystem->AddScene(rewardScene);
	//EventSystem::GetInstance()->PublishEvent(L"CHANGE_SCENE", std::wstring(L"Reward Scene"));

	//TestSceneGY* testGY = new TestSceneGY;
	//m_SceneSystem->AddScene(testGY);
	//m_SceneSystem->ChangeScene(L"근영이의 테스트 씬");


	TextureSystem->LoadTexture(L"../Resource/card_illust/사격.png", L"사격");
	TextureSystem->LoadTexture(L"../Resource/card_illust/회피.png", L"회피");
	TextureSystem->LoadTexture(L"../Resource/card_illust/다리걸기.png", L"다리걸기");
	TextureSystem->LoadTexture(L"../Resource/card_illust/난사.png", L"난사");
	TextureSystem->LoadTexture(L"../Resource/card_illust/저격.png", L"저격");
	TextureSystem->LoadTexture(L"../Resource/card_illust/플래쉬뱅.png", L"플래쉬뱅");
	TextureSystem->LoadTexture(L"../Resource/card_illust/피버타임.png", L"피버타임");
	TextureSystem->LoadTexture(L"../Resource/card_illust/빈틈포착.png", L"빈틈포착");
	TextureSystem->LoadTexture(L"../Resource/card_illust/마탄의사수.png", L"마탄의사수");
	TextureSystem->LoadTexture(L"../Resource/card_illust/아케인블래스트.png", L"아케인블래스트");

	TextureSystem->LoadTexture(L"../Resource/card_illust/차가운포옹.png", L"차가운포옹");
	TextureSystem->LoadTexture(L"../Resource/card_illust/깨물기.png", L"깨물기");

	TextureSystem->LoadTexture(L"../Resource/card_illust/야성해방.png", L"야성해방");
	TextureSystem->LoadTexture(L"../Resource/card_illust/무자비.png", L"무자비");
	TextureSystem->LoadTexture(L"../Resource/card_illust/저돌맹진.png", L"저돌맹진");

	TextureSystem->LoadTexture(L"../Resource/card_illust/필연적인공포.png", L"필연적인공포");
	TextureSystem->LoadTexture(L"../Resource/card_illust/끝없는추적.png", L"끝없는추적");

	TextureSystem->LoadTexture(L"../Resource/card_illust/멸망을부르는노래.png", L"멸망을부르는노래");
	TextureSystem->LoadTexture(L"../Resource/card_illust/공허의가호.png", L"공허의가호");
	TextureSystem->LoadTexture(L"../Resource/card_illust/징벌.png", L"징벌");

	TextureSystem->LoadTexture(L"../Resource/card_illust/시간의파동.png", L"시간의파동");
	TextureSystem->LoadTexture(L"../Resource/card_illust/엔진과부하.png", L"엔진과부하");
	TextureSystem->LoadTexture(L"../Resource/card_illust/말살.png", L"말살");
	TextureSystem->LoadTexture(L"../Resource/card_illust/기어체인지.png", L"기어체인지");

	TextureSystem->LoadTexture(L"../Resource/card_illust/간파.png", L"간파");
	TextureSystem->LoadTexture(L"../Resource/card_illust/치명.png", L"치명");
	TextureSystem->LoadTexture(L"../Resource/card_illust/시간가속.png", L"시간가속");
	TextureSystem->LoadTexture(L"../Resource/card_illust/숨을수없는숙명.png", L"숨을수없는숙명");
	TextureSystem->LoadTexture(L"../Resource/card_illust/도플갱어.png", L"도플갱어");
	TextureSystem->LoadTexture(L"../Resource/card_illust/공간팽창.png", L"공간팽창");
	TextureSystem->LoadTexture(L"../Resource/card_illust/스펠브레이크.png", L"스펠브레이크");
	TextureSystem->LoadTexture(L"../Resource/card_illust/초침멈추기.png", L"초침멈추기");
	TextureSystem->LoadTexture(L"../Resource/card_illust/운명절단.png", L"운명절단");
	TextureSystem->LoadTexture(L"../Resource/card_illust/미래예지.png", L"미래예지");
	TextureSystem->LoadTexture(L"../Resource/card_illust/양자얽힘.png", L"양자얽힘");
	TextureSystem->LoadTexture(L"../Resource/card_illust/차원격리.png", L"차원격리");
	TextureSystem->LoadTexture(L"../Resource/card_illust/야바위.png", L"야바위");
	TextureSystem->LoadTexture(L"../Resource/card_illust/시간선붕괴.png", L"시간선붕괴");
	TextureSystem->LoadTexture(L"../Resource/card_illust/세계속이기.png", L"세계속이기");
	TextureSystem->LoadTexture(L"../Resource/card_illust/가능성개화.png", L"가능성개화");
	TextureSystem->LoadTexture(L"../Resource/card_illust/효율증가.png", L"효율증가");
	TextureSystem->LoadTexture(L"../Resource/card_illust/고대의회중시계.png", L"고대의회중시계");
	TextureSystem->LoadTexture(L"../Resource/card_illust/체크메이트.png", L"체크메이트");
	TextureSystem->LoadTexture(L"../Resource/card_illust/파멸의예언.png", L"파멸의예언");
	TextureSystem->LoadTexture(L"../Resource/card_illust/존재확률수정.png", L"존재확률수정");
	TextureSystem->LoadTexture(L"../Resource/card_illust/대혼란.png", L"대혼란");
	TextureSystem->LoadTexture(L"../Resource/card_illust/데자뷰.png", L"데자뷰");
	TextureSystem->LoadTexture(L"../Resource/card_illust/평행세계.png", L"평행세계");

	return S_OK;
}

void McDemo::Finalize()
{
	m_EffectManager->Finalize();
	SAFE_DELETE(m_EffectManager)

	Mengine::Finalize();
}

void McDemo::UpdateAll(const float& deltaTime)
{
	Mengine::UpdateAll(deltaTime);
}

void McDemo::RenderAll()
{
	Mengine::RenderAll();
}

void PlaceInCenterOfScreen(HWND window, DWORD style, DWORD exStyle)
{
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	RECT clientRect;
	GetClientRect(window, &clientRect);

	int clientWidth = clientRect.right - clientRect.left;
	int clientHeight = clientRect.bottom - clientRect.top;

	SetWindowPos(window, NULL,
		screenWidth / 2 - clientWidth / 2,
		screenHeight / 2 - clientHeight / 2,
		clientWidth, clientHeight, 0
	);
}

// 커서 아이콘 변경
//LPCWSTR wideString2 = L"../Resource/FW_Cursor.png";

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC			hdc;
	PAINTSTRUCT ps;

	switch (message)
	{
	case WM_CREATE:
		PlaceInCenterOfScreen(hWnd, WS_OVERLAPPEDWINDOW, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);
		//SetCursor(LoadCursorFromFile(LPCSTR(wideString2)));
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		//DeleteObject(LoadCursorFromFile(LPCSTR(wideString2)));
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}