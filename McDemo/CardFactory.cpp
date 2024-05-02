#include "CardFactory.h"
#include "CardComponentHeader.h"
#include "Elements.h"
#include "PlayCard.h"
#include "FateCard.h"
#include "Card.h"
#include "CardTexture.h"
#include "../Engine/RandomGenerator.h"


PlayCard* CardFactory::CreateCard(DefaultPlayCard::PlayerCard cardName)
{
	switch (cardName)
	{
	case DefaultPlayCard::PlayerCard::사격:
	{
		PlayCard* card = new PlayCard(L"사격");
		card->GetComponent<CardTexture>()->SetIllustration(L"사격");
		card->InitializePlayCard(Rarity::DEFAULT, CharacterType::PLAYER, CardType::PLAYER_PLAY_CARD);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::INITIATIVE, 5);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::DAMAGE, 5, Destination::NEAREST_ENEMY);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultPlayCard::PlayerCard::회피:
	{
		PlayCard* card = new PlayCard(L"회피");
		card->GetComponent<CardTexture>()->SetIllustration(L"회피");
		card->InitializePlayCard(Rarity::DEFAULT, CharacterType::PLAYER, CardType::PLAYER_PLAY_CARD);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::INITIATIVE, 2);
		card->AddComponent<StateParts>()->InitializeStateParts(State::QUICK, 2, Destination::SELF);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultPlayCard::PlayerCard::다리걸기:
	{
		PlayCard* card = new PlayCard(L"다리 걸기");
		card->GetComponent<CardTexture>()->SetIllustration(L"다리걸기");
		card->InitializePlayCard(Rarity::DEFAULT, CharacterType::PLAYER, CardType::PLAYER_PLAY_CARD);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::INITIATIVE, 2);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::DAMAGE, 2, Destination::NEAREST_ENEMY);
		card->AddComponent<StateParts>()->InitializeStateParts(State::DISRUPTION, 1, Destination::NEAREST_ENEMY);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultPlayCard::PlayerCard::난사:
	{
		PlayCard* card = new PlayCard(L"난사");
		card->GetComponent<CardTexture>()->SetIllustration(L"난사");
		card->InitializePlayCard(Rarity::DEFAULT, CharacterType::PLAYER, CardType::PLAYER_PLAY_CARD);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::INITIATIVE, 4);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::DAMAGE, 4, Destination::NEAREST_ENEMY);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::ATTACK_COUNT, 2, Destination::NEAREST_ENEMY);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultPlayCard::PlayerCard::저격:
	{
		PlayCard* card = new PlayCard(L"저격");
		card->GetComponent<CardTexture>()->SetIllustration(L"저격");
		card->InitializePlayCard(Rarity::COMMON, CharacterType::PLAYER, CardType::PLAYER_PLAY_CARD);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::INITIATIVE, 7);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::DAMAGE, 16, Destination::FARTHEST_ENEMY);
		SetOrigin(card); 
		return card;
	}
	break;
	case DefaultPlayCard::PlayerCard::플래쉬뱅:
	{
		PlayCard* card = new PlayCard(L"플래쉬뱅");
		card->GetComponent<CardTexture>()->SetIllustration(L"플래쉬뱅");
		card->InitializePlayCard(Rarity::UNCOMMON, CharacterType::PLAYER, CardType::PLAYER_PLAY_CARD);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::INITIATIVE, 3);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::DAMAGE, 6, Destination::ALL_ENEMIES);
		card->AddComponent<StateParts>()->InitializeStateParts(State::CONFUSION, 3, Destination::ALL_ENEMIES);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultPlayCard::PlayerCard::피버타임:
	{
		PlayCard* card = new PlayCard(L"피버 타임");
		card->GetComponent<CardTexture>()->SetIllustration(L"피버타임");
		card->InitializePlayCard(Rarity::UNCOMMON, CharacterType::PLAYER, CardType::PLAYER_PLAY_CARD);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::INITIATIVE, 2);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::DAMAGE, 8, Destination::FARTHEST_ENEMY);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::DEFENSE, 8, Destination::SELF);
		SetOrigin(card);

		return card;
	}
	break;
	case DefaultPlayCard::PlayerCard::빈틈포착:
	{
		PlayCard* card = new PlayCard(L"빈틈 포착");
		card->GetComponent<CardTexture>()->SetIllustration(L"빈틈포착");
		card->InitializePlayCard(Rarity::UNCOMMON, CharacterType::PLAYER, CardType::PLAYER_PLAY_CARD);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::INITIATIVE, 4);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::DAMAGE, 6, Destination::FARTHEST_ENEMY);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::ATTACK_COUNT, 2, Destination::FARTHEST_ENEMY);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::DRAW_NUMBER, -9999, Destination::FARTHEST_ENEMY);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultPlayCard::PlayerCard::마탄의사수:
	{
		PlayCard* card = new PlayCard(L"마탄의 사수");
		card->GetComponent<CardTexture>()->SetIllustration(L"마탄의사수");
		card->InitializePlayCard(Rarity::RARE, CharacterType::PLAYER, CardType::PLAYER_PLAY_CARD);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::INITIATIVE, 1);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::DEFENSE, 10, Destination::SELF);
		card->AddComponent<StateParts>()->InitializeStateParts(State::ENCHANTMENT, 3, Destination::SELF);
		SetOrigin(card);

		return card;
	}
	break;
	case DefaultPlayCard::PlayerCard::아케인블래스트:
	{
		PlayCard* card = new PlayCard(L"아케인 블래스트");
		card->GetComponent<CardTexture>()->SetIllustration(L"아케인블래스트");
		card->InitializePlayCard(Rarity::RARE, CharacterType::PLAYER, CardType::PLAYER_PLAY_CARD);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::INITIATIVE, 7);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::DAMAGE, 25, Destination::NEAREST_ENEMY);
		card->AddComponent<StateParts>()->InitializeStateParts(State::DISRUPTION, 2, Destination::NEAREST_ENEMY);
		card->AddComponent<StateParts>()->InitializeStateParts(State::CONFUSION, 2, Destination::NEAREST_ENEMY);
		SetOrigin(card);
		return card;
	}
	break;
	default:
		return nullptr;
	}
}

FateCard* CardFactory::CreateCard(DefaultFateCard::PlayerCard cardName)
{
	switch (cardName)
	{
	case DefaultFateCard::PlayerCard::간파:
	{
		FateCard* card = new FateCard(L"간파");
		card->GetComponent<CardTexture>()->SetIllustration(L"간파");
		card->InitializeFateCard(Rarity::DEFAULT, 1, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::DAMAGE, Operation::SUB, 5, CardType::ENEMY_PLAY_CARD);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::치명:
	{
		FateCard* card = new FateCard(L"치명");
		card->GetComponent<CardTexture>()->SetIllustration(L"치명");
		card->InitializeFateCard(Rarity::DEFAULT, 1, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::DAMAGE, Operation::ADD, 5, CardType::PLAYER_PLAY_CARD);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::치명_패러독스:
	{
		FateCard* card = new FateCard(L"치명");
		card->GetComponent<CardTexture>()->SetIllustration(L"치명");
		card->InitializeFateCard(Rarity::DEFAULT, 1, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::DAMAGE, Operation::ADD, 5, CardType::PLAYER_PLAY_CARD);
		card->SetParadox(true);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::시간가속:
	{
		FateCard* card = new FateCard(L"시간 가속");
		card->GetComponent<CardTexture>()->SetIllustration(L"시간가속");
		card->InitializeFateCard(Rarity::DEFAULT, 1, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::INITIATIVE, Operation::SUB, 2, CardType::PLAY_CARD);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::숨을수없는숙명:
	{
		FateCard* card = new FateCard(L"숨을 수 없는 숙명");
		card->GetComponent<CardTexture>()->SetIllustration(L"숨을수없는숙명");
		card->InitializeFateCard(Rarity::DEFAULT, 1, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<DestinationMod>()->InitializeDestinationMod(CardType::PLAYER_PLAY_CARD, Destination::FARTHEST_ENEMY);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::도플갱어:
	{
		FateCard* card = new FateCard(L"도플갱어");
		card->GetComponent<CardTexture>()->SetIllustration(L"도플갱어");
		card->InitializeFateCard(Rarity::COMMON, 1, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::ATTACK_COUNT, Operation::ADD, 1, CardType::PLAY_CARD);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::공간팽창:
	{
		FateCard* card = new FateCard(L"공간 팽창");
		card->GetComponent<CardTexture>()->SetIllustration(L"공간팽창");
		card->InitializeFateCard(Rarity::COMMON, 1, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::INITIATIVE, Operation::ADD, 2, CardType::PLAY_CARD);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::스펠브레이크:
	{
		FateCard* card = new FateCard(L"스펠 브레이크");
		card->GetComponent<CardTexture>()->SetIllustration(L"스펠브레이크");
		card->InitializeFateCard(Rarity::COMMON, 1, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::DEFENSE, Operation::MUL, 0, CardType::ENEMY_PLAY_CARD);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::초침멈추기:
	{
		FateCard* card = new FateCard(L"초침 멈추기");
		card->GetComponent<CardTexture>()->SetIllustration(L"초침멈추기");
		card->InitializeFateCard(Rarity::UNCOMMON, 2, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<AllValueMod>()->InitializeAllValueMod(Attribute::INITIATIVE, Operation::DIV, 2);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::운명절단:
	{
		FateCard* card = new FateCard(L"운명 절단");
		card->GetComponent<CardTexture>()->SetIllustration(L"운명절단");
		card->InitializeFateCard(Rarity::UNCOMMON, 1, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::INITIATIVE, Operation::SUB, 2, CardType::PLAYER_PLAY_CARD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::DAMAGE, Operation::ADD, 5, CardType::PLAYER_PLAY_CARD);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::미래예지:
	{
		FateCard* card = new FateCard(L"미래 예지");
		card->GetComponent<CardTexture>()->SetIllustration(L"미래예지");
		card->InitializeFateCard(Rarity::UNCOMMON, 1, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::INITIATIVE, Operation::ADD, 2, CardType::ENEMY_PLAY_CARD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::DAMAGE, Operation::SUB, 5, CardType::ENEMY_PLAY_CARD);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::양자얽힘:
	{
		FateCard* card = new FateCard(L"양자 얽힘");
		card->GetComponent<CardTexture>()->SetIllustration(L"양자얽힘");
		card->InitializeFateCard(Rarity::UNCOMMON, 1, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<DestinationMod>()->InitializeDestinationMod(CardType::PLAYER_PLAY_CARD, Destination::ALL_ENEMIES);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::차원격리:
	{
		FateCard* card = new FateCard(L"차원 격리");
		card->GetComponent<CardTexture>()->SetIllustration(L"차원격리");
		card->InitializeFateCard(Rarity::UNCOMMON, 1, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::DEFENSE, Operation::ADD, 10, CardType::PLAYER_PLAY_CARD);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::야바위:
	{
		FateCard* card = new FateCard(L"야바위");
		card->GetComponent<CardTexture>()->SetIllustration(L"야바위");
		card->InitializeFateCard(Rarity::UNCOMMON, 2, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<OperationMod>();
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::시간선붕괴:
	{
		FateCard* card = new FateCard(L"시간선 붕괴");
		card->GetComponent<CardTexture>()->SetIllustration(L"시간선붕괴");
		card->InitializeFateCard(Rarity::UNCOMMON, 2, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::INITIATIVE, Operation::ADD, 5, CardType::ENEMY_PLAY_CARD);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::세계속이기:
	{
		FateCard* card = new FateCard(L"세계 속이기");
		card->GetComponent<CardTexture>()->SetIllustration(L"세계속이기");
		card->InitializeFateCard(Rarity::UNCOMMON, 1, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<TypeMod>()->InitializeTypeMod(Attribute::DAMAGE, Attribute::DEFENSE, CardType::PLAYER_PLAY_CARD);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::가능성개화:
	{
		FateCard* card = new FateCard(L"가능성 개화");
		card->GetComponent<CardTexture>()->SetIllustration(L"가능성개화");
		card->InitializeFateCard(Rarity::UNCOMMON, 2, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<DestinationMod>()->InitializeDestinationMod(CardType::PLAYER_PLAY_CARD, Destination::ALL_ENEMIES);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::DAMAGE, Operation::ADD, 9, CardType::PLAYER_PLAY_CARD);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::효율증가:
	{
		FateCard* card = new FateCard(L"효율 증가");
		card->GetComponent<CardTexture>()->SetIllustration(L"효율증가");
		card->InitializeFateCard(Rarity::UNCOMMON, 0, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::FATE_ENERGY, Operation::ADD, 2, CardType::NONE);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::고대의회중시계:
	{
		FateCard* card = new FateCard(L"고대의 회중시계");
		card->GetComponent<CardTexture>()->SetIllustration(L"고대의회중시계");
		card->InitializeFateCard(Rarity::RARE, 1, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<KeywordParts>()->InitializeKeywordParts(Keyword::OVERLOAD);
		card->AddComponent<ParadoxMod>();
		card->SetParadox(true);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::체크메이트:
	{
		FateCard* card = new FateCard(L"체크메이트");
		card->GetComponent<CardTexture>()->SetIllustration(L"체크메이트");
		card->InitializeFateCard(Rarity::RARE, 3, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::DAMAGE, Operation::MUL, 3, CardType::PLAYER_PLAY_CARD);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::파멸의예언:
	{
		FateCard* card = new FateCard(L"파멸의 예언");
		card->GetComponent<CardTexture>()->SetIllustration(L"파멸의예언");
		card->InitializeFateCard(Rarity::RARE, 2, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<KeywordParts>()->InitializeKeywordParts(Keyword::OVERLOAD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::VALUE, Operation::MUL, 2, CardType::PLAYER_FATE_CARD);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::존재확률수정:
	{
		FateCard* card = new FateCard(L"존재 확률 수정");
		card->GetComponent<CardTexture>()->SetIllustration(L"존재확률수정");
		card->InitializeFateCard(Rarity::RARE, 1, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<KeywordParts>()->InitializeKeywordParts(Keyword::OVERLOAD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::DAMAGE, Operation::MUL, 0, CardType::ENEMY_PLAY_CARD);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::대혼란:
	{
		FateCard* card = new FateCard(L"대혼란");
		card->GetComponent<CardTexture>()->SetIllustration(L"대혼란");
		card->InitializeFateCard(Rarity::RARE, 1, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<DestinationMod>()->InitializeDestinationMod(CardType::ENEMY_PLAY_CARD, Destination::SELF);
		SetOrigin(card);
		return card;
	}
	break;

	case DefaultFateCard::PlayerCard::데자뷰:
	{
		FateCard* card = new FateCard(L"데자뷰");
		card->GetComponent<CardTexture>()->SetIllustration(L"데자뷰");
		card->InitializeFateCard(Rarity::UNCOMMON, 0, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<KeywordParts>()->InitializeKeywordParts(Keyword::OVERLOAD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::INITIATIVE, Operation::SUB, 5, CardType::PLAYER_PLAY_CARD);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::평행세계:
	{
		FateCard* card = new FateCard(L"평행 세계");
		card->GetComponent<CardTexture>()->SetIllustration(L"평행세계");
		card->InitializeFateCard(Rarity::UNCOMMON, 1, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::ATTACK_COUNT, Operation::MUL, 2, CardType::PLAYER_PLAY_CARD);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::도플갱어_패러독스:
	{
		FateCard* card = new FateCard(L"도플갱어");
		card->GetComponent<CardTexture>()->SetIllustration(L"도플갱어");
		card->InitializeFateCard(Rarity::COMMON, 1, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::ATTACK_COUNT, Operation::ADD, 1, CardType::PLAY_CARD);
		card->SetParadox(true);

		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::공간팽창_패러독스:
	{
		FateCard* card = new FateCard(L"공간 팽창");
		card->GetComponent<CardTexture>()->SetIllustration(L"공간팽창");
		card->InitializeFateCard(Rarity::COMMON, 1, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::INITIATIVE, Operation::ADD, 2, CardType::PLAY_CARD);
		card->SetParadox(true);

		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::스펠브레이크_패러독스:
	{
		FateCard* card = new FateCard(L"스펠 브레이크");
		card->GetComponent<CardTexture>()->SetIllustration(L"스펠브레이크");
		card->InitializeFateCard(Rarity::COMMON, 1, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::DEFENSE, Operation::MUL, 0, CardType::ENEMY_PLAY_CARD);
		card->SetParadox(true);

		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::초침멈추기_패러독스:
	{
		FateCard* card = new FateCard(L"초침 멈추기");
		card->GetComponent<CardTexture>()->SetIllustration(L"초침멈추기");
		card->InitializeFateCard(Rarity::UNCOMMON, 2, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<AllValueMod>()->InitializeAllValueMod(Attribute::INITIATIVE, Operation::DIV, 2);
		card->SetParadox(true);

		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::운명절단_패러독스:
	{
		FateCard* card = new FateCard(L"운명 절단");
		card->GetComponent<CardTexture>()->SetIllustration(L"운명절단");
		card->InitializeFateCard(Rarity::UNCOMMON, 1, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::INITIATIVE, Operation::SUB, 2, CardType::PLAYER_PLAY_CARD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::DAMAGE, Operation::ADD, 5, CardType::PLAYER_PLAY_CARD);
		card->SetParadox(true);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::미래예지_패러독스:
	{
		FateCard* card = new FateCard(L"미래 예지");
		card->GetComponent<CardTexture>()->SetIllustration(L"미래예지");
		card->InitializeFateCard(Rarity::UNCOMMON, 1, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::INITIATIVE, Operation::ADD, 2, CardType::ENEMY_PLAY_CARD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::DAMAGE, Operation::SUB, 5, CardType::ENEMY_PLAY_CARD);
		card->SetParadox(true);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::양자얽힘_패러독스:
	{
		FateCard* card = new FateCard(L"양자 얽힘");
		card->GetComponent<CardTexture>()->SetIllustration(L"양자얽힘");
		card->InitializeFateCard(Rarity::UNCOMMON, 1, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<DestinationMod>()->InitializeDestinationMod(CardType::PLAYER_PLAY_CARD, Destination::ALL_ENEMIES);
		card->SetParadox(true);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::차원격리_패러독스:
	{
		FateCard* card = new FateCard(L"차원 격리");
		card->GetComponent<CardTexture>()->SetIllustration(L"차원격리");
		card->InitializeFateCard(Rarity::UNCOMMON, 1, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::DEFENSE, Operation::ADD, 10, CardType::PLAYER_PLAY_CARD);
		card->SetParadox(true);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::야바위_패러독스:
	{
		FateCard* card = new FateCard(L"야바위");
		card->GetComponent<CardTexture>()->SetIllustration(L"야바위");
		card->InitializeFateCard(Rarity::UNCOMMON, 2, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<OperationMod>();
		card->SetParadox(true);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::시간선붕괴_패러독스:
	{
		FateCard* card = new FateCard(L"시간선 붕괴");
		card->GetComponent<CardTexture>()->SetIllustration(L"시간선붕괴");
		card->InitializeFateCard(Rarity::UNCOMMON, 2, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::INITIATIVE, Operation::ADD, 5, CardType::ENEMY_PLAY_CARD);
		card->SetParadox(true);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::세계속이기_패러독스:
	{
		FateCard* card = new FateCard(L"세계 속이기");
		card->GetComponent<CardTexture>()->SetIllustration(L"세계속이기");
		card->InitializeFateCard(Rarity::UNCOMMON, 1, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<TypeMod>()->InitializeTypeMod(Attribute::DAMAGE, Attribute::DEFENSE, CardType::PLAYER_PLAY_CARD);
		card->SetParadox(true);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::가능성개화_패러독스:
	{
		FateCard* card = new FateCard(L"가능성 개화");
		card->GetComponent<CardTexture>()->SetIllustration(L"가능성개화");
		card->InitializeFateCard(Rarity::UNCOMMON, 2, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::DAMAGE, Operation::ADD, 9, CardType::PLAYER_PLAY_CARD);
		card->AddComponent<DestinationMod>()->InitializeDestinationMod(CardType::PLAYER_PLAY_CARD, Destination::ALL_ENEMIES);
		card->SetParadox(true);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::체크메이트_패러독스:
	{
		FateCard* card = new FateCard(L"체크메이트");
		card->GetComponent<CardTexture>()->SetIllustration(L"체크메이트");
		card->InitializeFateCard(Rarity::RARE, 3, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::DAMAGE, Operation::MUL, 3, CardType::PLAYER_PLAY_CARD);
		card->SetParadox(true);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::파멸의예언_패러독스:
	{
		FateCard* card = new FateCard(L"파멸의 예언");
		card->GetComponent<CardTexture>()->SetIllustration(L"파멸의예언");
		card->InitializeFateCard(Rarity::RARE, 2, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<KeywordParts>()->InitializeKeywordParts(Keyword::OVERLOAD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::VALUE, Operation::MUL, 2, CardType::PLAYER_FATE_CARD);
		card->SetParadox(true);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::존재확률수정_패러독스:
	{
		FateCard* card = new FateCard(L"존재 확률 수정");
		card->GetComponent<CardTexture>()->SetIllustration(L"존재확률수정");
		card->InitializeFateCard(Rarity::RARE, 1, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<KeywordParts>()->InitializeKeywordParts(Keyword::OVERLOAD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::DAMAGE, Operation::MUL, 0, CardType::ENEMY_PLAY_CARD);
		card->SetParadox(true);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::대혼란_패러독스:
	{
		FateCard* card = new FateCard(L"대혼란");
		card->GetComponent<CardTexture>()->SetIllustration(L"대혼란");
		card->InitializeFateCard(Rarity::RARE, 1, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<DestinationMod>()->InitializeDestinationMod(CardType::ENEMY_PLAY_CARD, Destination::SELF);
		card->SetParadox(true);
		SetOrigin(card);
		return card;
	}
	break;

	case DefaultFateCard::PlayerCard::데자뷰_패러독스:
	{
		FateCard* card = new FateCard(L"데자뷰");
		card->GetComponent<CardTexture>()->SetIllustration(L"데자뷰");
		card->InitializeFateCard(Rarity::UNCOMMON, 0, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<KeywordParts>()->InitializeKeywordParts(Keyword::OVERLOAD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::INITIATIVE, Operation::SUB, 5, CardType::PLAYER_PLAY_CARD);
		card->SetParadox(true);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultFateCard::PlayerCard::평행세계_패러독스:
	{
		FateCard* card = new FateCard(L"평행 세계");
		card->GetComponent<CardTexture>()->SetIllustration(L"평행세계");
		card->InitializeFateCard(Rarity::UNCOMMON, 1, CharacterType::PLAYER, CardType::PLAYER_FATE_CARD);
		card->AddComponent<ValueMod>()->InitializeValueMod(Attribute::ATTACK_COUNT, Operation::MUL, 2, CardType::PLAYER_PLAY_CARD);
		card->SetParadox(true);
		SetOrigin(card);
		return card;
	}
	break;
	default:
		return nullptr;
		break;
	}
}

PlayCard* CardFactory::CreateCard(DefaultPlayCard::MonsterCard cardName)
{
	switch (cardName)
	{
	case DefaultPlayCard::MonsterCard::차가운포옹:
	{
		PlayCard* card = new PlayCard(L"차가운 포옹");
		card->GetComponent<CardTexture>()->SetIllustration(L"차가운포옹");
		card->InitializePlayCard(Rarity::COMMON, CharacterType::ZOMBIE, CardType::ENEMY_PLAY_CARD);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::INITIATIVE, 3);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::DEFENSE, 5, Destination::SELF);
		card->AddComponent<StateParts>()->InitializeStateParts(State::DISRUPTION, 1, Destination::PLAYER);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultPlayCard::MonsterCard::깨물기:
	{
		PlayCard* card = new PlayCard(L"깨물기");
		card->GetComponent<CardTexture>()->SetIllustration(L"깨물기");
		card->InitializePlayCard(Rarity::COMMON, CharacterType::ZOMBIE, CardType::ENEMY_PLAY_CARD);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::INITIATIVE, 9);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::DAMAGE, 8, Destination::PLAYER);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultPlayCard::MonsterCard::야성해방:
	{
		PlayCard* card = new PlayCard(L"야성 해방");
		card->GetComponent<CardTexture>()->SetIllustration(L"야성해방");
		card->InitializePlayCard(Rarity::COMMON, CharacterType::WEREWOLF, CardType::ENEMY_PLAY_CARD);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::INITIATIVE, 4);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::DEFENSE, 7, Destination::SELF);
		card->AddComponent<StateParts>()->InitializeStateParts(State::ENCHANTMENT, 3, Destination::SELF);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultPlayCard::MonsterCard::무자비:
	{
		PlayCard* card = new PlayCard(L"무자비");
		card->GetComponent<CardTexture>()->SetIllustration(L"무자비");
		card->InitializePlayCard(Rarity::COMMON, CharacterType::WEREWOLF, CardType::ENEMY_PLAY_CARD);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::INITIATIVE, 10);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::DAMAGE, 7, Destination::PLAYER);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::ATTACK_COUNT, 2, Destination::PLAYER);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultPlayCard::MonsterCard::저돌맹진:
	{
		PlayCard* card = new PlayCard(L"저돌맹진");
		card->GetComponent<CardTexture>()->SetIllustration(L"저돌맹진");
		card->InitializePlayCard(Rarity::COMMON, CharacterType::WEREWOLF, CardType::ENEMY_PLAY_CARD);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::INITIATIVE, 4);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::DAMAGE, 13, Destination::PLAYER);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::DEFENSE, 7, Destination::SELF);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultPlayCard::MonsterCard::필연적인공포:
	{
		PlayCard* card = new PlayCard(L"필연적인 공포");
		card->GetComponent<CardTexture>()->SetIllustration(L"필연적인공포");
		card->InitializePlayCard(Rarity::COMMON, CharacterType::STALKER, CardType::ENEMY_PLAY_CARD);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::INITIATIVE, 1);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::DEFENSE, 10, Destination::ALL_ENEMIES);
		card->AddComponent<StateParts>()->InitializeStateParts(State::QUICK, 2, Destination::SELF);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultPlayCard::MonsterCard::끝없는추적:
	{
		PlayCard* card = new PlayCard(L"끝없는 추적");
		card->GetComponent<CardTexture>()->SetIllustration(L"끝없는추적");
		card->InitializePlayCard(Rarity::COMMON, CharacterType::STALKER, CardType::ENEMY_PLAY_CARD);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::INITIATIVE, 1);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::DAMAGE, 10, Destination::PLAYER);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultPlayCard::MonsterCard::저격:
	{
		PlayCard* card = new PlayCard(L"저격");
		card->GetComponent<CardTexture>()->SetIllustration(L"저격");
		card->InitializePlayCard(Rarity::COMMON, CharacterType::STALKER, CardType::ENEMY_PLAY_CARD);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::INITIATIVE, 7);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::DAMAGE, 16, Destination::PLAYER);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultPlayCard::MonsterCard::다리걸기:
	{
		PlayCard* card = new PlayCard(L"다리 걸기");
		card->GetComponent<CardTexture>()->SetIllustration(L"다리걸기");
		card->InitializePlayCard(Rarity::COMMON, CharacterType::STALKER, CardType::ENEMY_PLAY_CARD);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::INITIATIVE, 2);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::DAMAGE, 2, Destination::PLAYER);
		card->AddComponent<StateParts>()->InitializeStateParts(State::DISRUPTION, 1, Destination::PLAYER);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultPlayCard::MonsterCard::플래쉬뱅:
	{
		PlayCard* card = new PlayCard(L"플래쉬뱅");
		card->GetComponent<CardTexture>()->SetIllustration(L"플래쉬뱅");
		card->InitializePlayCard(Rarity::COMMON, CharacterType::STALKER, CardType::ENEMY_PLAY_CARD);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::INITIATIVE, 3);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::DAMAGE, 6, Destination::PLAYER);
		card->AddComponent<StateParts>()->InitializeStateParts(State::CONFUSION, 2, Destination::PLAYER);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultPlayCard::MonsterCard::멸망을부르는노래:
	{
		PlayCard* card = new PlayCard(L"멸망을 부르는 노래");
		card->GetComponent<CardTexture>()->SetIllustration(L"멸망을부르는노래");
		card->InitializePlayCard(Rarity::COMMON, CharacterType::FANATIC, CardType::ENEMY_PLAY_CARD);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::INITIATIVE, 9);
		card->AddComponent<StateParts>()->InitializeStateParts(State::IMPENDING_RUIN, 2, Destination::ALL_ENEMIES);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultPlayCard::MonsterCard::공허의가호:
	{
		PlayCard* card = new PlayCard(L"공허의 가호");
		card->GetComponent<CardTexture>()->SetIllustration(L"공허의가호");
		card->InitializePlayCard(Rarity::COMMON, CharacterType::FANATIC, CardType::ENEMY_PLAY_CARD);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::INITIATIVE, 1);
		card->AddComponent<StateParts>()->InitializeStateParts(State::WILL_OF_RUIN, 10, Destination::ALL_ENEMIES);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultPlayCard::MonsterCard::징벌:
	{
		PlayCard* card = new PlayCard(L"징벌");
		card->GetComponent<CardTexture>()->SetIllustration(L"징벌");
		card->InitializePlayCard(Rarity::COMMON, CharacterType::FANATIC, CardType::ENEMY_PLAY_CARD);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::INITIATIVE, 6);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::DAMAGE, 2, Destination::PLAYER);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::ATTACK_COUNT, 3);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultPlayCard::MonsterCard::시공의파동:
	{
		PlayCard* card = new PlayCard(L"시공의 파동");
		card->GetComponent<CardTexture>()->SetIllustration(L"시간의파동");
		card->InitializePlayCard(Rarity::COMMON, CharacterType::GOLEM, CardType::ENEMY_PLAY_CARD);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::INITIATIVE, 1);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::DAMAGE, 10, Destination::PLAYER);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultPlayCard::MonsterCard::엔진과부하:
	{
		PlayCard* card = new PlayCard(L"엔진 과부하");
		card->GetComponent<CardTexture>()->SetIllustration(L"엔진과부하");
		card->InitializePlayCard(Rarity::COMMON, CharacterType::GOLEM, CardType::ENEMY_PLAY_CARD);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::INITIATIVE, 7);
		card->AddComponent<StateParts>()->InitializeStateParts(State::ENGINE_OVERLOAD, 2, Destination::SELF);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultPlayCard::MonsterCard::말살:
	{
		PlayCard* card = new PlayCard(L"말살");
		card->GetComponent<CardTexture>()->SetIllustration(L"말살");
		card->InitializePlayCard(Rarity::COMMON, CharacterType::GOLEM, CardType::ENEMY_PLAY_CARD);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::INITIATIVE, 6);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::DAMAGE, 9, Destination::PLAYER);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::ATTACK_COUNT, 4);
		SetOrigin(card);
		return card;
	}
	break;
	case DefaultPlayCard::MonsterCard::기어체인지:
	{
		PlayCard* card = new PlayCard(L"기어 체인지");
		card->GetComponent<CardTexture>()->SetIllustration(L"기어체인지");
		card->InitializePlayCard(Rarity::COMMON, CharacterType::GOLEM, CardType::ENEMY_PLAY_CARD);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::INITIATIVE, 9);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::DAMAGE, 18, Destination::PLAYER);
		card->AddComponent<AttributeParts>()->InitializeAttributeParts(Attribute::DEFENSE, 25, Destination::SELF);
		card->AddComponent<StateParts>()->InitializeStateParts(State::QUICK, 3, Destination::SELF);
		SetOrigin(card);
		return card;
	}
	break;

	default:
		return nullptr;
	}
}

Rarity CardFactory::GetRandomFateRarity()
{
	RandomGenerator* rngInstance = RandomGenerator::GetInstance();

	double randomValue = static_cast<double>(rngInstance->GetRandomNumber(0, RAND_MAX) / RAND_MAX);
	double cumulativeProbability = 0.0;
	for (const auto& entry : fateRarityProbabilities)
	{
		cumulativeProbability += entry.second;
		if (randomValue < cumulativeProbability)
		{
			return entry.first;
		}
	}
	return Rarity::COMMON;
}

Rarity CardFactory::GetRandomPlayRarity()
{
	RandomGenerator* rngInstance = RandomGenerator::GetInstance();

	double randomValue = static_cast<double>(rngInstance->GetRandomNumber(0, RAND_MAX) / RAND_MAX);
	double cumulativeProbability = 0.0;
	for (const auto& entry : playRarityProbabilities)
	{
		cumulativeProbability += entry.second;
		if (randomValue < cumulativeProbability)
		{
			return entry.first;
		}
	}
	return Rarity::COMMON;
}

PlayCard* CardFactory::MakeRandomPlayCard()
{
	RandomGenerator* rngInstance = RandomGenerator::GetInstance();

	const std::vector<DefaultPlayCard::PlayerCard>& cards = playerPlayCardMap[GetRandomPlayRarity()];

	int randomIndex = rngInstance->GetRandomNumber(0, cards.size() - 1);

	return CreateCard(cards[randomIndex]);
}

FateCard* CardFactory::MakeRandomFateCard()
{
	RandomGenerator* rngInstance = RandomGenerator::GetInstance();

	const std::vector<DefaultFateCard::PlayerCard>& cards = playerFateCardMap[GetRandomFateRarity()];

	int randomIndex = rngInstance->GetRandomNumber(0, cards.size() - 1);

	return CreateCard(cards[randomIndex]);
}


/*test*/
PlayCard* CardFactory::MakeTestPlayerPlayCard()
{
	RandomGenerator* rngInstance = RandomGenerator::GetInstance();

	int randomIndex = rngInstance->GetRandomNumber(0, playerTestPlayCardVector.size() - 1);

	return CreateCard(playerTestPlayCardVector[randomIndex]);
}

PlayCard* CardFactory::MakeTestMonsterPlayCard()
{
	RandomGenerator* rngInstance = RandomGenerator::GetInstance();

	int randomIndex = rngInstance->GetRandomNumber(0, MonsterTestPlayCardVector.size() - 1);

	return CreateCard(MonsterTestPlayCardVector[randomIndex]);
}

FateCard* CardFactory::MakeTestPlayerFateCard()
{
	RandomGenerator* rngInstance = RandomGenerator::GetInstance();

	int randomIndex = rngInstance->GetRandomNumber(0, playerTestFateCardVector.size() - 1);

	return CreateCard(playerTestFateCardVector[randomIndex]);
}

void CardFactory::SetOrigin(Card* card)
{
	std::vector<CardPartsComponent*> cpcs = card->GetComponents<CardPartsComponent>();
	if (!cpcs.empty())
	{
		for (auto cpc : cpcs)
		{
			cpc->SetOriginValue();
		}
	}
	std::vector<CardFuncComponent*> cfcs = card->GetComponents<CardFuncComponent>();
	if (!cfcs.empty())
	{
		for (auto cfc : cfcs)
		{
			cfc->SetOriginValue();
		}
	}
}