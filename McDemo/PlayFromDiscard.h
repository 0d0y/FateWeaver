#pragma once
#include "CardFuncComponent.h"
/*-------------------------------------------------------
PlayFromDiscard
버려진 카드 덱에서 선택한 한장의 카드를 미래영역으로 보내는 FATECARD를 위한 컴포넌트
이벤트 호출시 배틀씬에서 버려진 플레이카드덱을 보여주고 플레이어가 1개 선택하도록 한 뒤 선택된 카드를 미래영역으로 보내야함.
-------------------------------------------------------*/
class PlayFromDiscard :
	public CardFuncComponent
{
public:
	PlayFromDiscard(McCol::GameObject* owner);
	~PlayFromDiscard() override;

public:
	void Initialize() override;

	void ApplyEffect(McCol::GameObject* targetObj) override;
	std::wstring ExtractString() override;
	void SetOriginValue() override;
	void ResetToOriginValue() override;
};

