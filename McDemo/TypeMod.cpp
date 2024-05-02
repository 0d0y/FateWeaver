#include "TypeMod.h"
#include "Card.h"
#include "Elements.h"
#include "AttributeParts.h"
#include "FateCard.h"

void TypeMod::Initialize()
{
}

TypeMod::TypeMod(McCol::GameObject* owner)
	: CardFuncComponent(owner)
	, m_AttributeTarget(Attribute::NONE)
	, m_AttributeToModify(Attribute::NONE)
{
}

TypeMod::~TypeMod()
{
}

void TypeMod::InitializeTypeMod(Attribute attrTarget, Attribute attrModify, CardType targetCard)
{
	m_AttributeTarget = attrTarget;
	m_AttributeToModify = attrModify;
	m_TargetCard = targetCard;
}

void TypeMod::ApplyEffect(McCol::GameObject* targetObj)
{
	Card* targetCard = dynamic_cast<Card*>(targetObj);

	if (targetCard && targetCard->GetCardType() == m_TargetCard)
	{
		AttributeParts* AttributeTarget = targetCard->GetAttribute(m_AttributeTarget);
		if (AttributeTarget)
			AttributeTarget->SetAttribute(m_AttributeToModify);

		if (dynamic_cast<FateCard*>(GetOwner())->IsParadox())
			AttributeTarget->SetOriginValue();
	}
}

std::wstring TypeMod::ExtractString()
{
	std::wstring result;

	std::wstring attributeTargetString;
	switch (m_AttributeTarget)
	{
	case Attribute::DAMAGE:
		attributeTargetString = L"데미지 수정 : ";
		break;
	default:
		break;
	}

	std::wstring attributeToModify;
	switch (m_AttributeToModify)
	{
	case Attribute::DEFENSE:
		attributeToModify = L"방어도";
		break;
	default:
		break;
	}

	result = L"내 행동 카드\n" + attributeTargetString + L" " + attributeToModify;

	return result;
}

void TypeMod::SetOriginValue()
{
}

void TypeMod::ResetToOriginValue()
{
}
