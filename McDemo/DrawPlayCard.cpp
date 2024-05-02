#include "DrawPlayCard.h"
#include "../Engine/EventSystem.h"

DrawPlayCard::DrawPlayCard(McCol::GameObject* owner)
	: CardComponent(owner)
{
}

int DrawPlayCard::GetNumOfCards()
{
	return m_NumberOfCards;
}

void DrawPlayCard::SetNumOfCards(int numberOfCards)
{
	m_NumberOfCards = numberOfCards;
}

void DrawPlayCard::ApplyEffect(McCol::GameObject* targetObj)
{
	McCol::EventSystem::GetInstance()->PublishEvent(L"DRAW_PLAYCARD", this);
	//DRAW_PLAYCARD  // ¿©±â
}
