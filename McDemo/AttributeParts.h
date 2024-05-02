#pragma once
#include "CardPartsComponent.h"
#include "Elements.h"

class McCol::GameObject;

class AttributeParts :
	public CardPartsComponent
{
private:
	Attribute m_Attribute;
	int m_Value;
	Destination m_Destination;

	Attribute m_OriginAttribute;
	int m_OriginValue;
	Destination m_OriginDestination;

public:
	AttributeParts(McCol::GameObject* owner);
	~AttributeParts();

	void InitializeAttributeParts(Attribute Attr, int value, Destination destination = Destination::NONE);

	void Initialize() override;

public:
	void SetValue(int value);
	int GetValue() const;

	void SetAttribute(Attribute attribute);
	Attribute GetAttribute() const;

	void SetDestination(Destination destination);
	Destination GetDestination() const;

	std::wstring GetValueString() const;
	std::wstring ExtractString() override;

	void SetOriginValue() override;
	void ResetToOriginValue() override;
};

