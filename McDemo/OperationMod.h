#pragma once
#include "CardFuncComponent.h"

class OperationMod
	: public CardFuncComponent
{
public:
	OperationMod(McCol::GameObject* owner);
	~OperationMod() override;

public:
	void Initialize() override;

public:
	void ApplyEffect(McCol::GameObject* targetObj) override;
	std::wstring ExtractString() override;

	void SetOriginValue() override;
	void ResetToOriginValue() override;
};

