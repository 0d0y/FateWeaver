#include "Deck.h"
#include "Card.h"

#include "../Engine/RandomGenerator.h"
#include "../Engine/EventSystem.h"
#include "../Engine/Scene.h"
#include "../Engine/Transform.h"
#include "../Engine/OBB.h"
#include "../Engine/InputSystem.h"

using namespace McCol;

Deck::Deck(std::wstring_view name, CharacterIndex index)
	: GameObject(name, Layer::UI)
	, m_OwnerIndex(index)
	, m_DeckToRender(DeckList::DECK)
	, m_IsRender(false)
	, m_CurrentPageIndex(1)
{
}

Deck::~Deck()
{
	for (Card*& card : m_Deck)
	{
		//delete card;
		//card = nullptr;
	}
	m_Deck.clear();

	for(Card* card :m_DisCardDeck)
	{
		//m_Deck.push_back(card);
	/*	delete card;
		card = nullptr;*/
	}
	m_DisCardDeck.clear();

	for (Card* card : m_OverLoadDeck)
	{
		//delete card;
		//card = nullptr;
	}
	m_OverLoadDeck.clear();
}

void Deck::Update(const float& deltaTime)
{
	for (const auto& card : m_Deck)
	{
		card->Update(deltaTime);
	}
	for (const auto& card : m_DisCardDeck)
	{
		card->Update(deltaTime);
	}
	for (const auto& card : m_OverLoadDeck)
	{
		card->Update(deltaTime);
	}

	FromDiscardedToDeck();

	if (McCol::InputSystem::GetInstance()->IsKeyDown(VK_LBUTTON))
	{
		if (m_OnMouseCard)
			m_ClickedCard = m_OnMouseCard;
		else
		{
			m_PrevClickedCard = m_ClickedCard;
			//m_ClickedCard = nullptr;
		}
	}


	/*if (InputSystem::GetInstance()->IsKeyDown('2'))
	{
		m_CurrentPageIndex++;
	}
	if (InputSystem::GetInstance()->IsKeyDown('3'))
	{
		m_CurrentPageIndex--;
	}*/
}

void Deck::FixedUpdate(const float& deltaTime)
{
	for (const auto& card : m_Deck)
	{
		card->FixedUpdate(deltaTime);
	}
	for (const auto& card : m_DisCardDeck)
	{
		card->FixedUpdate(deltaTime);
	}
	for (const auto& card : m_OverLoadDeck)
	{
		card->FixedUpdate(deltaTime);
	}
}

void Deck::Render(McCol::D2DRender* renderer)
{
	if (m_IsRender)
		RenderCardsInGrid(renderer);
}

void Deck::SuffleCard()
{
	RandomGenerator* random = RandomGenerator::GetInstance();

	std::ranges::shuffle(m_Deck.begin(), m_Deck.end(), random->GetRandomEngine());
}

Card* Deck::DrawCard()
{
	if (!m_Deck.empty())
	{
		Card* drawnCard = m_Deck.back();
		m_Deck.pop_back();

		// 덱이 비었을 경우 알림
		if (m_Deck.empty())
		{
			EventSystem::GetInstance()->PublishEvent(L"EMPTY_DECK", this);
		}

		return drawnCard;
	}
	return nullptr;
}

void Deck::AddCard(Card* card)
{
	if (card == nullptr) return;

	m_Deck.push_back(card);
	card->SetMyOwnerDeck(this);
	card->Initialize();
	//card->SetAble(false);
	card->SetCharacterIndex(m_OwnerIndex);
}

void Deck::AddDisCardDeck(Card* card)
{
	card->SetMyOwnerDeck(this);
	card->SetAble(false);
	m_DisCardDeck.push_back(card);
}

void Deck::AddOverLoadDeck(Card* card)
{
	card->SetMyOwnerDeck(this);
	card->SetAble(false);
	m_OverLoadDeck.push_back(card);
}

void Deck::RemoveCard(Card* card)
{
	if (card == nullptr) return;
	m_Deck.erase(std::remove(m_Deck.begin(), m_Deck.end(), card), m_Deck.end());
}

size_t Deck::DeckSize() const
{
	return m_Deck.size();
}

void Deck::FromDiscardedToDeck()
{
	if (m_Deck.empty())
	{
		m_Deck = m_DisCardDeck;
		m_DisCardDeck.clear();
		SuffleCard();
	}
}

void Deck::SetDeckToRender(DeckList deckList)
{
	m_DeckToRender = deckList;
}

void Deck::IsRender(bool isRender)
{
	m_IsRender = isRender;
	//m_IsRender = !m_IsRender;
}

void Deck::SetOnMouseCard(Card* pc)
{
	m_OnMouseCard = pc;
}

Card* Deck::GetOnMouseCard() const
{
	return m_OnMouseCard;
}

Card* Deck::GetClickedCard() const
{
	if (m_ClickedCard != nullptr)
		return m_ClickedCard;
	else
		return m_PrevClickedCard;

}

void Deck::RenderCardsInGrid(McCol::D2DRender* renderer)
{
	const int rowCount = 2;
	const int columnCount = 5;
	const float cardWidth = 220.0f;
	const float cardHeight = 330.0f;
	const float spacingX = 50.0f;
	const float spacingY = 50.0f;

	std::vector<Card*> deck;

	switch (m_DeckToRender)
	{
	case DeckList::DECK:
		deck = m_Deck;
		break;
	case DeckList::DISCARD:
		deck = m_DisCardDeck;
		break;
	case DeckList::OVERLOAD:
		deck = m_OverLoadDeck;
		break;
	default:
		return;
	}
	if (deck.empty())
		return;

	size_t totalCards = deck.size();
	size_t maxPages = (totalCards + rowCount * columnCount - 1) / (rowCount * columnCount);

	if (m_CurrentPageIndex < 1)
		m_CurrentPageIndex = 1;
	else if (m_CurrentPageIndex > maxPages)
		m_CurrentPageIndex = maxPages;

	size_t startIndex = (m_CurrentPageIndex - 1) * (rowCount * columnCount);
	size_t endIndex = std::min<size_t>(startIndex + rowCount * columnCount, totalCards);

	if (m_CurrentPageIndex == maxPages && totalCards % (rowCount * columnCount) != 0)
	{
		endIndex = startIndex + (totalCards % (rowCount * columnCount));
	}

	for (int i = startIndex; i < endIndex ; ++i)
	{
		size_t gridNumber = i - startIndex;

		int row = gridNumber / columnCount;
		int col = gridNumber % columnCount;

		float xOffset = col * (cardWidth + spacingX);
		float yOffset = row * (cardHeight + spacingY);

		float x = xOffset - (static_cast<float>(columnCount - 1) * (cardWidth + spacingX)) / 2.0f;
		float y = yOffset - (static_cast<float>(rowCount - 1) * (cardHeight + spacingY)) / 2.0f;

		deck[i]->GetComponent<McCol::Transform>()->SetPosition({ x, -y });
		deck[i]->SetAble(true);
		deck[i]->Render(renderer);
	}
}

