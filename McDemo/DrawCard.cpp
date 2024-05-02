#include "DrawCard.h"
#include "FateCard.h"
#include "../Engine/EventSystem.h"

DrawCard::DrawCard(McCol::GameObject* owner)
	: CardFuncComponent(owner)
	, m_TargetDeckType(DeckType::NONE)
	, m_NumberOfCards(0)
{
}

DrawCard::~DrawCard()
{
}

void DrawCard::Initialize()
{
}

void DrawCard::InitializeDrawCard(DeckType targetDeckType, int numberOfCards)
{
	m_TargetDeckType = targetDeckType;
	m_NumberOfCards = numberOfCards;
}

int DrawCard::GetNumOfCards()
{
	return m_NumberOfCards;
}

void DrawCard::SetNumOfCards(int numberOfCards)
{
	m_NumberOfCards = numberOfCards;
}

void DrawCard::ApplyEffect(McCol::GameObject* targetObj)
{
	if (m_TargetDeckType == DeckType::PLAYER_PLAY_CARD)
		McCol::EventSystem::GetInstance()->PublishEvent(L"DRAW_PLAYCARD", this);

	if (m_TargetDeckType == DeckType::PLAYER_FATE_CARD)
		McCol::EventSystem::GetInstance()->PublishEvent(L"DRAW_FATECARD", this);
}

std::wstring DrawCard::ExtractString()
{
	std::wstring result = L"";

	std::wstring targetDeckTypeString;
	FateCard* owner = dynamic_cast<FateCard*>(GetOwner());

	switch (m_TargetDeckType)
	{
	case DeckType::NONE:
		targetDeckTypeString = L"";
		break;
	case DeckType::PLAYER_PLAY_CARD:
	{
		if (owner)
			targetDeckTypeString = L"행동 카드 덱에서\n";
		targetDeckTypeString = L"행동 카드\n";
	}
	break;
	case DeckType::PLAYER_FATE_CARD:
	{
		if (owner)
			targetDeckTypeString = L"운명 카드 덱에서\n";
		targetDeckTypeString = L"운명 카드\n";
	}
	break;
	default:
		break;
	}

	if (owner)
		result = L"즉시\n";

	result += targetDeckTypeString + L" " + std::to_wstring(m_NumberOfCards) + L"장 드로우";

	return result;
}

void DrawCard::SetOriginValue()
{
}

void DrawCard::ResetToOriginValue()
{
}
