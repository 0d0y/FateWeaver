#pragma once
#include "Deck.h"
#include "../Engine/Vector2.h"

class FutureDeck : public Deck
{
public:
	FutureDeck();
	~FutureDeck() override;

private:
	float m_StartX, m_StartY;
	float m_NextX, m_NextY;

public:
	void DeckUpdate(const float& deltaTime) override;
	void DeckRender(McCol::D2DRender* renderer) override;

private:
	McCol::Vector2 GetCurPos(int initiative, size_t index);
};
