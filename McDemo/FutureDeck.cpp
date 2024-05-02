#include "FutureDeck.h"
#include "Card.h"
#include "PlayCard.h"
#include "../RenderEngine/D2DRender.h"
#include "../Engine/Transform.h"

using namespace McCol;

FutureDeck::FutureDeck()
	: Deck(L"Future Deck")
	, m_StartX(100)
	, m_StartY(100)
	, m_NextX(0)
	, m_NextY(0)
{
}

FutureDeck::~FutureDeck()
{
}

void FutureDeck::DeckUpdate(const float& deltaTime)
{

}

void FutureDeck::DeckRender(McCol::D2DRender* renderer)
{
	for (size_t i = 0; i < m_Deck.size(); i++)
	{
		const auto playCard = dynamic_cast<PlayCard*>(m_Deck[i]);
		auto curPos = GetCurPos(playCard->GetInitiative(), i);
		playCard->GetComponent<Transform>()->SetPosition(curPos);
	}
}

McCol::Vector2 FutureDeck::GetCurPos(int initiative, size_t index)
{
	return { m_StartX + m_NextX * index, m_StartY + m_NextY * index };
}
