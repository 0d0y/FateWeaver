#include "AttributeParts.h"

AttributeParts::AttributeParts(McCol::GameObject* owner)
	: CardPartsComponent(owner)
	, m_Attribute(Attribute::NONE)
	, m_Value(0)
	, m_Destination(Destination::NONE)
{
}

AttributeParts::~AttributeParts()
{
}

void AttributeParts::Initialize()
{
}

void AttributeParts::InitializeAttributeParts(Attribute attr, int value, Destination destination)
{
	m_Attribute = attr;
	m_Value = value;
	m_Destination = destination;
}

void AttributeParts::SetValue(int Value)
{
	m_Value = Value;
}

int AttributeParts::GetValue() const
{
	return m_Value;
}

void AttributeParts::SetAttribute(Attribute attribute)
{
	m_Attribute = attribute;
}

Attribute AttributeParts::GetAttribute() const
{
	return m_Attribute;
}

void AttributeParts::SetDestination(Destination destination)
{
	m_Destination = destination;
}

Destination AttributeParts::GetDestination() const
{
	return m_Destination;
}

std::wstring AttributeParts::GetValueString() const
{
	return std::to_wstring(m_Value);
}

std::wstring AttributeParts::ExtractString()
{
	std::wstring result;

	std::wstring attributeString;
	switch (m_Attribute)
	{
	case Attribute::NONE:
		attributeString = L"";
		break;
	case Attribute::DAMAGE:
		attributeString = L"데미지";
		break;
	case Attribute::DEFENSE:
		attributeString = L"방어도";
		break;
	case Attribute::ATTACK_COUNT:
		attributeString = L"번 공격";
		break;
	case Attribute::END:
		attributeString = L"";
		break;
	default:
		attributeString = L"";
		break;
	}

	std::wstring destinationString;
	switch (m_Destination)
	{
	case Destination::NONE:
		destinationString = L"";
		break;
	case Destination::PLAYER:
		destinationString = L"플레이어";
		break;
	case Destination::SELF:
		destinationString = L"자기 자신";
		break;
	case Destination::NEAREST_ENEMY:
		destinationString = L"가장 앞의 적";
		break;
	case Destination::FARTHEST_ENEMY:
		destinationString = L"가장 뒤의 적";
		break;
	case Destination::ALL_ENEMIES:
		destinationString = L"모든 적";
		break;
	default:
		destinationString = L"";
		break;
	}
	if (m_Attribute == Attribute::DRAW_NUMBER && m_Value == -9999)
		return L"";

	if (m_Attribute == Attribute::INITIATIVE)
	{
		return L"";
	}

	if (m_Attribute == Attribute::ATTACK_COUNT)
	{
		result = std::to_wstring(m_Value) + attributeString;

		return result;
	}

	result = destinationString + L" " + std::to_wstring(m_Value) + L" " + attributeString;

	return result;
}

void AttributeParts::SetOriginValue()
{
	m_OriginAttribute = m_Attribute;
	m_OriginValue = m_Value;
	m_OriginDestination = m_Destination;
}

void AttributeParts::ResetToOriginValue()
{
	m_Attribute = m_OriginAttribute;
	m_Value = m_OriginValue;
	m_Destination = m_OriginDestination;
}
