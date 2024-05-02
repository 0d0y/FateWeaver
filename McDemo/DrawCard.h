#pragma once
#include "CardFuncComponent.h"
/*-------------------------------------------------------
DrawCard
카드 드로우를 해주는 FATECARD를 위한 컴포넌트
m_TargetDeckType에 따라서 다른 이벤트 호출
배틀씬에서 타겟 덱 타입에 맞는 덱에서 m_NumberOfCards 수만큼 카드 드로우 해줘야함.
-------------------------------------------------------*/

class DrawCard :
	public CardFuncComponent
{
private:
	DeckType m_TargetDeckType;
	int m_NumberOfCards;

public:
	DrawCard(McCol::GameObject* owner);
	~DrawCard() override;

	void Initialize() override;
	void InitializeDrawCard(DeckType, int);

public:
	int GetNumOfCards();
	void SetNumOfCards(int numberOfCards);

public:
	void ApplyEffect(McCol::GameObject* targetObj) override;
	std::wstring ExtractString() override;
	void SetOriginValue() override;
	void ResetToOriginValue() override;
};

