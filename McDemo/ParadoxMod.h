#pragma once
#include "CardFuncComponent.h"
/*-------------------------------------------------------
ParadoxMod
FateCard를 위한 Paradox 수정 컴포넌트
ApplyEffect 호출할 때 타겟 운명카드의 m_Paradox을 true로 수정해줌.
-------------------------------------------------------*/
class ParadoxMod :
    public CardFuncComponent
{
public:
	ParadoxMod(McCol::GameObject* owner);
	~ParadoxMod() override;

public:
	void Initialize() override;

	void ApplyEffect(McCol::GameObject* targetObj) override;
	std::wstring ExtractString() override;
	void SetOriginValue() override;
	void ResetToOriginValue() override;
};

