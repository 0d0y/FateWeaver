#pragma once
#include "CardFuncComponent.h"
/*-------------------------------------------------------
TypeMod
FateCard를 위한 Type 수정 컴포넌트
ApplyEffect 호출할 때 타겟 카드의 Attribute을 m_AttributeToModify로 수정해줌.
-------------------------------------------------------*/

class TypeMod :
    public CardFuncComponent
{
private:
	Attribute m_AttributeTarget;
	Attribute m_AttributeToModify;
	CardType m_TargetCard;

	Attribute m_OriginAttributeTarget;
	Attribute m_OriginAttributeToModify;
	CardType m_OriginTargetCard;

public:
	TypeMod(McCol::GameObject* owner);
	~TypeMod() override;

	void Initialize() override;
	void InitializeTypeMod(Attribute attrTarget, Attribute attrModify, CardType targetCard);

public:
	void ApplyEffect(McCol::GameObject* targetObj) override;
	std::wstring ExtractString() override;
	void SetOriginValue() override;
	void ResetToOriginValue() override;
};

