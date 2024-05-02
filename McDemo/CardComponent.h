#pragma once
#include "..\Engine\Component.h"
#include "Elements.h"
/*-------------------------------------------------------
CardComponent
카드에 달아줄 컴포넌트들을 위한 추상화 클래스
TODO:
차원격리 카드 기능(카드를 방어도 +10 해주는 카드로 교체)
-------------------------------------------------------*/
class McCol::GameObject;
class Card;

class CardComponent :
	public McCol::Component
{
public:
	CardComponent(McCol::GameObject* owner);
	~CardComponent() override;

public:
	virtual void ApplyEffect(McCol::GameObject* targetObj = nullptr) = 0;
	void Initialize() override {}
};

