#pragma once
#include "CardComponent.h"

class DrawPlayCard :
	public CardComponent
{
private:
	int m_NumberOfCards;

public:
	DrawPlayCard(McCol::GameObject* owner);

public:
	int GetNumOfCards();
	void SetNumOfCards(int numberOfCards);

public:
	void ApplyEffect(McCol::GameObject* targetObj) override;
};

