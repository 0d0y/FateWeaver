#include "PlayFromDiscard.h"
#include "../Engine/EventSystem.h"

PlayFromDiscard::PlayFromDiscard(McCol::GameObject* owner)
	: CardFuncComponent(owner)
{
}

PlayFromDiscard::~PlayFromDiscard()
{
}

void PlayFromDiscard::Initialize()
{
}

void PlayFromDiscard::ApplyEffect(McCol::GameObject* targetObj)
{
	McCol::EventSystem::GetInstance()->PublishEvent(L"PLAY_FROM_DISCARD", this);
	//PLAY_FROM_DISCARD 버린 카드 덱에서 하나 선택해서 카드 내는 이벤트
}

std::wstring PlayFromDiscard::ExtractString()
{
	return std::wstring();
}

void PlayFromDiscard::SetOriginValue()
{
}

void PlayFromDiscard::ResetToOriginValue()
{
}
