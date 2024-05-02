#include "GameManager.h"
#include "../Engine/Macro.h"

#include "Deck.h"
#include "PlayCard.h"
#include "FateCard.h"
#include "CardComponentHeader.h"
#include "../Engine/EventSystem.h"


GameManager* GameManager::m_Instance = nullptr;

GameManager::GameManager()
	: m_PlayDeck(nullptr)
	, m_FateDeck(nullptr)
	, m_NumberPlayerFateEnengy(0)
	, m_MapIndex(0)
{
	m_DrawCountPlayer[DeckType::PLAYER_FATE_CARD] = 5;
	m_DrawCountPlayer[DeckType::PLAYER_PLAY_CARD] = 2;
	m_DrawCountEnemy[CharacterType::ZOMBIE] = 1;
	m_DrawCountEnemy[CharacterType::WEREWOLF] = 2;
	m_DrawCountEnemy[CharacterType::STALKER] = 1;
	m_DrawCountEnemy[CharacterType::FANATIC] = 1;
	m_DrawCountEnemy[CharacterType::GOLEM] = 3;

	m_PlayerCurHealth = m_PlayerMaxHealth = 80;

	m_NumberPlayerFateEnengy = 3;

	m_FateDeck = new Deck(L"Player Fate Deck", CharacterIndex::NONE);
	m_PlayDeck = new Deck(L"Player Play Deck", CharacterIndex::NONE);

	//m_FateDeck->AddCard(m_CardFactory.CreateCard(DefaultFateCard::PlayerCard::간파));
	//m_FateDeck->AddCard(m_CardFactory.CreateCard(DefaultFateCard::PlayerCard::간파));
	//m_FateDeck->AddCard(m_CardFactory.CreateCard(DefaultFateCard::PlayerCard::간파));
	//m_FateDeck->AddCard(m_CardFactory.CreateCard(DefaultFateCard::PlayerCard::치명));
	//m_FateDeck->AddCard(m_CardFactory.CreateCard(DefaultFateCard::PlayerCard::치명));
	//m_FateDeck->AddCard(m_CardFactory.CreateCard(DefaultFateCard::PlayerCard::치명_패러독스));
	//m_FateDeck->AddCard(m_CardFactory.CreateCard(DefaultFateCard::PlayerCard::시간가속));
	//m_FateDeck->AddCard(m_CardFactory.CreateCard(DefaultFateCard::PlayerCard::숨을수없는숙명));
	//m_FateDeck->SuffleCard();

	//m_PlayDeck->AddCard(m_CardFactory.CreateCard(DefaultPlayCard::PlayerCard::사격));
	//m_PlayDeck->AddCard(m_CardFactory.CreateCard(DefaultPlayCard::PlayerCard::사격));
	//m_PlayDeck->AddCard(m_CardFactory.CreateCard(DefaultPlayCard::PlayerCard::회피));
	//m_PlayDeck->AddCard(m_CardFactory.CreateCard(DefaultPlayCard::PlayerCard::회피));
	//m_PlayDeck->AddCard(m_CardFactory.CreateCard(DefaultPlayCard::PlayerCard::다리걸기));
	//m_PlayDeck->AddCard(m_CardFactory.CreateCard(DefaultPlayCard::PlayerCard::난사));
	m_FateDeck->AddCard(m_CardFactory.CreateCard(DefaultFateCard::PlayerCard::간파));
	m_FateDeck->AddCard(m_CardFactory.CreateCard(DefaultFateCard::PlayerCard::간파));
	m_FateDeck->AddCard(m_CardFactory.CreateCard(DefaultFateCard::PlayerCard::간파));

	m_FateDeck->AddCard(m_CardFactory.CreateCard(DefaultFateCard::PlayerCard::치명));
	m_FateDeck->AddCard(m_CardFactory.CreateCard(DefaultFateCard::PlayerCard::치명));
	m_FateDeck->AddCard(m_CardFactory.CreateCard(DefaultFateCard::PlayerCard::치명));
	m_FateDeck->AddCard(m_CardFactory.CreateCard(DefaultFateCard::PlayerCard::시간가속));
	m_FateDeck->AddCard(m_CardFactory.CreateCard(DefaultFateCard::PlayerCard::시간가속));
	m_FateDeck->AddCard(m_CardFactory.CreateCard(DefaultFateCard::PlayerCard::시간가속));

	m_FateDeck->AddCard(m_CardFactory.CreateCard(DefaultFateCard::PlayerCard::숨을수없는숙명));
	m_FateDeck->AddCard(m_CardFactory.CreateCard(DefaultFateCard::PlayerCard::숨을수없는숙명));
	m_FateDeck->AddCard(m_CardFactory.CreateCard(DefaultFateCard::PlayerCard::숨을수없는숙명));

	for (int i = SIZE(DefaultFateCard::PlayerCard::도플갱어); i < SIZE(DefaultFateCard::PlayerCard::도플갱어_패러독스); i++)
	{
		m_FateDeck->AddCard(m_CardFactory.CreateCard(static_cast<DefaultFateCard::PlayerCard>(i)));
	}
	m_FateDeck->SuffleCard();

	m_PlayDeck->AddCard(m_CardFactory.CreateCard(DefaultPlayCard::PlayerCard::사격));
	m_PlayDeck->AddCard(m_CardFactory.CreateCard(DefaultPlayCard::PlayerCard::사격));
	m_PlayDeck->AddCard(m_CardFactory.CreateCard(DefaultPlayCard::PlayerCard::사격));

	m_PlayDeck->AddCard(m_CardFactory.CreateCard(DefaultPlayCard::PlayerCard::회피));
	m_PlayDeck->AddCard(m_CardFactory.CreateCard(DefaultPlayCard::PlayerCard::회피));
	m_PlayDeck->AddCard(m_CardFactory.CreateCard(DefaultPlayCard::PlayerCard::회피));

	m_PlayDeck->AddCard(m_CardFactory.CreateCard(DefaultPlayCard::PlayerCard::다리걸기));
	m_PlayDeck->AddCard(m_CardFactory.CreateCard(DefaultPlayCard::PlayerCard::다리걸기));
	m_PlayDeck->AddCard(m_CardFactory.CreateCard(DefaultPlayCard::PlayerCard::다리걸기));

	m_PlayDeck->AddCard(m_CardFactory.CreateCard(DefaultPlayCard::PlayerCard::난사));
	m_PlayDeck->AddCard(m_CardFactory.CreateCard(DefaultPlayCard::PlayerCard::난사));
	m_PlayDeck->AddCard(m_CardFactory.CreateCard(DefaultPlayCard::PlayerCard::난사));

	m_PlayDeck->AddCard(m_CardFactory.CreateCard(DefaultPlayCard::PlayerCard::저격));
	m_PlayDeck->AddCard(m_CardFactory.CreateCard(DefaultPlayCard::PlayerCard::플래쉬뱅));
	m_PlayDeck->AddCard(m_CardFactory.CreateCard(DefaultPlayCard::PlayerCard::피버타임));
	m_PlayDeck->AddCard(m_CardFactory.CreateCard(DefaultPlayCard::PlayerCard::빈틈포착));
	m_PlayDeck->AddCard(m_CardFactory.CreateCard(DefaultPlayCard::PlayerCard::마탄의사수));
	m_PlayDeck->AddCard(m_CardFactory.CreateCard(DefaultPlayCard::PlayerCard::아케인블래스트));

	m_PlayDeck->SuffleCard();

	//for (auto fatecard : m_FateDeck->GetDeck())
	//{
	//	std::vector<CardPartsComponent*> cpcs = fatecard->GetComponents<CardPartsComponent>();
	//	if (!cpcs.empty())
	//	{
	//		for (auto cpc : cpcs)
	//		{
	//			cpc->SetOriginValue();
	//		}
	//	}
	//	std::vector<CardFuncComponent*> cfcs = fatecard->GetComponents<CardFuncComponent>();
	//	if (!cfcs.empty())
	//	{
	//		for (auto cfc : cfcs)
	//		{
	//			cfc->SetOriginValue();
	//		}
	//	}
	//}
	//for (auto fatecard : m_PlayDeck->GetDeck())
	//{
	//	std::vector<CardPartsComponent*> cpcs = fatecard->GetComponents<CardPartsComponent>();
	//	if (!cpcs.empty())
	//	{
	//		for (auto cpc : cpcs)
	//		{
	//			cpc->SetOriginValue();
	//		}
	//	}
	//	std::vector<CardFuncComponent*> cfcs = fatecard->GetComponents<CardFuncComponent>();
	//	if (!cfcs.empty())
	//	{
	//		for (auto cfc : cfcs)
	//		{
	//			cfc->SetOriginValue();
	//		}
	//	}
	//}

}

void GameManager::Initialize()
{
}

void GameManager::Finalize()
{
	SAFE_DELETE(m_Instance)
}

PlayCard* GameManager::CreateCard(DefaultPlayCard::PlayerCard cardName)
{
	return m_CardFactory.CreateCard(cardName);
}

FateCard* GameManager::CreateCard(DefaultFateCard::PlayerCard cardName)
{
	return m_CardFactory.CreateCard(cardName);
}

PlayCard* GameManager::CreateCard(DefaultPlayCard::MonsterCard cardName)
{
	return m_CardFactory.CreateCard(cardName);
}

size_t GameManager::GetDrawCountPlayer(DeckType deckType)
{
	return m_DrawCountPlayer[deckType];
}
size_t GameManager::GetDrawCountEnemy(CharacterType CharaterType)
{
	return m_DrawCountEnemy[CharaterType];
}

size_t GameManager::GetNumberPlayerFateEnengy()
{
	return m_NumberPlayerFateEnengy;
}

void GameManager::SetNumberPlayerFateEnengy(size_t number)
{
	m_NumberPlayerFateEnengy = number;
}

void GameManager::SetMapIndex(const int& mapIndex)
{
	m_MapIndex = mapIndex;
}

int GameManager::GetMapIndex()
{
	return m_MapIndex;
}

int GameManager::GetCurHealth()
{
	return m_PlayerCurHealth;
}

int GameManager::GetMaxHealth()
{
	return m_PlayerMaxHealth;
}

void GameManager::SetCurHealth(int curHp)
{
	m_PlayerCurHealth = curHp;
}

void GameManager::SetMaxHealth(int maxHp)
{
	m_PlayerMaxHealth = maxHp;
}

Deck* GameManager::CreateMonsterDeck(CharacterType ct, Deck* deck)
{
	switch (ct)
	{
	case CharacterType::ZOMBIE:
	{
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::차가운포옹));
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::차가운포옹));
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::깨물기));
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::깨물기));
		deck->SuffleCard();
	}
	break;
	case CharacterType::WEREWOLF:
	{
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::야성해방));
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::야성해방));
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::무자비));
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::무자비));
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::저돌맹진));
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::저돌맹진));
		deck->SuffleCard();
	}
	break;
	case CharacterType::STALKER:
	{
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::필연적인공포));
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::필연적인공포));
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::끝없는추적));
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::끝없는추적));
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::저격));
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::저격));
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::다리걸기));
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::다리걸기));
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::플래쉬뱅));
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::플래쉬뱅));
		deck->SuffleCard();
	}
	break;
	case CharacterType::FANATIC:
	{
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::멸망을부르는노래));
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::멸망을부르는노래));
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::공허의가호));
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::공허의가호));
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::징벌));
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::징벌));
		deck->SuffleCard();
	}
	break;
	case CharacterType::GOLEM:
	{
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::시공의파동));
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::시공의파동));
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::엔진과부하));
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::엔진과부하));
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::말살));
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::말살));
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::기어체인지));
		deck->AddCard(CreateCard(DefaultPlayCard::MonsterCard::기어체인지));
		deck->SuffleCard();
	}
	break;
	default:
		return nullptr;
		break;
	}
}

void GameManager::MakeDefaultPlayDeck()
{
}

void GameManager::MakeDefaultFateDeck()
{
}
