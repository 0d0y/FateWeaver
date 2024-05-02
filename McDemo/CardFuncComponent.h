#pragma once
#include "..\Engine\Component.h"
#include "Elements.h"
#include <string>

/*-------------------------------------------------------
CardComponent
카드에 달아줄 컴포넌트들을 위한 추상화 클래스
TODO:
차원격리 카드 기능(카드를 방어도 +10 해주는 카드로 교체)
-------------------------------------------------------*/
class McCol::GameObject;
class Card;

class CardFuncComponent :
	public McCol::Component
{
public:
	CardFuncComponent(McCol::GameObject* owner);
	~CardFuncComponent() override;

public:
	void Initialize() override;

public:
	virtual void ApplyEffect(McCol::GameObject* targetObj = nullptr) = 0;
	virtual std::wstring ExtractString() = 0;
	virtual void SetOriginValue() = 0;
	virtual void ResetToOriginValue() = 0;
};

