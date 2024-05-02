#include "OperationMod.h"
#include "FateCard.h"
#include "ValueMod.h"

#include <vector>

OperationMod::OperationMod(McCol::GameObject* owner)
	: CardFuncComponent(owner)
{
}

OperationMod::~OperationMod()
{
}

void OperationMod::Initialize()
{
}

void OperationMod::ApplyEffect(McCol::GameObject* targetObj)
{
	FateCard* targetCard = dynamic_cast<FateCard*>(targetObj);

	if (targetCard)
	{
		ValueMod* vm = targetCard->GetComponent<ValueMod>();

		if (vm && vm->GetOperation() == Operation::ADD)
		{
			vm->SetOperation(Operation::SUB);
		}

		if (dynamic_cast<FateCard*>(GetOwner())->IsParadox())
			vm->SetOriginValue();
	}

}

std::wstring OperationMod::ExtractString()
{
	std::wstring result;

	result = L"운명카드\n카드의 +를\n-로 바꿉니다.";

	return result;
}

void OperationMod::SetOriginValue()
{
}

void OperationMod::ResetToOriginValue()
{
}
