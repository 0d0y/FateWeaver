#pragma once
#include "..\Engine\Component.h"
#include "Elements.h"
#include <string>


class McCol::GameObject;
class Card;

class CardPartsComponent :
    public McCol::Component
{
public:
	CardPartsComponent(McCol::GameObject* owner);
	~CardPartsComponent() override;

public:
	void Initialize() override;
	virtual std::wstring ExtractString() = 0;
	virtual void SetOriginValue() = 0;
	virtual void ResetToOriginValue() = 0;
};