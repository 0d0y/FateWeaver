#pragma once
#include "../Engine/GameObject.h"

#include "Elements.h"

#include <vector>


class Card;

enum class DeckList
{
    DECK,
    DISCARD,
    OVERLOAD,
};

class Deck : public McCol::GameObject
{
protected:
    std::vector<Card*> m_Deck;
    std::vector<Card*> m_DisCardDeck;
    std::vector<Card*> m_OverLoadDeck;
    CharacterIndex m_OwnerIndex;

    Card* m_OnMouseCard;
    Card* m_ClickedCard;
    Card* m_PrevClickedCard;

    DeckList m_DeckToRender;
    bool m_IsRender;
    size_t m_CurrentPageIndex;

public:
    Deck(std::wstring_view name, CharacterIndex index);
    ~Deck() override;

public:
    void Update(const float& deltaTime) override;
    void FixedUpdate(const float& deltaTime) override;
    void Render(McCol::D2DRender* renderer) override;

    void SuffleCard();
    Card* DrawCard();
    void AddCard(Card* card);
    void AddDisCardDeck(Card* card);
    void AddOverLoadDeck(Card* card);
    void RemoveCard(Card* card);
    size_t DeckSize() const;
    void FromDiscardedToDeck();

    std::vector<Card*> GetDeck() const
    {
        return m_Deck;
    }

    void PopCard(Card* cardToPop)
    {
        auto cardIterator = std::find(m_Deck.begin(), m_Deck.end(), cardToPop);

        if (cardIterator != m_Deck.end())
        {
            m_Deck.erase(cardIterator);
        }
    }

	size_t Size() { return m_Deck.size(); }

    void SetDeckToRender(DeckList deckList);
    void IsRender(bool isRender);

    void SetOnMouseCard(Card* pc);
    Card* GetOnMouseCard() const;

    Card* GetClickedCard() const;

    CharacterIndex GetOwnerIndex() { return m_OwnerIndex; }

    void RenderCardsInGrid(McCol::D2DRender* renderer);

    size_t GetCurrentPageIndex() const { return m_CurrentPageIndex; }
    void SetCurrentPageIndex(size_t index) { m_CurrentPageIndex = index; }

};

