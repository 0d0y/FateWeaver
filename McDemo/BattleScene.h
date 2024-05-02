#pragma once
#include "../Engine/Scene.h"

#include "../Engine/Vector2.h"
#include "Elements.h"

#include <thread>
#include <chrono>
#include <future>

namespace McCol
{
	class Camera;
	class UI;
	class Button;
	class Panel;
	class PopUp;
	class StateIcon;
	class EventSystem;
}

enum class BattleProgress
{
	DRAW_FATECARD,
	DRAW_PLAYCARD,
	SHOW_PLAYCARD,
	USE_FATECARD,
	SELECT_TARGET_CARD,
	DRAW_FUTURE,
	APPLY_PLAYCARD,
	ATTACK_CHRACTER,
};

class PlayCard;
class FateCard;
class CardTrigger;
class Card;
class Character;
class Deck;
class Hand;
class Future;
class Mouse;

class StateIconManager;
class HpRenderer;

class BattleScene : public McCol::Scene
{
public:
	BattleScene();
	~BattleScene() override;

private:
	BattleProgress m_Progress;
	float m_DelayedTime;

	McCol::GameObject* m_Camera;
	Mouse* m_Mouse;

	std::vector<Character*> m_CharactersInField;	// 0 : 플레이어, 1 ~ : 몬스터
	std::vector<CharacterType> m_TypeArrange;

	FateCard* m_SelectedCard;

	Card* m_TargetCard;

	/*Card Container*/
	Hand* m_Hand;

	// Future
	Future* m_Future;
	PlayCard* m_ExecutedPlayCard;
	std::map<Destination, CardInfo> m_LastCardInfo;

	bool m_TurnOff = false;
	bool m_IsOnMoment = false;
	bool m_IsStart = true;
	bool m_IsWin = false;

	std::vector<Card*> m_CanBeUsedCards;

	Deck* m_PlayerFateDeck;

	Deck* m_PlayerPlayDeck;

	std::vector<Deck*> m_MonsterPlayDecks;

	McCol::GameObject* m_BgObj;

	///UI
	// UI 상단
	McCol::UI* UIUpperSector;
	McCol::UI* UIUpperIconLogo;
	McCol::UI* UIUpperIconHP;
	McCol::UI* UIUpperHPText;
	//McCol::UI* UIUpperIconNowFloor;
	//McCol::UI* UIUpperFloorText;
	McCol::Button* UIUpperTutorial;
	McCol::Button* UIUpperFdeck;
	McCol::Button* UIUpperPdeck;
	McCol::Button* UIUpperExit;

	// UI 인게임
	//McCol::UI* UIFutureTerritory;
	//McCol::UI* UIHPProgressBar;
	//McCol::UI* UIPlayerDefense;

	// UI 하단
	McCol::UI* UILowerIconEnergy;
	McCol::UI* UILowerIconOverload;
	McCol::Button* UILowerIconPdeck;
	McCol::Button* UILowerIconFdeck;
	McCol::Button* UILowerIconPgrave;
	McCol::Button* UILowerIconFgrave;
	McCol::Button* UILowerEndOfTurn;

	// UI 에너지 텍스트
	int m_PlayerFateEnergy;

	// 상태이상 아이콘 팝업 UI
	McCol::UI* UIStateIconPopUp;

	// 상태이상 아이콘 UI
	StateIconManager* TestIconManager;

	// 체력 바 렌더러
	HpRenderer* m_HpRenderer;
	McCol::GameObject* m_HpBar;

	// 튜토리얼 팝업
	McCol::PopUp* UITutorialPopup;
	McCol::Button* UITutorialLeftButton;
	McCol::Button* UITutorialRightButton;
	McCol::Button* UITutorialBackButton;
	McCol::UI* UITutorialPageText;

	int m_LeftClickCount = 1;
	int m_RightClickCount = 1;


	std::vector<bool> m_IsDead;

public:
	void Enter() override;
	void Exit() override;

	void Update(const float& deltaTime) override;
	FateCard* GetSelectedCard() { return m_SelectedCard; }

private:
	void MakeMonster(CharacterType type, int index);
	McCol::Vector2 GetIndexPosition(size_t index);

	// Event Func
	void SetMonster(std::any monsters);
	//void SetArtifact(std::any artifacts);

	//void DrawPlayCard(std::any count);
	//void DrawFateCard(std::any count);
	//void DrawMonsterCard(std::any count);


	void CheckOnMoment();
	void CheckOnCarryOver();

	/*Battle Progress*/
	void DrawFateCards();
	void DrawPlayCards();
	void ShowPlayCards();

	//Play
	void UseFateCards();
	void SelectTargetCard();
	void CheckAvailableCard();
	bool CheckCanBeUsedCard();
	void SetHandAndFutureCollidable(bool iscollidable);

	//Future
	void DrawFuture();
	void ApplyPlayCard();
	void AttackCharacter();
	//bool CheckExitCondition();

	bool UpdateDelayTime(float t);

	///UI
	// UI 상단바
	void UpperTutorialOn(std::any any);
	void UpperFdeckOn(std::any any);
	void UpperPdeckOn(std::any any);
	void UpperExitOn(std::any any);

	// UI 하단바
	void LowerPdeckOn(std::any any);
	void LowerFdeckOn(std::any any);
	void LowerPgraveOn(std::any any);
	void LowerFgraveOn(std::any any);
	void LowerEndOfTurnOn(std::any any);

	// 상태이상 아이콘 이벤트
	void StateIconOn(std::any any);
	void StateIconOut(std::any any);

	// 튜토리얼 팝업 내 버튼 이벤트
	void TutorialLeftButtonOn(std::any any);
	void TutorialRightButtonOn(std::any any);
	void TutorialBackButtonOn(std::any any);

	void ReserveClickCount(int count);

	// 캐릭터 사망 확인 이벤트
	void MakeDeath(std::any index);

	// 대상 좌표 보정
	size_t SetCorrectTarget(Destination index);
};




// 미래 영역
// 플레이어 플레이 카드 덱 (뽑을, 버릴)
// 몬스터 플레이 카드 덱 (뽑을, 버릴)

// 플레이어 손패
// 플레이어 운명 카드 덱 (뽑을, 버릴)

// 게임 플레이 상황 (게임이 시작하며, 플레이어가 조작이 불가능한 상황)
// 1. 플레이어 플레이 카드 덱, 몬스터 플레이 카드 덱에서 정해진 카드 수를 각각 뽑아서 뽑힌 플레이 카드 포인터 벡터에 담는다
// 2. 뽑힌 카드 포인터 벡터를 미래 영역에 전달한다
// 3. 미래 영역에서 정렬 기준에 맞게 정렬한다
//	3.1. 정렬 기준에 따라 순서대로 렌더링한다 (이건 좀 고생을 해야할 듯)
// 4. 플레이어 운명 카드 덱에서 정해진 카드 수를 뽑아서 뽑힌 운명 카드 포인터 벡터에 담는다
// 5. 뽑힌 카드 포인터 벡터를 손패에 전달한다
// 6. 손패에서 렌더링한다

// 게임 플레이 상황 (모든 카드 배치가 끝나고, 플레이어가 조작이 가능한 상황)
// 1. 손패의 운명 카드 위에 마우스가 올라왔을 때
//	1.1. 해당 카드의 렌더링을 후순위로 미룬 뒤 손패에서 조금 위로 올라오는 모습으로 렌더를 해준다
// 2. 손패의 운명 카드를 클릭했을 때
//	2.1. 해당 운명 카드가 상호작용 가능한 대상들


// 게임 플레이 상황 (턴 종료 버튼을 누른 후, 플레이어가 조작이 불가능한 상황)
// 미래 영역에서 플레이카드를 뽑아왔을 때 가운데로 뿅!