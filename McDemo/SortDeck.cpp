#include "SortDeck.h"
#include "../Engine/EventSystem.h"

SortDeck::SortDeck(McCol::GameObject* owner)
	: CardFuncComponent(owner)
{
}

SortDeck::~SortDeck()
{
}

void SortDeck::Initialize()
{
}

void SortDeck::ApplyEffect(McCol::GameObject* targetObj)
{
	McCol::EventSystem::GetInstance()->PublishEvent(L"SORT_TOP5_CARD", this);
	//SORT_TOP5_CARD 플레이 카드 덱에서 다섯 개 선택해서 덱에서 선택한 순서대로 내림차순 정렬해주는 이벤트
}

std::wstring SortDeck::ExtractString()
{
	return std::wstring();
}

void SortDeck::SetOriginValue()
{
}

void SortDeck::ResetToOriginValue()
{
}
