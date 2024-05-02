#pragma once
#include "CardFuncComponent.h"
/*-------------------------------------------------------
SetCard
카드 변경하는 기능을 가진 FATECARD를 위한 컴포넌트
ApplyEffect 호출할 때 타겟카드를 방어도 +10을 주는 카드로 바꾼다.
-------------------------------------------------------*/
class SetCard :
	public CardFuncComponent
{
public:
	SetCard(McCol::GameObject* owner);
	~SetCard() override;

public:
	void Initialize() override;

	void ApplyEffect(McCol::GameObject* targetObj) override;
	std::wstring ExtractString() override;
	void SetOriginValue() override;
	void ResetToOriginValue() override;
};

