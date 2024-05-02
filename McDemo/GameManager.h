#pragma once
#include "../Engine/EventHandler.h"
#include "CardFactory.h"
#include "Deck.h"


class Deck;

class GameManager : public McCol::EventHandler
{
private:
	GameManager();
	~GameManager() override = default;

private:
	static GameManager* m_Instance;

	int m_PlayerMaxHealth;
	int m_PlayerCurHealth;

	// 저장할 멤버 변수
	Deck* m_PlayDeck;
	Deck* m_FateDeck;

	std::map<DeckType, size_t> m_DrawCountPlayer;
	std::map<CharacterType, size_t> m_DrawCountEnemy;
	size_t m_NumberPlayerFateEnengy;

	// 카드 팩토리
	CardFactory m_CardFactory;

	// 현재 맵 인덱스
	int m_MapIndex;

public:
	static GameManager* GetInstance()
	{
		if (m_Instance == nullptr)
			m_Instance = new GameManager;

		return m_Instance;
	}
	void Initialize();
	void Finalize();

	Deck* GetPlayerPlayDeck()
	{
		return m_PlayDeck;
	}
	Deck* GetPlayerFateDeck()
	{
		return m_FateDeck;
	}

	// 멤버 변수 Get, Set
	//Deck*& GetPlayerPlayDeck() { return m_PlayDeck; }
	//Deck*& GetPlayerFateDeck() { return m_FateDeck; }

	PlayCard* CreateCard(DefaultPlayCard::PlayerCard cardName);
	FateCard* CreateCard(DefaultFateCard::PlayerCard cardName);
	PlayCard* CreateCard(DefaultPlayCard::MonsterCard cardName);

	size_t GetDrawCountPlayer(DeckType deckType);
	size_t GetDrawCountEnemy(CharacterType CharaterType);
	size_t GetNumberPlayerFateEnengy();
	void SetNumberPlayerFateEnengy(size_t number);

	// 맵 씬에서 인덱스 Get / Set 용도의 함수
	void SetMapIndex(const int& mapIndex);
	int GetMapIndex();

	int GetCurHealth();
	int GetMaxHealth();
	void SetCurHealth(int curHp);
	void SetMaxHealth(int maxHp);

	Deck* CreateMonsterDeck(CharacterType ct, Deck* deck);

	void MoveCardsToScene(Deck* scenePlayDeck, Deck* sceneFateDeck)
	{
		std::vector<Card*> playdeck = m_PlayDeck->GetDeck();
		for (Card* card : playdeck)
		{
			scenePlayDeck->AddCard(card);
		}
		std::vector<Card*> fatedeck = m_FateDeck->GetDeck();
		for (Card* card : fatedeck)
		{
			sceneFateDeck->AddCard(card);
		}
	}

private:
	void MakeDefaultPlayDeck();
	void MakeDefaultFateDeck();

};
