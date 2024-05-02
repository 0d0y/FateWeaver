#include "SetCard.h"

SetCard::SetCard(McCol::GameObject* owner)
	: CardFuncComponent(owner)
{
}

SetCard::~SetCard()
{
}

void SetCard::Initialize()
{
}

void SetCard::ApplyEffect(McCol::GameObject* targetObj)
{
	//PlayCard* targetCard = dynamic_cast<PlayCard*>(targetObj);

}

std::wstring SetCard::ExtractString()
{
	return std::wstring();
}

void SetCard::SetOriginValue()
{
}

void SetCard::ResetToOriginValue()
{
}
