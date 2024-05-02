/*-------------------------------------------------------
Play Card
: Play로 PlayCard가 갖고 있는 AffectComponent 찾아서 그 객체의 ApplyEffect 호출

- 주도력, 타겟은 PlayCard에서만 사용되므로 멤버 변수로 존재함
- 사용되는 Factor가 FateCard와 주로 겹치기 때문에 Card의 Attribute에서 끌어다가 사용함
- 효과의 경우, FateCard와 겹치지 않으므로 AffectComponent로 구현함

++) PlayCard의 경우 비고가 2개 존재할 때가 있는데... 이건 나중에 .. 띵킹해보죠
------------------------------------------------------ - */

#pragma once
#include <map>

#include "Card.h"
#include "Elements.h"

class PlayCard :
	public Card
{
public:
	PlayCard(std::wstring_view name);
	~PlayCard() override;



public:
	void InitializePlayCard(Rarity rarity, CharacterType chT, CardType caT);

	void HandleCollisionStay(McCol::Collider* otherCollider) override;
	void HandleCollisionEnter(McCol::Collider* otherCollider) override;
	void HandleCollisionExit(McCol::Collider* otherCollider) override;

public:
	void Play(GameObject* targetObj) override;

public:
	int GetInitiative() const;
	void SetInitiative(int value);

	std::map<Destination, CardInfo> GetCardInfo();

	std::wstring MakeString() override;
};

