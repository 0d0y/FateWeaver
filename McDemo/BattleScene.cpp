﻿#include "BattleScene.h"

#include "CardFactory.h"
#include "GameManager.h"
#include "CardTrigger.h"
#include "PlayCard.h"
#include "FateCard.h"
#include "Deck.h"
#include "CardComponentHeader.h"
#include "Future.h"
#include "Hand.h"
#include "Mouse.h"
#include "CardTexture.h"

#include "Player.h"
#include "Zombie.h"
#include "Fanatic.h"
#include "Werewolf.h"
#include "Stalker.h"
#include "Golem.h"
#include "HpRenderer.h"

#include "../RenderEngine/D2DTextureSystem.h"
#include "../Engine/InputSystem.h"

#include "../Engine/Camera.h"
#include "../Engine/Transform.h"
#include "../Engine/Animation.h"
#include "../Engine/TextureRenderer.h"
#include "../Engine/MouseCollisionSystem.h"
#include "../Engine/UI.h"
#include "../Engine/PopUp.h"
#include "../Engine/Button.h"
#include "../Engine/StateIcon.h"
#include "../Engine/SoundSystem.h"

#include "../Engine/Macro.h"

#include "StateIconManager.h"

constexpr int MIN_INDEX = 0;
constexpr int MAX_INDEX = 4;

using namespace McCol;

BattleScene::BattleScene()
	: Scene(L"Battle Scene")
	, m_DelayedTime(0)
	, m_Progress(BattleProgress::DRAW_FATECARD)
	, m_Camera(nullptr)
	, m_PlayerPlayDeck(nullptr)
	, m_PlayerFateDeck(nullptr)
	, m_Future(nullptr)
	, m_Hand(nullptr)
	, m_Mouse(nullptr)
	, m_SelectedCard(nullptr)
	, m_TargetCard(nullptr)

{
	EventSystem::GetInstance()->Subscribe(L"SET_MONSTER", MakeListenerInfo(&BattleScene::SetMonster));

	///UI Upper Button Event
	McCol::EventSystem::GetInstance()->Subscribe(L"B_UI_TUTORIAL_BUTTON_DOWN", MakeListenerInfo(&BattleScene::UpperTutorialOn));
	McCol::EventSystem::GetInstance()->Subscribe(L"B_UI_UPPER_FDECK_BUTTON_DOWN", MakeListenerInfo(&BattleScene::UpperFdeckOn));
	McCol::EventSystem::GetInstance()->Subscribe(L"B_UI_UPPER_PDECK_DOWN", MakeListenerInfo(&BattleScene::UpperPdeckOn));
	McCol::EventSystem::GetInstance()->Subscribe(L"B_UI_UPPER_EXIT_DOWN", MakeListenerInfo(&BattleScene::UpperExitOn));

	///UI Lower Button Event
	McCol::EventSystem::GetInstance()->Subscribe(L"B_UI_LOWER_PDECK_DOWN", MakeListenerInfo(&BattleScene::LowerPdeckOn));
	McCol::EventSystem::GetInstance()->Subscribe(L"B_UI_LOWER_FDECK_DOWN", MakeListenerInfo(&BattleScene::LowerFdeckOn));
	McCol::EventSystem::GetInstance()->Subscribe(L"B_UI_LOWER_PGRAVE_DOWN", MakeListenerInfo(&BattleScene::LowerPgraveOn));
	McCol::EventSystem::GetInstance()->Subscribe(L"B_UI_LOWER_FGRAVE_DOWN", MakeListenerInfo(&BattleScene::LowerFgraveOn));
	McCol::EventSystem::GetInstance()->Subscribe(L"B_UI_LOWER_END_TURN_DOWN", MakeListenerInfo(&BattleScene::LowerEndOfTurnOn));

	///Icon Event
	McCol::EventSystem::GetInstance()->Subscribe(L"B_UI_STATE_ICON_ON", MakeListenerInfo(&BattleScene::StateIconOn));
	McCol::EventSystem::GetInstance()->Subscribe(L"B_UI_STATE_ICON_OUT", MakeListenerInfo(&BattleScene::StateIconOut));

	///Tutorial Popup Event
	McCol::EventSystem::GetInstance()->Subscribe(L"B_UI_TUTORIAL_LEFT_BUTTON_CLICK", MakeListenerInfo(&BattleScene::TutorialLeftButtonOn));
	McCol::EventSystem::GetInstance()->Subscribe(L"B_UI_TUTORIAL_RIGHT_BUTTON_CLICK", MakeListenerInfo(&BattleScene::TutorialRightButtonOn));
	McCol::EventSystem::GetInstance()->Subscribe(L"B_UI_TUTORIAL_BACK_BUTTON_CLICK", MakeListenerInfo(&BattleScene::TutorialBackButtonOn));


	// Character Death Event
	McCol::EventSystem::GetInstance()->Subscribe(L"B_CHARACTER_DEATH", MakeListenerInfo(&BattleScene::MakeDeath));
}

BattleScene::~BattleScene()
{
}

void BattleScene::Enter()
{
	SoundSystem::GetInstance()->Replay("BGM_02");

	m_TurnOff = false;
	m_IsOnMoment = false;
	m_IsStart = true;
	m_IsWin = false;
	m_DelayedTime = 0.0f;

	for (size_t i = 0; i < m_TypeArrange.size(); i++)
	{
		MakeMonster(m_TypeArrange[i], i);

		if (m_TypeArrange[i] == CharacterType::PLAYER)
		{
			m_PlayerFateDeck = new Deck(L"Player Fate Deck", CharacterIndex::PLAYER);
			EventCreateOBJ(m_PlayerFateDeck);

			m_PlayerPlayDeck = new Deck(L"Player Fate Deck", CharacterIndex::PLAYER);
			EventCreateOBJ(m_PlayerPlayDeck);
		}
		else if (m_TypeArrange[i] != CharacterType::NONE)
		{
			Deck* monsterPlayDeck = new Deck(L"Monster PlayDeck", static_cast<CharacterIndex>(i));
			m_MonsterPlayDecks.push_back(monsterPlayDeck);
			EventCreateOBJ(monsterPlayDeck);
		}
	}


	//m_TypeArrange.clear();

	m_Camera = new GameObject(L"Camera");
	m_Camera->AddComponent<Camera>();
	m_Camera->AddComponent<Transform>();
	EventCreateOBJ(m_Camera);

	m_Hand = new Hand(L"Hand Area", this);
	EventCreateOBJ(m_Hand);

	m_Future = new Future;
	EventCreateOBJ(m_Future);

	m_Mouse = new Mouse(L"Mouse");
	Scene::EventCreateOBJ(m_Mouse);

	CardFactory cf;
	//for (size_t i = 0; i < 100; i++)
	//{
	//	m_PlayerFateDeck->AddCard(cf.MakeTestPlayerFateCard());
	//}

	//for (size_t i = 0; i < 100; i++)
	//{
	//	m_PlayerPlayDeck->AddCard(cf.MakeTestPlayerPlayCard());
	//}

	//for (auto md : m_MonsterPlayDecks)
	//{
	//	for (size_t i = 0; i < 20; i++)
	//	{
	//		md->AddCard(cf.MakeTestMonsterPlayCard());
	//	}
	//}

	//플레이어덱 가져오기
	//for (auto card : GameManager::GetInstance()->GetPlayerFateDeck()->GetDeck())
	//{
	//	m_PlayerFateDeck->AddCard(card);
	//}

	//for (auto card : GameManager::GetInstance()->GetPlayerPlayDeck()->GetDeck())
	//{
	//	m_PlayerPlayDeck->AddCard(card);
	//}

	GameManager::GetInstance()->MoveCardsToScene(m_PlayerPlayDeck, m_PlayerFateDeck);

	//패러독스 값으로 초기화
	for (auto fatecard : m_PlayerFateDeck->GetDeck())
	{
		std::vector<CardPartsComponent*> cpcs = fatecard->GetComponents<CardPartsComponent>();
		if (!cpcs.empty())
		{
			for (auto cpc : cpcs)
			{
				cpc->ResetToOriginValue();
			}
		}
		std::vector<CardFuncComponent*> cfcs = fatecard->GetComponents<CardFuncComponent>();
		if (!cfcs.empty())
		{
			for (auto cfc : cfcs)
			{
				cfc->ResetToOriginValue();
			}
		}
	}
	for (auto fatecard : m_PlayerPlayDeck->GetDeck())
	{
		std::vector<CardPartsComponent*> cpcs = fatecard->GetComponents<CardPartsComponent>();
		if (!cpcs.empty())
		{
			for (auto cpc : cpcs)
			{
				cpc->ResetToOriginValue();
			}
		}
		std::vector<CardFuncComponent*> cfcs = fatecard->GetComponents<CardFuncComponent>();
		if (!cfcs.empty())
		{
			for (auto cfc : cfcs)
			{
				cfc->ResetToOriginValue();
			}
		}
	}

	//몹덱 생성
	for (auto md : m_MonsterPlayDecks)
	{
		GameManager::GetInstance()->CreateMonsterDeck(m_CharactersInField[SIZE(md->GetOwnerIndex())]->GetType(), md);
	}

	Player* player = dynamic_cast<Player*>(m_CharactersInField[0]);
	player->SetFateEnergy(3);

	///Background
	m_BgObj = new GameObject(L"배경", Layer::BACKGROUND);

	m_BgObj->AddComponent<Transform>();
	m_BgObj->GetComponent<Transform>()->SetPosition({ 0.f, 0.f });
	m_BgObj->GetComponent<Transform>()->SetScale({ 1.0f, 1.0f });

	m_BgObj->AddComponent<TextureRenderer>();
	m_BgObj->GetComponent<TextureRenderer>()->SetBitmap(D2DTextureSystem::GetInstance()->LoadTexture(L"../Resource/2560X1440.png", L"background"));
	m_BgObj->GetComponent<TextureRenderer>()->SetTextureScale(0.75f);

	///UI Upper
	UIUpperSector = new UI(L"UI 상단바");
	UIUpperSector->SetLayer(Layer::CHARACTER);
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
	UIUpperIconHP->SetLayer(Layer::CHARACTER);
	UIUpperIconHP->SetUIAreaRect(45.f, 40.f);
	UIUpperIconHP->LoadUITexture(L"../Resource/icon/UI_Upper_Icon_HP.png", L"UI_Upper_Icon_HP");
	UIUpperIconHP->GetUITransform()->SetPosition({ -677.5f, 505.f });

	UIUpperHPText = new UI(L"UI 상단바 HP 텍스트");
	UIUpperHPText->AddUIText();
	UIUpperHPText->SetLayer(Layer::CHARACTER);
	UIUpperHPText->SetUIAreaRect(75.f, 19.f);
	auto curHp = GameManager::GetInstance()->GetCurHealth();
	auto maxHp = GameManager::GetInstance()->GetMaxHealth();
	UIUpperHPText->SetUIText(std::to_wstring(curHp) + L" / " + std::to_wstring(maxHp), 18.f, FontWeight::BOLD, D2D1::ColorF::White);
	UIUpperHPText->GetUITransform()->SetPosition({ -597.5f, 505.f });

	//UIUpperIconNowFloor = new UI(L"UI 상단바 층");
	//UIUpperIconNowFloor->AddUITexture();
	//UIUpperIconNowFloor->SetUIAreaRect(55.f, 55.f);
	//UIUpperIconNowFloor->LoadUITexture(L"../Resource/icon/UI_Upper_Icon_NowFloor.png", L"UI_Upper_Icon_NowFloor");
	//UIUpperIconNowFloor->GetUITransform()->SetPosition({ 242.5f, 502.5f });
	//
	//UIUpperFloorText = new UI(L"UI 상단바 층 텍스트");
	//UIUpperFloorText->AddUIText();
	//UIUpperFloorText->SetUIAreaRect(46.f, 25.f);
	//UIUpperFloorText->SetUIText(L"4층", 18.f, FontWeight::BOLD, D2D1::ColorF::White);
	//UIUpperFloorText->GetUITransform()->SetPosition({ 298.f, 502.5f });

	UIUpperTutorial = new Button(L"UI 상단바 튜토리얼");
	UIUpperTutorial->AddUITexture();
	UIUpperTutorial->SetUIAreaRect(55.f, 55.f);
	UIUpperTutorial->LoadUITexture(L"../Resource/icon/UI_Upper_Tutorial.png", L"UI_Upper_Tutorial");
	UIUpperTutorial->GetUITransform()->SetPosition({ 482.5f, 502.5f });
	UIUpperTutorial->ReserveButtonClickEvent(L"B_UI_TUTORIAL_BUTTON_DOWN");
	UIUpperTutorial->SetUIActivate(false);

	UIUpperFdeck = new Button(L"UI 상단바 운명카드 덱");
	UIUpperFdeck->AddUITexture();
	UIUpperFdeck->SetUIAreaRect(65.f, 55.f);
	UIUpperFdeck->LoadUITexture(L"../Resource/icon/UI_Upper_Fdeck.png", L"UI_Upper_Fdeck");
	UIUpperFdeck->GetUITransform()->SetPosition({ 732.5f, 502.5f });
	UIUpperFdeck->ReserveButtonClickEvent(L"B_UI_UPPER_FDECK_BUTTON_DOWN");
	UIUpperFdeck->SetUIActivate(false);

	UIUpperPdeck = new Button(L"UI 상단바 플레이카드 덱");
	UIUpperPdeck->AddUITexture();
	UIUpperPdeck->SetUIAreaRect(65.f, 55.f);
	UIUpperPdeck->LoadUITexture(L"../Resource/icon/UI_Upper_Pdeck.png", L"UI_Upper_Pdeck");
	UIUpperPdeck->GetUITransform()->SetPosition({ 812.5f, 502.5f });
	UIUpperPdeck->ReserveButtonClickEvent(L"B_UI_UPPER_PDECK_DOWN");
	UIUpperPdeck->SetUIActivate(false);

	UIUpperExit = new Button(L"UI 상단바 게임종료");
	UIUpperExit->AddUITexture();
	UIUpperExit->SetUIAreaRect(55.f, 55.f);
	UIUpperExit->LoadUITexture(L"../Resource/icon/UI_Upper_Exit.png", L"UI_Upper_Exit");
	UIUpperExit->GetUITransform()->SetPosition({ 907.5f, 502.5f });
	UIUpperExit->ReserveButtonClickEvent(L"B_UI_UPPER_EXIT_DOWN");
	UIUpperExit->SetUIActivate(false);

	///UI InGame
	//UIFutureTerritory = new UI(L"UI 미래영역");
	//UIFutureTerritory->SetLayer(Layer::CHARACTER);
	//UIFutureTerritory->AddUITexture();
	//UIFutureTerritory->SetUIAreaRect(1327.f, 120.f);
	//UIFutureTerritory->LoadUITexture(L"../Resource/UI/UI_FutureTerritory.png", L"UI_FutureTerritory");
	//UIFutureTerritory->GetUITransform()->SetPosition({ 1.5f, 370.f });

	//UIHPProgressBar = new UI(L"UI 체력 바");
	//UIHPProgressBar->AddUIPrimitive();
	//UIHPProgressBar->SetUIAreaRect(250.f, 15.f);
	//UIHPProgressBar->GetUITransform()->SetPosition({ -515.f, -232.5f });

	/*UIPlayerDefense = new UI(L"UI 방어도 위치");
	UIPlayerDefense->AddUIText();
	UIPlayerDefense->SetUIAreaRect(35.f, 35.f);
	UIPlayerDefense->GetUITransform()->SetPosition({ -647.5f, -232.5f });
	UIPlayerDefense->SetUIText(L"0", 18.f, FontWeight::BOLD, D2D1::ColorF::White);*/

	///UI Lower
	UILowerIconEnergy = new UI(L"UI 에너지 아이콘");
	UILowerIconEnergy->AddUITexture();
	UILowerIconEnergy->AddUIText();
	UILowerIconEnergy->SetUIAreaRect(120.f, 120.f);
	UILowerIconEnergy->LoadUITexture(L"../Resource/icon/UI_Icon_Energy.png", L"UI_Icon_Energy");
	m_PlayerFateEnergy = dynamic_cast<Player*>(m_CharactersInField[SIZE(CharacterIndex::PLAYER)])->GetFateEnergy();
	UILowerIconEnergy->GetUIText()->SetTextAttribute(std::to_wstring(m_PlayerFateEnergy) + L"/3", 40.f, FontWeight::BOLD);
	UILowerIconEnergy->GetUIText()->SetBrushColor(D2D1::ColorF::White);
	UILowerIconEnergy->GetUITransform()->SetPosition({ -770.f, -315.f });

	UILowerIconPdeck = new Button(L"UI 하단 플레이 덱");
	UILowerIconPdeck->AddUITexture();
	UILowerIconPdeck->SetUIAreaRect(90.f, 90.f);
	UILowerIconPdeck->LoadUITexture(L"../Resource/icon/UI_Icon_Pdeck.png", L"UI_Icon_Pdeck");
	UILowerIconPdeck->GetUITransform()->SetPosition({ -895.f, -360.f });
	UILowerIconPdeck->ReserveButtonClickEvent(L"B_B_UI_LOWER_PDECK_DOWN");

	UILowerIconFdeck = new Button(L"UI 하단 운명 덱");
	UILowerIconFdeck->AddUITexture();
	UILowerIconFdeck->SetUIAreaRect(90.f, 90.f);
	UILowerIconFdeck->LoadUITexture(L"../Resource/icon/UI_Icon_Pdeck.png", L"UI_Icon_Pdeck");
	UILowerIconFdeck->GetUITransform()->SetPosition({ -875.f, -485.f });
	UILowerIconFdeck->ReserveButtonClickEvent(L"B_UI_LOWER_FDECK_DOWN");

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
	UILowerIconPgrave->ReserveButtonClickEvent(L"B_UI_LOWER_PGRAVE_DOWN");

	UILowerIconFgrave = new Button(L"UI 하단 버린 운명 덱");
	UILowerIconFgrave->AddUITexture();
	UILowerIconFgrave->SetUIAreaRect(90.f, 90.f);
	UILowerIconFgrave->LoadUITexture(L"../Resource/icon/UI_Icon_Fgrave.png", L"UI_Icon_Fgrave");
	UILowerIconFgrave->GetUITransform()->SetPosition({ 875.f, -485.f });
	UILowerIconFgrave->ReserveButtonClickEvent(L"B_UI_LOWER_FGRAVE_DOWN");

	UILowerEndOfTurn = new Button(L"UI 하단 턴 종료 버튼");
	//TextureRenderer* tr = UILowerEndOfTurn->AddComponent<TextureRenderer>();
	//tr->Initialize();
	//tr->LoadTexture(L"../Resource/Effect_End.png", L"Effect_End");
	UILowerEndOfTurn->AddUITexture();
	UILowerEndOfTurn->SetUIAreaRect(90.f, 90.f);
	UILowerEndOfTurn->LoadUITexture(L"../Resource/UI/UI_Toggle_01.png", L"UI_Toggle_01");
	UILowerEndOfTurn->GetUITransform()->SetPosition({ 725.f, -295.f });
	UILowerEndOfTurn->ReserveButtonClickEvent(L"B_UI_LOWER_END_TURN_DOWN");

	///UI 상태이상 Icon
	TestIconManager = new StateIconManager();
	//
	//TestIconManager->ModifyState(State::QUICK, 400);
	//TestIconManager->ModifyState(State::DISRUPTION, 3);
	//TestIconManager->ModifyState(State::CONFUSION, 2);
	//TestIconManager->ModifyState(State::ENGINE_OVERLOAD, 2);

	UIStateIconPopUp = new UI(L"아이콘 패널");
	UIStateIconPopUp->AddUITexture();
	UIStateIconPopUp->LoadUITexture(L"../Resource/MINI_POPUP_TEST.png", L"MINI_POPUP_TEST");
	UIStateIconPopUp->SetAble(false);

	// TODO : Chracter랑 연결해줘야함
	///Hp Bar
	//m_HpBar = new GameObject(L"플레이어 체력 바");
	//m_HpBar->AddComponent<Transform>();
	//m_HpBar->GetComponent<Transform>()->SetPosition({ -635.f, -238.5f });
	////m_HpBar->GetComponent<Transform>()->SetPosition({ 0.f, -200.f });
	//m_HpBar->GetComponent<Transform>()->SetScale({ 1.0f, 1.0f });
	//m_HpBar->AddComponent<HpRenderer>();
	//m_HpBar->GetComponent<HpRenderer>()->LoadTexture(HpType::MIDDLE);

	///UI Tutorial PopUp
	UITutorialPopup = new PopUp(L"튜토리얼 팝업");
	UITutorialPopup->AddUITexture();
	UITutorialPopup->GetUITransform()->SetPosition({ 0.f, 0.f });
	UITutorialPopup->LoadUITexture(L"../Resource/Tutorial/Tutorial_Page_01.png", L"Tutorial_Page_01");
	UITutorialPopup->SetAble(false);
	UITutorialPopup->SetTutorialIndex(1);

	UITutorialPageText = new UI(L"튜토리얼 페이지 텍스트");
	UITutorialPageText->AddUIText();
	UITutorialPageText->SetUIAreaRect(90.f, 48.f);
	UITutorialPageText->GetUIText()->SetTextAttribute(L"1/4", 48.f, FontWeight::BOLD);
	UITutorialPageText->GetUIText()->SetBrushColor(D2D1::ColorF::White);
	UITutorialPageText->GetUITransform()->SetPosition({ 0.f, -468.f });
	UITutorialPageText->SetAble(false);

	UITutorialLeftButton = new Button(L"튜토리얼 팝업 왼쪽 화살표");
	UITutorialLeftButton->AddUITexture();
	UITutorialLeftButton->LoadUITexture(L"../Resource/UI/UI_Page_Left.png", L"UI_Page_Left");
	UITutorialLeftButton->GetUITransform()->SetPosition({ -130.f, -469.f });
	UITutorialLeftButton->ReserveButtonClickEvent(L"B_UI_TUTORIAL_LEFT_BUTTON_CLICK");
	UITutorialLeftButton->SetAble(false);

	UITutorialRightButton = new Button(L"튜토리얼 팝업 오른쪽 화살표");
	UITutorialRightButton->AddUITexture();
	UITutorialRightButton->LoadUITexture(L"../Resource/UI/UI_Page_Right.png", L"UI_Page_Right");
	UITutorialRightButton->GetUITransform()->SetPosition({ 130.f, -469.f });
	UITutorialRightButton->ReserveButtonClickEvent(L"B_UI_TUTORIAL_RIGHT_BUTTON_CLICK");
	UITutorialRightButton->SetAble(false);

	UITutorialBackButton = new Button(L"튜토리얼 팝업 뒤로가기 화살표");
	UITutorialBackButton->AddUITexture();
	UITutorialBackButton->LoadUITexture(L"../Resource/UI/UI_Toggle_03.png", L"UI_Toggle_03");
	UITutorialBackButton->GetUITransform()->SetPosition({ 705.f, -475.f });
	UITutorialBackButton->ReserveButtonClickEvent(L"B_UI_TUTORIAL_BACK_BUTTON_CLICK");
	UITutorialBackButton->SetAble(false);

	///Object
	Scene::EventCreateOBJ(m_BgObj);

	///UI
	Scene::EventCreateOBJ(UIUpperSector);
	Scene::EventCreateOBJ(UIUpperIconLogo);
	Scene::EventCreateOBJ(UIUpperIconHP);
	Scene::EventCreateOBJ(UIUpperHPText);
	//Scene::EventCreateOBJ(UIUpperIconNowFloor);
	//Scene::EventCreateOBJ(UIUpperFloorText);
	Scene::EventCreateOBJ(UIUpperTutorial);
	Scene::EventCreateOBJ(UIUpperFdeck);
	Scene::EventCreateOBJ(UIUpperPdeck);
	Scene::EventCreateOBJ(UIUpperExit);

	//Scene::EventCreateOBJ(UIFutureTerritory);
	//Scene::EventCreateOBJ(UIHPProgressBar);
	//Scene::EventCreateOBJ(UIPlayerDefense);

	Scene::EventCreateOBJ(UILowerIconEnergy);
	Scene::EventCreateOBJ(UILowerIconOverload);
	Scene::EventCreateOBJ(UILowerIconPdeck);
	Scene::EventCreateOBJ(UILowerIconFdeck);
	Scene::EventCreateOBJ(UILowerIconPgrave);
	Scene::EventCreateOBJ(UILowerIconFgrave);
	Scene::EventCreateOBJ(UILowerEndOfTurn);

	Scene::EventCreateOBJ(UIStateIconPopUp);

	//Scene::EventCreateOBJ(m_HpBar);

	Scene::EventCreateOBJ(UITutorialPopup);
	Scene::EventCreateOBJ(UITutorialLeftButton);
	Scene::EventCreateOBJ(UITutorialRightButton);
	Scene::EventCreateOBJ(UITutorialBackButton);
	Scene::EventCreateOBJ(UITutorialPageText);

	EffectInfo battleStartEff;
	battleStartEff.Type = EffectType::전투개시;
	EventSystem::GetInstance()->PublishEvent(L"EFFECT", battleStartEff);
}

void BattleScene::Exit()
{
	Scene::Exit();

	m_CharactersInField.clear();
	m_TypeArrange.clear();
	m_LastCardInfo.clear();
	m_CanBeUsedCards.clear();
	m_MonsterPlayDecks.clear();
	m_IsDead.clear();
}


// 몬스터 배치 및 생성
void BattleScene::MakeMonster(CharacterType type, int index)
{
	if (index < MIN_INDEX or index > MAX_INDEX)
		return;

	if (type == CharacterType::NONE)
		return;

	Character* character = nullptr;
	auto defaultSlot = GetIndexPosition(index);

	// todo : character 클래스 변경
	switch (type)
	{
	case CharacterType::PLAYER:
	{
		character = new Player(CharacterIndex::PLAYER);
		defaultSlot.x += 88;
		defaultSlot.y += 110;
		character->GetComponent<Transform>()->SetPosition(defaultSlot);
	}
	break;
	case CharacterType::ZOMBIE:
	{
		character = new Zombie(static_cast<CharacterIndex>(index));
		defaultSlot.y += 130;
		character->GetComponent<Transform>()->SetPosition(defaultSlot);
	}
	break;
	case CharacterType::WEREWOLF:
	{
		character = new Werewolf(static_cast<CharacterIndex>(index));
		defaultSlot.y += 157;
		character->GetComponent<Transform>()->SetPosition(defaultSlot);
	}
	break;
	case CharacterType::STALKER:
	{
		character = new Stalker(static_cast<CharacterIndex>(index));
		defaultSlot.y += 150;
		character->GetComponent<Transform>()->SetPosition(defaultSlot);
	}
	break;
	case CharacterType::FANATIC:
	{
		character = new Fanatic(static_cast<CharacterIndex>(index));
		defaultSlot.y += 138;
		character->GetComponent<Transform>()->SetPosition(defaultSlot);
	}
	break;
	case CharacterType::GOLEM:
	{
		character = new Golem(static_cast<CharacterIndex>(index - 1));
		defaultSlot.x += 55;
		defaultSlot.y += 238;
		character->GetComponent<Transform>()->SetPosition(defaultSlot);
	}
	break;
	}

	m_CharactersInField.push_back(character);

	// 해당 인덱스 캐릭터 생사 여부 표시
	m_IsDead.push_back(false);
	EventCreateOBJ(character);
}

// 몬스터 슬롯 위치
McCol::Vector2 BattleScene::GetIndexPosition(size_t index)
{
	switch (index)
	{
	case 0:
		return { -565,-175 };
	case 1:
		return { 725,-165 };
	case 2:
		return { 475,-215 };
	case 3:
		return { 230,-160 };
	case 4:
		return { -45,-210 };
	default:
		return { -565,-175 };
	}
}

void BattleScene::SetMonster(std::any monsters)
{
	m_TypeArrange = std::any_cast<std::vector<CharacterType>>(monsters);
}

void BattleScene::Update(const float& deltaTime)
{
	Scene::Update(deltaTime);
	if (m_IsWin)
		m_DelayedTime = 10.0f;

	//CheckOnMoment();//찰나
	//CheckOnCarryOver();//이월

	if (UpdateDelayTime(deltaTime))
	{
		switch (m_Progress)
		{
		case BattleProgress::DRAW_FATECARD:
			DrawFateCards();
			break;
		case BattleProgress::DRAW_PLAYCARD:
			DrawPlayCards();
			break;
		case BattleProgress::SHOW_PLAYCARD:
			ShowPlayCards();
			break;
		case BattleProgress::USE_FATECARD:
			UseFateCards();
			break;
		case BattleProgress::SELECT_TARGET_CARD:
			SelectTargetCard();
			break;
		case BattleProgress::DRAW_FUTURE:
			DrawFuture();
			break;
		case BattleProgress::APPLY_PLAYCARD:
			ApplyPlayCard();
			break;
		case BattleProgress::ATTACK_CHRACTER:
			AttackCharacter();
			break;
		default:
			break;
		}
	}

	if (InputSystem::GetInstance()->IsKeyDown('1'))
	{
		EventSystem::GetInstance()->PublishEvent(L"CHANGE_SCENE", std::wstring(L"UI 테스트용 맵 씬"));
	}
	if (InputSystem::GetInstance()->IsKeyDown('2'))
	{
		EventSystem::GetInstance()->PublishEvent(L"CHANGE_SCENE", std::wstring(L"UI 테스트용 메인 씬"));
	}

	// 체력 갱신
	UIUpperHPText->GetUIText()->SetSrcText(std::to_wstring(m_CharactersInField[0]->GetHealth()) + L" / " + std::to_wstring(m_CharactersInField[0]->GetMaxHealth()));
}

void BattleScene::DrawFateCards()
{
	size_t drawCardCount = GameManager::GetInstance()->GetDrawCountPlayer(DeckType::PLAYER_FATE_CARD);
	SoundSystem::GetInstance()->Replay("FX_Draw");

	if (m_Hand->Size() == drawCardCount)
	{
		m_Progress = BattleProgress::DRAW_PLAYCARD;
		return;
	}
	else
	{
		m_DelayedTime = 0.2f; //temp

		//EffectInfo info;
		//info.Type = EffectType::Effect_DrawCard;
		//info.X = InputSystem::GetInstance()->GetMousePos().x; //TODO: 덱 아이콘 좌표로 수정
		//info.Y = InputSystem::GetInstance()->GetMousePos().y;
		//EventSystem::GetInstance()->PublishEvent(L"EFFECT", info);

		m_Hand->AddCard(dynamic_cast<FateCard*>(m_PlayerFateDeck->DrawCard()));
	}
}

void BattleScene::DrawPlayCards()
{
	size_t playerDrawCardCount = GameManager::GetInstance()->GetDrawCountPlayer(DeckType::PLAYER_PLAY_CARD);

	for (size_t i = 0; i < playerDrawCardCount; i++)
	{
		// todo : 카드 없을 경우 예외 처리 필요
		m_Future->AddCard(dynamic_cast<PlayCard*>(m_PlayerPlayDeck->DrawCard()));
	}

	for (auto md : m_MonsterPlayDecks)
	{
		size_t enemyDrawCardCount = GameManager::GetInstance()->GetDrawCountEnemy(m_CharactersInField[SIZE(md->GetOwnerIndex())]->GetType());

		for (size_t i = 0; i < enemyDrawCardCount; i++)
		{
			m_Future->AddCard(dynamic_cast<PlayCard*>(md->DrawCard()));
		}
	}

	m_Future->Sort();
	m_Progress = BattleProgress::SHOW_PLAYCARD;
}

void BattleScene::ShowPlayCards()
{
	m_DelayedTime = 0.2f; //temp
	SoundSystem::GetInstance()->Replay("FX_Draw");

	EffectInfo info;
	info.Type = EffectType::Damaged;
	info.X = InputSystem::GetInstance()->GetMousePos().x; //TODO: 카드의 소유자 인덱스에 있는 캐릭터의 트랜스폼 좌표로 수정
	info.Y = InputSystem::GetInstance()->GetMousePos().y;
	EventSystem::GetInstance()->PublishEvent(L"EFFECT", info);

	if (!m_Future->ShowFrontCard())
	{
		m_Progress = BattleProgress::USE_FATECARD;
	}
}


void BattleScene::UseFateCards()
{
	if (m_IsStart)
	{
		SoundSystem::GetInstance()->Replay("FX_StartTurn");
		EffectInfo startEff;
		startEff.Type = EffectType::차례시작;
		EventSystem::GetInstance()->PublishEvent(L"EFFECT", startEff);
		EventSystem::GetInstance()->PublishEvent(L"TURN_START");

		m_IsStart = false;
		m_DelayedTime = 0.5f;
	}


	if (m_TurnOff && !m_SelectedCard)
	{
		SetHandAndFutureCollidable(false);

		size_t count = m_Hand->Size();
		for (size_t i = 0; i < count; i++)
		{
			m_PlayerFateDeck->AddDisCardDeck(m_Hand->DrawCard());
		}

		m_Progress = BattleProgress::DRAW_FUTURE;
	}
	else if (!m_SelectedCard)
	{
		SetHandAndFutureCollidable(true);
		FateCard* clickedCard = dynamic_cast<FateCard*>(m_Hand->GetClickedCard());

		// 찰나 확인
		if (m_Future->IsMoment() && !m_IsOnMoment)
		{
			m_IsOnMoment = true;
			// 찰나 카드 뽑기 위한 상태 전환
			m_Progress = BattleProgress::DRAW_FUTURE;

			EffectInfo momentEff;
			momentEff.Type = EffectType::즉시발동;
			EventSystem::GetInstance()->PublishEvent(L"EFFECT", momentEff);
			m_DelayedTime = 0.5f;
			return;
		}

		// 이월 확인
		if (auto discardedCard = m_Future->GetCarryOverCard())
		{
			// 버린 카드덱에 넣기
			if (discardedCard->GetCharacterIndex() == 0) // 플레이어 카드일때
			{
				m_PlayerPlayDeck->AddDisCardDeck(discardedCard);
			}
			else   // 몬스터 카드일때
				m_MonsterPlayDecks[discardedCard->GetCharacterIndex() - 1]->AddDisCardDeck(discardedCard);

			EffectInfo momentEff;
			momentEff.Type = EffectType::행동카드제거;
			EventSystem::GetInstance()->PublishEvent(L"EFFECT", momentEff);
		}


		if (clickedCard)
		{
			m_SelectedCard = clickedCard;

			if (!CheckCanBeUsedCard())
			{
				m_SelectedCard = nullptr;
				m_Hand->SetClickedCard(nullptr);
			}
			else
			{
				m_Hand->SetClickedCard(nullptr);
				m_Progress = BattleProgress::SELECT_TARGET_CARD;
			}
		}
	}
	else if (m_SelectedCard)
	{
		m_Progress = BattleProgress::SELECT_TARGET_CARD;
	}
}

bool BattleScene::CheckCanBeUsedCard()
{
	if (m_SelectedCard)
	{
		m_TurnOff = false;
		Player* player = dynamic_cast<Player*>(m_CharactersInField[0]);

		if (static_cast<int>(player->GetFateEnergy()) - static_cast<int>(m_SelectedCard->GetCost()) < 0)
		{
			//코스트 강조 이펙트 or 마나 부족 이펙트
			EffectInfo noEnergyEff;
			noEnergyEff.Type = EffectType::에너지부족;
			noEnergyEff.X = player->GetComponent<Transform>()->GetPosition().x + 230;
			noEnergyEff.Y = player->GetComponent<Transform>()->GetPosition().y + 50;
			EventSystem::GetInstance()->PublishEvent(L"EFFECT", noEnergyEff);
			SoundSystem::GetInstance()->Replay("FX_Fail");

			m_SelectedCard = nullptr;
			m_Hand->SetClickedCard(nullptr);
			return false;
		}

		if (m_SelectedCard->GetName() == L"효율 증가")
		{
			//카드 재생 effect, delay
			int FateEnergy = m_SelectedCard->GetComponent<ValueMod>()->GetValueToModify();
			if (m_SelectedCard->IsParadox())
			{
				player->SetFateEnergy(player->GetFateEnergy() + FateEnergy);
				GameManager::GetInstance()->SetNumberPlayerFateEnengy(GameManager::GetInstance()->GetNumberPlayerFateEnengy() + FateEnergy);
			}
			else
			{
				player->SetFateEnergy(player->GetFateEnergy() + FateEnergy);
			}

			UILowerIconEnergy->GetUIText()->SetSrcText(std::to_wstring(player->GetFateEnergy()) + L"/3");
			//player->SetFateEnergy(player->GetFateEnergy() - m_SelectedCard->GetCost());

			m_Hand->PopCard(m_SelectedCard);
			if (m_SelectedCard->GetComponent<KeywordParts>())
			{
				m_PlayerFateDeck->AddOverLoadDeck(m_SelectedCard);
			}
			else
			{
				m_PlayerFateDeck->AddDisCardDeck(m_SelectedCard);
			}
			return false;
		}

		else if (m_SelectedCard->GetName() == L"초침 멈추기")
		{
			//카드 재생 effect, delay
			for (auto futureDeckCard : m_Future->GetFutureDeckList())
			{
				if (futureDeckCard->GetCardType() == CardType::PLAYER_PLAY_CARD)
				{
					m_CanBeUsedCards.push_back(futureDeckCard);
				}
			}
			for (auto cards : m_CanBeUsedCards)
			{
				m_SelectedCard->Play(cards);
				cards->GetComponent<CardTexture>()->RenewalString();
			}

			player->SetFateEnergy(player->GetFateEnergy() - m_SelectedCard->GetCost());
			m_CanBeUsedCards.clear();
			m_Hand->PopCard(m_SelectedCard);
			if (m_SelectedCard->GetComponent<KeywordParts>())
			{
				m_PlayerFateDeck->AddOverLoadDeck(m_SelectedCard);
			}
			else
			{
				m_PlayerFateDeck->AddDisCardDeck(m_SelectedCard);
			}
			m_Future->Sort();
			return false;
		}
		else if (m_SelectedCard->GetName() == L"야바위")
		{
			for (auto HandDeckCard : m_Hand->GetHandDeckList())
			{
				std::vector<ValueMod*> valueMods = HandDeckCard->GetComponents<ValueMod>();
				if (!valueMods.empty())
				{
					for (auto valueMod : valueMods)
					{
						if (valueMod->GetOperation() == Operation::ADD)
						{
							m_CanBeUsedCards.push_back(HandDeckCard);
						}
					}
				}
			}
		}
		//else if (m_SelectedCard->GetName() == L"새로운 비전")
		//{
		//	for (auto futureDeckCard : m_Future->GetFutureDeckList())
		//	{
		//		std::vector<AttributeParts*> attributeParts = futureDeckCard->GetComponents<AttributeParts>();
		//		if (!attributeParts.empty())
		//		{
		//			for (auto attr : attributeParts)
		//			{
		//				if (attr->GetAttribute() == Attribute::DAMAGE &&
		//					attr->GetDestination() != Destination::SELF)
		//				{
		//					m_CanBeUsedCards.push_back(futureDeckCard);
		//				}
		//			}
		//		}
		//	}
		//}
		else if (m_SelectedCard->GetName() == L"세계 속이기")
		{
			for (auto futureDeckCard : m_Future->GetFutureDeckList())
			{
				std::vector<AttributeParts*> attributeParts = futureDeckCard->GetComponents<AttributeParts>();
				if (!attributeParts.empty())
				{
					for (auto attr : attributeParts)
					{
						if (attr->GetAttribute() == Attribute::DAMAGE)
						{
							m_CanBeUsedCards.push_back(futureDeckCard);
						}
					}
				}
			}
		}
		else if (m_SelectedCard->GetName() == L"고대의 회중시계")
		{
			for (auto HandDeckCard : m_Hand->GetHandDeckList())
			{
				if (!HandDeckCard->IsParadox())
				{
					m_CanBeUsedCards.push_back(HandDeckCard);
				}
			}
		}
		else if (m_SelectedCard->GetName() == L"파멸의 예언")
		{
			for (auto HandDeckCard : m_Hand->GetHandDeckList())
			{
				std::vector<ValueMod*> valueMods = HandDeckCard->GetComponents<ValueMod>();
				if (!valueMods.empty())
				{
					for (auto valueMod : valueMods)
					{
						if (valueMod->GetAttribute() == Attribute::INITIATIVE)
							continue;
						else
							m_CanBeUsedCards.push_back(HandDeckCard);
					}
				}
			}
		}
		else if (m_SelectedCard->GetComponent<DestinationMod>())
		{
			CardType target = m_SelectedCard->GetComponent<DestinationMod>()->GetDestinationTarget();
			Destination dest = m_SelectedCard->GetComponent<DestinationMod>()->GetDestinationToModify();

			for (auto futureDeckCard : m_Future->GetFutureDeckList())
			{
				if (futureDeckCard->GetCardType() == target)
				{
					std::vector<AttributeParts*> attrParts = futureDeckCard->GetAttributes();
					if (!attrParts.empty())
					{
						for (auto attr : attrParts)
						{
							if (attr->GetDestination() != Destination::SELF &&
								attr->GetDestination() != dest)
							{
								m_CanBeUsedCards.push_back(futureDeckCard);
							}
						}
					}
				}
			}
		}
		else if (m_SelectedCard->GetComponent<ValueMod>())
		{
			std::vector<ValueMod*> valueMods = m_SelectedCard->GetComponents<ValueMod>();

			for (auto futureDeckCard : m_Future->GetFutureDeckList())
			{
				std::vector<AttributeParts*> attributeParts = futureDeckCard->GetComponents<AttributeParts>();

				if (!attributeParts.empty())
				{
					for (auto valuemod : valueMods)
					{
						for (auto attr : attributeParts)
						{
							if (valuemod->GetTargetCard() == CardType::PLAY_CARD || futureDeckCard->GetCardType() == valuemod->GetTargetCard())
							{
								if (attr->GetAttribute() == valuemod->GetAttribute())
								{
									m_CanBeUsedCards.push_back(futureDeckCard);
								}

							}
						}
					}
				}
			}
		}
	}

	if (m_CanBeUsedCards.empty())
	{
		//선택한 카드에 대해 적용 될 수 있는 카드 없음
		//대상이 없다는 이펙트
		EffectInfo noTargetEff;
		noTargetEff.Type = EffectType::대상없음;
		noTargetEff.X = m_CharactersInField[0]->GetComponent<Transform>()->GetPosition().x + 230;
		noTargetEff.Y = m_CharactersInField[0]->GetComponent<Transform>()->GetPosition().y + 50;
		EventSystem::GetInstance()->PublishEvent(L"EFFECT", noTargetEff);
		SoundSystem::GetInstance()->Replay("FX_Fail");

		m_SelectedCard = nullptr;
		return false;
	}
	else
	{
		for (auto card : m_CanBeUsedCards)
		{
			m_SelectedCard->GetComponent<CardTexture>()->IsFremeEffect(true, FrameEffectInfo::FRAME_GREEN);
			m_SelectedCard->GetComponent<CardTexture>()->Initialize();
			if (m_SelectedCard->IsParadox())
			{
				card->GetComponent<CardTexture>()->IsFremeEffect(true, FrameEffectInfo::FRAME_RED);
				card->GetComponent<CardTexture>()->Initialize();
			}
			else
			{
				card->GetComponent<CardTexture>()->IsFremeEffect(true, FrameEffectInfo::FRAME_YELLOW);
				card->GetComponent<CardTexture>()->Initialize();
			}
		}
		return true;
	}
}

void BattleScene::CheckOnMoment()
{
	std::list<PlayCard*>& futureDeck = m_Future->GetFutureDeckList();
	if (futureDeck.empty())
		return;

	for (auto card : futureDeck)
	{
		if (card->GetAttribute(Attribute::INITIATIVE)->GetValue() <= 0)
		{
			card->GetAttribute(Attribute::INITIATIVE)->SetValue(0);
			m_IsOnMoment = true;
			m_Progress = BattleProgress::DRAW_FUTURE;
			break;
		}
	}
}

void BattleScene::CheckOnCarryOver()
{
	std::list<PlayCard*>& futureDeck = m_Future->GetFutureDeckList();

	if (futureDeck.empty())
		return;

	for (auto card : futureDeck)
	{
		if (card->GetAttribute(Attribute::INITIATIVE)->GetValue() > 10)
		{
			card->GetAttribute(Attribute::INITIATIVE)->SetValue(10);
			//이월 이펙트 호출

			m_Future->PopCard(card);
			if (card->GetCharacterIndex() == 0) // 플레이어 카드일때
			{
				m_PlayerPlayDeck->AddDisCardDeck(card);
				m_Future->AddCard(dynamic_cast<PlayCard*>(m_PlayerPlayDeck->DrawCard()));
				m_Future->Sort();
			}
			else   // 몬스터 카드일때
			{
				m_MonsterPlayDecks[card->GetCharacterIndex() - 1]->AddDisCardDeck(card);
				m_Future->AddCard(dynamic_cast<PlayCard*>(m_MonsterPlayDecks[card->GetCharacterIndex() - 1]->DrawCard()));
				m_Future->Sort();
			}
		}
	}
}

void BattleScene::SelectTargetCard()
{
	m_Hand->SetIsRenderSelectedCard(true);
	FateCard* clickedCard = m_Hand->GetClickedCard();
	PlayCard* clickedPlayCard = dynamic_cast<PlayCard*>(m_Future->GetClickedCard());
	if (clickedPlayCard)
	{
		if (!m_CanBeUsedCards.empty())
			for (auto card : m_CanBeUsedCards)
			{
				if (card == clickedPlayCard)
				{
					m_TargetCard = clickedPlayCard;
				}
			}
	}
	else
	{
		if (clickedCard)
		{
			if (!m_CanBeUsedCards.empty())
				for (auto card : m_CanBeUsedCards)
				{
					if (card == clickedCard)
					{
						m_TargetCard = clickedCard;
					}
					else
					{
						m_Hand->SetClickedCard(nullptr);
					}
				}
		}
	}

	if (m_TargetCard)
	{
		m_SelectedCard->Play(m_TargetCard);


		Player* player = dynamic_cast<Player*>(m_CharactersInField[0]);
		player->SetFateEnergy(player->GetFateEnergy() - m_SelectedCard->GetCost());
		UILowerIconEnergy->GetUIText()->SetSrcText(std::to_wstring(player->GetFateEnergy()) + L"/3");

		m_TargetCard->GetComponent<CardTexture>()->RenewalString();
		m_TargetCard->GetComponent<CardTexture>()->Initialize();

		//적용 이펙트 호출 & 딜레이

		m_Hand->PopCard(m_SelectedCard);
		if (m_SelectedCard->GetComponent<KeywordParts>())
		{
			m_PlayerFateDeck->AddOverLoadDeck(m_SelectedCard);
		}
		else
		{
			m_PlayerFateDeck->AddDisCardDeck(m_SelectedCard);
		}

		m_SelectedCard->GetComponent<CardTexture>()->IsFremeEffect(false);
		m_SelectedCard->GetComponent<CardTexture>()->Initialize();

		m_SelectedCard = nullptr;
		m_TargetCard = nullptr;

		m_Future->SetClickedCard(nullptr);
		m_Hand->SetClickedCard(nullptr);

		for (auto card : m_CanBeUsedCards)
		{
			card->GetComponent<CardTexture>()->IsFremeEffect(false);
			card->GetComponent<CardTexture>()->Initialize();
		}
		m_Future->Sort();
		m_CanBeUsedCards.clear();
	}

	if (!m_TargetCard && !m_SelectedCard)
	{
		m_Progress = BattleProgress::USE_FATECARD;
	}
}


void BattleScene::SetHandAndFutureCollidable(bool iscollidable)
{
	m_Hand->SetHandCollidable(iscollidable);
	m_Future->SetFutureCollidable(iscollidable);
}

// 미래 영역의 카드를 뽑는 단계
void BattleScene::DrawFuture()
{
	//미래영역 실행 카드 뽑기
	m_ExecutedPlayCard = m_Future->PopFrontCard();
	SoundSystem::GetInstance()->Replay("FX_Playuse");

	// 뽑을 카드 검사
	if (m_ExecutedPlayCard == nullptr)
	{
		m_DelayedTime = 0.1f;
		m_Progress = BattleProgress::DRAW_FATECARD;
		m_IsStart = true;
		m_TurnOff = false;
		return;
	}

	// todo : 카드 뽑는 사운드

	// 카드 정보 및 대상 추출
	m_LastCardInfo = m_ExecutedPlayCard->GetCardInfo();
	int ownerIndex = m_ExecutedPlayCard->GetCharacterIndex();

	// 카드 송신 전 주인 상태 적용
	for (auto& [dest, info] : m_LastCardInfo)
	{
		m_CharactersInField[ownerIndex]->ApplyOwnerState(info);
	}

	m_Progress = BattleProgress::APPLY_PLAYCARD;
}

// 카드의 수치들을 적용하는 단계
void BattleScene::ApplyPlayCard()
{
	EffectInfo playEffect;
	playEffect.Type = EffectType::Damaged;
	playEffect.X = m_ExecutedPlayCard->GetComponent<Transform>()->GetPosition().x;
	playEffect.Y = m_ExecutedPlayCard->GetComponent<Transform>()->GetPosition().y;
	EventSystem::GetInstance()->PublishEvent(L"EFFECT", playEffect);

	for (auto& [dest, info] : m_LastCardInfo)
	{
		switch (dest)
		{
		case Destination::SELF:
		{
			m_CharactersInField[m_ExecutedPlayCard->GetCharacterIndex()]->ApplyCardInfo(info);
			break;
		}
		case Destination::PLAYER:
		{
			m_CharactersInField[0]->ApplyCardInfo(info);
			break;
		}
		case Destination::NEAREST_ENEMY:
		{
			m_CharactersInField[SetCorrectTarget(dest)]->ApplyCardInfo(info);
			break;
		}
		case Destination::FARTHEST_ENEMY:
		{
			m_CharactersInField[SetCorrectTarget(dest)]->ApplyCardInfo(info);
			break;
		}
		case Destination::ALL_ENEMIES:
		{
			for (size_t i = 1; i < m_CharactersInField.size(); i++)
			{
				if (!m_IsDead[i])
					m_CharactersInField[i]->ApplyCardInfo(info);
			}
			break;
		}
		default:
			break;
		}
	}

	// 딜레이
	m_DelayedTime = 0.1f;
	m_Progress = BattleProgress::ATTACK_CHRACTER;
}

// 미래 영역에서 추출된 카드로 캐릭터를 공격하는 단계
void BattleScene::AttackCharacter()
{
	float delaySum = 0.0f;

	for (auto& [dest, info] : m_LastCardInfo)
	{
		auto lastDest = dest;
		if (info.Attributes[SIZE(Attribute::ATTACK_COUNT)] != 0)
		{
			delaySum += info.Attributes[SIZE(Attribute::ATTACK_COUNT)] * 0.5f;
		}
		else
		{
			delaySum = 0.5f;
		}


		switch (dest)
		{
		case Destination::SELF:
		{
			m_CharactersInField[m_ExecutedPlayCard->GetCharacterIndex()]->QueuedDamage(info);
			break;
		}
		case Destination::PLAYER:
		{
			m_CharactersInField[0]->QueuedDamage(info);
			break;
		}
		case Destination::NEAREST_ENEMY:
		{
			m_CharactersInField[SetCorrectTarget(dest)]->QueuedDamage(info);
			break;
		}
		case Destination::FARTHEST_ENEMY:
		{
			m_CharactersInField[SetCorrectTarget(dest)]->QueuedDamage(info);
			break;
		}
		case Destination::ALL_ENEMIES:
		{
			for (size_t i = 1; i < m_CharactersInField.size(); i++)
			{
				if (!m_IsDead[i])
					m_CharactersInField[i]->QueuedDamage(info);
			}
			break;
		}
		default:
			break;
		}
	}

	if (m_ExecutedPlayCard->GetCharacterIndex() == 0) // 플레이어 카드일때
	{
		m_PlayerPlayDeck->AddDisCardDeck(m_ExecutedPlayCard);
	}
	else   // 몬스터 카드일때
		m_MonsterPlayDecks[m_ExecutedPlayCard->GetCharacterIndex() - 1]->AddDisCardDeck(m_ExecutedPlayCard);


	// 찰나로 진입했다면 플레이 상태로 전환
	if (m_IsOnMoment)
	{
		m_IsOnMoment = false;
		m_Progress = BattleProgress::USE_FATECARD;
		return;
	}

	m_DelayedTime = delaySum;
	m_Progress = BattleProgress::DRAW_FUTURE;

}

bool BattleScene::UpdateDelayTime(float deltaTime)
{
	m_DelayedTime -= deltaTime;

	if (m_DelayedTime < 0)
		return true;
	else
		return false;
}

void BattleScene::UpperTutorialOn(std::any any)
{
	// 튜토리얼 버튼 클릭 시 발생하는 이벤트
	DEBUGPRINT("UpperTutorialOn\n");

	// 튜토리얼 팝업으로 이동 / 팝업 노출
	UITutorialPopup->SetAble(true);
	UITutorialLeftButton->SetAble(true);
	UITutorialRightButton->SetAble(true);
	UITutorialBackButton->SetAble(true);
	UITutorialPageText->SetAble(true);

	// 튜토리얼 팝업의 모든 버튼을 터치 가능 상태로 만들고
	UITutorialLeftButton->SetUIActivate(false);
	UITutorialRightButton->SetUIActivate(false);
	UITutorialBackButton->SetUIActivate(false);

	// 다른 UI들은 터치 불가능 상태로 만든다.
	McCol::EventSystem::GetInstance()->PublishEvent(L"UI_INTERACTIVE_FALSE");
}

void BattleScene::UpperFdeckOn(std::any any)
{
	DEBUGPRINT("UpperFdeckOn\n");
}

void BattleScene::UpperPdeckOn(std::any any)
{
	DEBUGPRINT("UpperPdeckOn\n");
}

void BattleScene::UpperExitOn(std::any any)
{
	DEBUGPRINT("메인으로 나가기\n");
	EventSystem::GetInstance()->PublishEvent(L"CHANGE_SCENE", std::wstring(L"UI 테스트용 메인 씬"));
}

void BattleScene::LowerPdeckOn(std::any any)
{
	DEBUGPRINT("LowerPdeckOn\n");
}

void BattleScene::LowerFdeckOn(std::any any)
{
	DEBUGPRINT("LowerFdeckOn\n");
}

void BattleScene::LowerPgraveOn(std::any any)
{
	DEBUGPRINT("LowerPgraveOn\n");
}

void BattleScene::LowerFgraveOn(std::any any)
{
	DEBUGPRINT("LowerFgraveOn\n");
}

void BattleScene::LowerEndOfTurnOn(std::any any)
{
	DEBUGPRINT("LowerEndOfTurnOn : 턴 종료\n");
	auto player = dynamic_cast<Player*>(m_CharactersInField[0]);
	player->SetFateEnergy(3);
	UILowerIconEnergy->GetUIText()->SetSrcText(L"3/3");
	m_TurnOff = true;
}

void BattleScene::StateIconOn(std::any any)
{
	// UI Icon On 예시
	DEBUGPRINT("StateIconOn\n");

	auto iconInfo = std::any_cast<IconInfo>(any);

	UIStateIconPopUp->GetUITransform()->SetPosition({ iconInfo.StateIcon->GetUITransform()->GetPosition().x + iconInfo.OffsetX + 150.5f, iconInfo.StateIcon->GetUITransform()->GetPosition().y });
	switch (iconInfo.PlayerState)
	{
	case State::QUICK:
	{
		UIStateIconPopUp->GetUITexture()->LoadTexture(L"../Resource/MiniPopupGuide/UI_MiniPOPUP_CC_Agillity.png", L"UI_MiniPOPUP_CC_Agillity");
		UIStateIconPopUp->SetAble(true);
		break;
	}
	case State::DISRUPTION:
	{
		UIStateIconPopUp->GetUITexture()->LoadTexture(L"../Resource/MiniPopupGuide/UI_MiniPOPUP_Falling.png", L"UI_MiniPOPUP_Falling");
		UIStateIconPopUp->SetAble(true);
		break;
	}
	case State::CONFUSION:
	{
		UIStateIconPopUp->GetUITexture()->LoadTexture(L"../Resource/MiniPopupGuide/UI_MiniPOPUP_Confuse.png", L"UI_MiniPOPUP_Confuse");
		UIStateIconPopUp->SetAble(true);
		break;
	}
	case State::ENCHANTMENT:
	{
		UIStateIconPopUp->GetUITexture()->LoadTexture(L"../Resource/MiniPopupGuide/UI_MiniPOPUP__Charge.png", L"UI_MiniPOPUP__Charge");
		UIStateIconPopUp->SetAble(true);
		break;
	}
	case State::STUNNED:
	{
		UIStateIconPopUp->GetUITexture()->LoadTexture(L"../Resource/MiniPopupGuide/UI_MiniPOPUP_Stun.png", L"UI_MiniPOPUP_Stun");
		UIStateIconPopUp->SetAble(true);
		break;
	}
	case State::IMPENDING_RUIN:
	{
		UIStateIconPopUp->GetUITexture()->LoadTexture(L"../Resource/MiniPopupGuide/UI_MiniPOPUP_Pridict.png", L"UI_MiniPOPUP_Pridict");
		UIStateIconPopUp->SetAble(true);
		break;
	}
	case State::WILL_OF_RUIN:
	{
		UIStateIconPopUp->GetUITexture()->LoadTexture(L"../Resource/MiniPopupGuide/UI_MiniPOPUP_Will.png", L"UI_MiniPOPUP_Will");
		UIStateIconPopUp->SetAble(true);
		break;
	}
	case State::ENGINE_OVERLOAD:
	{
		UIStateIconPopUp->GetUITexture()->LoadTexture(L"../Resource/MiniPopupGuide/UI_MiniPOPUP_Will.png", L"UI_MiniPOPUP_Will");
		UIStateIconPopUp->SetAble(true);
		break;
	}
	case State::DEFENSE:
	{
		UIStateIconPopUp->GetUITexture()->LoadTexture(L"../Resource/MiniPopupGuide/UI_MiniPOPUP__Shield.png", L"UI_MiniPOPUP__Shield");
		UIStateIconPopUp->SetAble(true);
		break;
	}
	}
}

void BattleScene::StateIconOut(std::any any)
{
	UIStateIconPopUp->SetAble(false);
}

void BattleScene::TutorialLeftButtonOn(std::any any)
{
	// 튜토리얼 팝업에서 왼쪽 버튼 클릭 시 발생하는 이벤트
	DEBUGPRINT("TutorialLeftButtonOn\n");

	ReserveClickCount(m_LeftClickCount);

	switch (m_LeftClickCount)
	{
	case 1:
	{
		UITutorialPopup->GetUITexture()->LoadTexture(L"../Resource/Tutorial/Tutorial_Page_01.png", L"Tutorial_Page_01");
		UITutorialPageText->GetUIText()->SetSrcText(L"1/4");
		break;
	}
	case 2:
	{
		UITutorialPopup->GetUITexture()->LoadTexture(L"../Resource/Tutorial/Tutorial_Page_02.png", L"Tutorial_Page_02");
		UITutorialPageText->GetUIText()->SetSrcText(L"2/4");
		break;
	}
	case 3:
	{
		UITutorialPopup->GetUITexture()->LoadTexture(L"../Resource/Tutorial/Tutorial_Page_03.png", L"Tutorial_Page_03");
		UITutorialPageText->GetUIText()->SetSrcText(L"3/4");
		break;
	}
	case 4:
	{
		UITutorialPopup->GetUITexture()->LoadTexture(L"../Resource/Tutorial/Tutorial_Page_04.png", L"Tutorial_Page_04");
		UITutorialPageText->GetUIText()->SetSrcText(L"4/4");

		break;
	}
	}
}

void BattleScene::TutorialRightButtonOn(std::any any)
{
	// 튜토리얼 팝업에서 오른쪽 버튼 클릭 시 발생하는 이벤트
	DEBUGPRINT("TutorialRightButtonOn\n");

	m_RightClickCount = (m_RightClickCount % 4) + 1;

	switch (m_RightClickCount)
	{
	case 1:
	{
		UITutorialPopup->GetUITexture()->LoadTexture(L"../Resource/Tutorial/Tutorial_Page_01.png", L"Tutorial_Page_01");
		UITutorialPageText->GetUIText()->SetSrcText(L"1/4");
		break;
	}
	case 2:
	{
		UITutorialPopup->GetUITexture()->LoadTexture(L"../Resource/Tutorial/Tutorial_Page_02.png", L"Tutorial_Page_02");
		UITutorialPageText->GetUIText()->SetSrcText(L"2/4");
		break;
	}
	case 3:
	{
		UITutorialPopup->GetUITexture()->LoadTexture(L"../Resource/Tutorial/Tutorial_Page_03.png", L"Tutorial_Page_03");
		UITutorialPageText->GetUIText()->SetSrcText(L"3/4");
		break;
	}
	case 4:
	{
		UITutorialPopup->GetUITexture()->LoadTexture(L"../Resource/Tutorial/Tutorial_Page_04.png", L"Tutorial_Page_04");
		UITutorialPageText->GetUIText()->SetSrcText(L"4/4");
		break;
	}
	}
}

void BattleScene::TutorialBackButtonOn(std::any any)
{
	// 튜토리얼 팝업에서 넘어가기 버튼 클릭 시 발생하는 이벤트
	DEBUGPRINT("TutorialBackButtonOn\n");

	// 튜토리얼 팝업 노출 비활성화
	UITutorialPopup->SetAble(false);
	UITutorialLeftButton->SetAble(false);
	UITutorialRightButton->SetAble(false);
	UITutorialBackButton->SetAble(false);
	UITutorialPageText->SetAble(false);

	// 모든 UI 터치 가능 상태로 만든다.
	McCol::EventSystem::GetInstance()->PublishEvent(L"UI_INTERACTIVE_TRUE", nullptr);
}

void BattleScene::ReserveClickCount(int count)
{
	if (count == 1) {
		m_LeftClickCount = 4;
	}
	else if (count == 4) {
		m_LeftClickCount = 3;
	}
	else if (count == 3) {
		m_LeftClickCount = 2;
	}
	else if (count == 2) {
		m_LeftClickCount = 1;
	}
}


void BattleScene::MakeDeath(std::any index)
{
	auto battleIndex = std::any_cast<CharacterIndex>(index);
	m_IsDead[SIZE(battleIndex)] = true;

	if (m_IsDead[SIZE(CharacterIndex::PLAYER)])
	{
		// 패배
		SoundSystem::GetInstance()->Replay("FX_Death");
		EventSystem::GetInstance()->PublishEvent(L"BATTLE_LOSE", 5.0f);

		m_IsWin = true;
		EffectInfo loseEff;
		loseEff.Type = EffectType::패배;
		EventSystem::GetInstance()->PublishEvent(L"EFFECT", loseEff);
	}

	size_t enemyDeathCount = 0;

	for (size_t i = 1; i < m_IsDead.size(); i++)
	{
		if (m_IsDead[i])
			enemyDeathCount++;
	}

	if (enemyDeathCount == m_IsDead.size() - 1)
	{
		GameManager::GetInstance()->SetCurHealth(m_CharactersInField[0]->GetHealth());
		GameManager::GetInstance()->SetMaxHealth(m_CharactersInField[0]->GetMaxHealth());

		EventSystem::GetInstance()->PublishEvent(L"CHANGE_SCENE", std::wstring(L"UI 테스트용 맵 씬"), 2.0f);
	}
}

size_t BattleScene::SetCorrectTarget(Destination index)
{
	if (index == Destination::NEAREST_ENEMY)
	{
		for (size_t i = 1; i < m_IsDead.size(); i++)
		{
			if (!m_IsDead[i])
				return i;
		}
	}
	if (index == Destination::FARTHEST_ENEMY)
	{
		for (size_t i = m_IsDead.size(); i-- > 1;)
		{
			if (!m_IsDead[i])
				return i;
		}
	}

    return 1;
}