#include "AllValueMod.h"
#include "PlayCard.h"
#include "FateCard.h"
#include "../Engine/EventSystem.h"
#include "ValueMod.h"
#include "AttributeParts.h"

AllValueMod::AllValueMod(McCol::GameObject* owner)
	: CardFuncComponent(owner)
	, m_AttributeTarget(Attribute::NONE)
	, m_Operation(Operation::NONE)
	, m_ValueToModify(0)
{
}

AllValueMod::~AllValueMod()
{
}

void AllValueMod::Initialize()
{
}

void AllValueMod::InitializeAllValueMod(Attribute attr, Operation op, int value)
{
	m_AttributeTarget = attr;
	m_Operation = op;
	m_ValueToModify = value;
}

void AllValueMod::ApplyEffect(McCol::GameObject* targetObj)
{
	PlayCard* targetCard = dynamic_cast<PlayCard*>(targetObj);

	if (targetCard)
	{
		AttributeParts* attrParts = dynamic_cast<AttributeParts*>(targetCard->GetAttribute(Attribute::INITIATIVE));
		attrParts->SetValue(static_cast<int>(attrParts->GetValue() / 2));

		if (dynamic_cast<FateCard*>(GetOwner())->IsParadox())
			attrParts->SetOriginValue();
	}
}

std::wstring AllValueMod::ExtractString()
{
	std::wstring result;

	result = L"즉시\n모든 내 행동카드\n주도력 ÷2";

	return result;
}

void AllValueMod::SetOriginValue()
{
}

void AllValueMod::ResetToOriginValue()
{
}
