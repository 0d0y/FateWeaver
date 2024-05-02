#pragma once
#include "CardFuncComponent.h"
/*-------------------------------------------------------
SortDeck
덱에서 상위 5개 카드를 선택한 순서대로 정렬하는 기능을 가진 FATECARD를 위한 컴포넌트
이벤트 호출시 배틀씬에서 플레이카드덱을 보여주고 플레이어가 5개 선택하도록 한 뒤에 선택한 순서대로 덱 인덱스 앞으로 오게 정렬해줘야함.
-------------------------------------------------------*/
class SortDeck :
    public CardFuncComponent
{
public:
	SortDeck(McCol::GameObject* owner);
	~SortDeck() override;

public:
	void Initialize() override;

	void ApplyEffect(McCol::GameObject* targetObj) override;
	std::wstring ExtractString() override;
	void SetOriginValue() override;
	void ResetToOriginValue() override;
};

