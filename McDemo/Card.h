#pragma once
#include "Elements.h"
#include <string>
#include "..\Engine\GameObject.h"
#include "..\Engine\ICollidable.h"
/*-------------------------------------------------------
Card
흠... 일단 fatecard를 위한 최소한의 구현은 된거 같음...
AttributeComponent로 인트 밸류하나 갖고 있는 객체 만들어서
map으로 이넘클래스 타입 지정해서 m_Attributes에 보관.
그 속성이 존재하는지 체크할땐 GetAttribute() 리턴이 0이 아닌지 체크하면 된다.
근데 0으로 체크하면 밸류가 0인 속성이 있을수도 있지 않나? 이건 확인이 필요
카드 동작은 Play로 구현. 카드 동작에는 모든 타겟 카드가 존재할거라 생각해서 일단 저렇게 구현함
-------------------------------------------------------*/

class AttributeParts;

class Card :
	public McCol::GameObject
{
protected:
	CardType m_CardType;
	CharacterType m_CardOwnerType;
	Rarity m_Rarity;
	CharacterIndex m_OwnerCharacterIndex;
	GameObject* m_MyOwnerDeck;

	bool m_Iscollidable;

public:
	Card(std::wstring_view name);
	~Card() override;

public:
	void HandleCollisionStay(McCol::Collider* otherCollider) override;
	void HandleCollisionEnter(McCol::Collider* otherCollider) override;
	void HandleCollisionExit(McCol::Collider* otherCollider) override;
	void Update(const float& deltaTime) override;
	void Render(McCol::D2DRender* renderer) override;
	void Initialize() override;

public:
	void InitializeCard(CharacterType chT, CardType caT);
	virtual void Play(GameObject* targetObj) = 0;

public:
	void SetAttributeValue(Attribute attrTarget, int value);
	void SetAttributeType(Attribute attrTarget, Attribute attrModify);

	void SetDestination(Attribute attrTarget, Destination dest);
	void SetDestinations(Destination dest);

	Rarity GetRarity() const;
	Destination GetDestination() const;
	AttributeParts* GetAttribute(Attribute attr) const;
	std::vector<AttributeParts*> GetAttributes() const;

	int GetCharacterIndex() const;
	void SetCharacterIndex(CharacterIndex ci);

	CharacterType GetCardOwnerType() const;
	CardType GetCardType() const;

	void Setcollidable(bool iscollidable) { m_Iscollidable = iscollidable; }

	void SetMyOwnerDeck(McCol::GameObject* deck);

	virtual std::wstring MakeString() = 0;
};
