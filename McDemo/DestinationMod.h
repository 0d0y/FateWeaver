#pragma once
#include "CardFuncComponent.h"
#include "Elements.h"
/*-------------------------------------------------------
DestinationMod
FateCard를 위한 Destination 수정 컴포넌트
ApplyEffect 호출할 때 타겟 카드의 Destination을 m_DestinationToModify로 수정해줌.
-------------------------------------------------------*/

class DestinationMod
	: public CardFuncComponent
{
private:
	CardType m_DestinationTarget;
	Destination m_DestinationToModify;

public:
	DestinationMod(McCol::GameObject* owner);
	~DestinationMod() override;

public:
	void Initialize() override;
	void InitializeDestinationMod(CardType destinationTarget, Destination destinationToModify);

public:
	CardType GetDestinationTarget() const { return m_DestinationTarget; }
	Destination GetDestinationToModify() const { return m_DestinationToModify; }

public:
	void ApplyEffect(McCol::GameObject* targetObj) override;
	std::wstring ExtractString() override;
	void SetOriginValue() override;
	void ResetToOriginValue() override;

};

