#pragma once
#include "CardFuncComponent.h"

class AllValueMod
	: public CardFuncComponent
{

private:
	Attribute m_AttributeTarget;
	Operation m_Operation;
	int m_ValueToModify;

public:
	AllValueMod(McCol::GameObject* owner);
	~AllValueMod() override;

	void Initialize() override;
	void InitializeAllValueMod(Attribute attr, Operation op, int value);

public:
	void ApplyEffect(McCol::GameObject* targetObj) override;
	std::wstring ExtractString() override;
	void SetOriginValue() override;
	void ResetToOriginValue() override;
};
