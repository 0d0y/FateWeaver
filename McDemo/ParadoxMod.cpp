#include "ParadoxMod.h"
#include "FateCard.h"

ParadoxMod::ParadoxMod(McCol::GameObject* owner)
	: CardFuncComponent(owner)
{
}

ParadoxMod::~ParadoxMod()
{
}

void ParadoxMod::Initialize()
{
}

void ParadoxMod::ApplyEffect(McCol::GameObject* targetObj)
{
	FateCard* targetCard = dynamic_cast<FateCard*>(targetObj);
	if (targetCard)
	{
		targetCard->ParadoxOn();
	}

}

std::wstring ParadoxMod::ExtractString()
{
	std::wstring result;

	result = L"운명카드\n효과 수정 : 패러독스";

	return result;
}

void ParadoxMod::SetOriginValue()
{
}

void ParadoxMod::ResetToOriginValue()
{
}
