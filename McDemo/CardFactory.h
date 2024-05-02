#pragma once
#include "Elements.h"
#include <vector>
#include <map>

class PlayCard;
class FateCard;
class Card;

class CardFactory
{
private:

	std::map<Rarity, double> fateRarityProbabilities =
	{
		{ Rarity::COMMON, 0.28 },
		{ Rarity::UNCOMMON, 0.315 },
		{ Rarity::RARE, 0.105 },
		{ Rarity::PARADOX_COMMON, 0.12 },
		{ Rarity::PARADOX_UNCOMMON, 0.135 },
		{ Rarity::PARADOX_RARE, 0.045 }
	};

	std::map<Rarity, double> playRarityProbabilities =
	{
		{ Rarity::COMMON, 0.35 },
		{ Rarity::UNCOMMON, 0.50 },
		{ Rarity::RARE, 1.15 }
	};

	std::map<Rarity, std::vector<DefaultPlayCard::PlayerCard>>
		playerPlayCardMap =
	{
		{ Rarity::COMMON,
		{
			DefaultPlayCard::PlayerCard::저격,
		}},
		{ Rarity::UNCOMMON,
		{
			DefaultPlayCard::PlayerCard::플래쉬뱅,
			DefaultPlayCard::PlayerCard::피버타임,
			DefaultPlayCard::PlayerCard::빈틈포착,
		}},
		{ Rarity::RARE,
		{
			DefaultPlayCard::PlayerCard::마탄의사수,
			DefaultPlayCard::PlayerCard::아케인블래스트,
		}}
	};

	std::map<Rarity, std::vector<DefaultFateCard::PlayerCard>>
		playerFateCardMap =
	{
		{ Rarity::COMMON,
		{
			DefaultFateCard::PlayerCard::도플갱어,
			DefaultFateCard::PlayerCard::공간팽창,
			DefaultFateCard::PlayerCard::스펠브레이크,
		}},
		{ Rarity::UNCOMMON,
		{
			DefaultFateCard::PlayerCard::초침멈추기,
			DefaultFateCard::PlayerCard::운명절단,
			DefaultFateCard::PlayerCard::미래예지,
			DefaultFateCard::PlayerCard::양자얽힘,
			DefaultFateCard::PlayerCard::차원격리,
			DefaultFateCard::PlayerCard::야바위,
			DefaultFateCard::PlayerCard::시간선붕괴,
			DefaultFateCard::PlayerCard::세계속이기,
			DefaultFateCard::PlayerCard::가능성개화,
			DefaultFateCard::PlayerCard::효율증가,

		}},
		{ Rarity::RARE,
		{
			DefaultFateCard::PlayerCard::고대의회중시계,
			DefaultFateCard::PlayerCard::체크메이트,
			DefaultFateCard::PlayerCard::파멸의예언,
			DefaultFateCard::PlayerCard::존재확률수정,
			DefaultFateCard::PlayerCard::대혼란,
			DefaultFateCard::PlayerCard::데자뷰,
			DefaultFateCard::PlayerCard::평행세계,
		}},
		{ Rarity::PARADOX_COMMON,
		{
			DefaultFateCard::PlayerCard::도플갱어_패러독스,
			DefaultFateCard::PlayerCard::공간팽창_패러독스,
			DefaultFateCard::PlayerCard::스펠브레이크_패러독스,

		}},
		{ Rarity::PARADOX_UNCOMMON,
		{
			DefaultFateCard::PlayerCard::초침멈추기_패러독스,
			DefaultFateCard::PlayerCard::운명절단_패러독스,
			DefaultFateCard::PlayerCard::미래예지_패러독스,
			DefaultFateCard::PlayerCard::양자얽힘_패러독스,
			DefaultFateCard::PlayerCard::차원격리_패러독스,
			DefaultFateCard::PlayerCard::야바위_패러독스,
			DefaultFateCard::PlayerCard::시간선붕괴_패러독스,
			DefaultFateCard::PlayerCard::세계속이기_패러독스,
			DefaultFateCard::PlayerCard::가능성개화_패러독스,
		}},
		{ Rarity::PARADOX_RARE,
		{
			DefaultFateCard::PlayerCard::고대의회중시계,
			DefaultFateCard::PlayerCard::체크메이트_패러독스,
			DefaultFateCard::PlayerCard::파멸의예언_패러독스,
			DefaultFateCard::PlayerCard::존재확률수정_패러독스,
			DefaultFateCard::PlayerCard::대혼란_패러독스,
			DefaultFateCard::PlayerCard::데자뷰_패러독스,
			DefaultFateCard::PlayerCard::평행세계_패러독스,
		}},
	};

	/*Test*/
	std::vector<DefaultFateCard::PlayerCard>
		playerTestFateCardVector =
	{
			DefaultFateCard::PlayerCard::간파,
			DefaultFateCard::PlayerCard::치명,
			DefaultFateCard::PlayerCard::치명_패러독스,
			DefaultFateCard::PlayerCard::시간가속,
			DefaultFateCard::PlayerCard::숨을수없는숙명,
			DefaultFateCard::PlayerCard::도플갱어,
			DefaultFateCard::PlayerCard::공간팽창,
			DefaultFateCard::PlayerCard::스펠브레이크,
			DefaultFateCard::PlayerCard::초침멈추기,
			DefaultFateCard::PlayerCard::운명절단,
			DefaultFateCard::PlayerCard::미래예지,
			DefaultFateCard::PlayerCard::양자얽힘,
			DefaultFateCard::PlayerCard::차원격리,
			DefaultFateCard::PlayerCard::야바위,
			DefaultFateCard::PlayerCard::시간선붕괴,
			DefaultFateCard::PlayerCard::세계속이기,
			DefaultFateCard::PlayerCard::가능성개화,
			DefaultFateCard::PlayerCard::효율증가,
			DefaultFateCard::PlayerCard::고대의회중시계,
			DefaultFateCard::PlayerCard::체크메이트,
			DefaultFateCard::PlayerCard::파멸의예언,
			DefaultFateCard::PlayerCard::존재확률수정,
			DefaultFateCard::PlayerCard::대혼란,
			DefaultFateCard::PlayerCard::데자뷰,
			DefaultFateCard::PlayerCard::평행세계,
	};

	std::vector<DefaultPlayCard::PlayerCard>
		playerTestPlayCardVector =
	{
			DefaultPlayCard::PlayerCard::사격,
			DefaultPlayCard::PlayerCard::회피,
			DefaultPlayCard::PlayerCard::다리걸기,
			DefaultPlayCard::PlayerCard::난사,
			DefaultPlayCard::PlayerCard::저격,
			DefaultPlayCard::PlayerCard::플래쉬뱅,
			DefaultPlayCard::PlayerCard::피버타임,
			DefaultPlayCard::PlayerCard::빈틈포착,
			DefaultPlayCard::PlayerCard::마탄의사수,
			DefaultPlayCard::PlayerCard::아케인블래스트,
	};

	std::vector<DefaultPlayCard::MonsterCard>
		MonsterTestPlayCardVector =
	{
			DefaultPlayCard::MonsterCard::차가운포옹,
			DefaultPlayCard::MonsterCard::깨물기,
			DefaultPlayCard::MonsterCard::야성해방,
			DefaultPlayCard::MonsterCard::무자비,
			DefaultPlayCard::MonsterCard::저돌맹진,
			DefaultPlayCard::MonsterCard::필연적인공포,
			DefaultPlayCard::MonsterCard::끝없는추적,
			DefaultPlayCard::MonsterCard::저격,
			DefaultPlayCard::MonsterCard::다리걸기,
			DefaultPlayCard::MonsterCard::플래쉬뱅,
			DefaultPlayCard::MonsterCard::멸망을부르는노래,
			DefaultPlayCard::MonsterCard::공허의가호,
			DefaultPlayCard::MonsterCard::징벌,
			DefaultPlayCard::MonsterCard::시공의파동,
			DefaultPlayCard::MonsterCard::엔진과부하,
			DefaultPlayCard::MonsterCard::말살,
			DefaultPlayCard::MonsterCard::기어체인지,
	};
	/*----*/
public:
	PlayCard* CreateCard(DefaultPlayCard::PlayerCard cardName);
	FateCard* CreateCard(DefaultFateCard::PlayerCard cardName);
	PlayCard* CreateCard(DefaultPlayCard::MonsterCard cardName);


public:
	Rarity GetRandomFateRarity();
	Rarity GetRandomPlayRarity();

	PlayCard* MakeRandomPlayCard();
	FateCard* MakeRandomFateCard();

	//test
	PlayCard* MakeTestPlayerPlayCard();
	PlayCard* MakeTestMonsterPlayCard();
	FateCard* MakeTestPlayerFateCard();
	void SetOrigin(Card* card);
};

