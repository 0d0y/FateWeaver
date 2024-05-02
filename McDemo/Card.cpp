#include "Card.h"
#include "AttributeParts.h"
#include "Deck.h"

// for Rendering
#include "CardTexture.h"
#include "../Engine/Transform.h"
#include "../Engine/CameraSystem.h"
#include "../RenderEngine/D2DRender.h"

#include "../Engine/Obb.h"
using namespace McCol;

Card::Card(std::wstring_view name)
	: GameObject(name, Layer::CARD)
	, m_Rarity(Rarity::COMMON)
	, m_OwnerCharacterIndex(CharacterIndex::NONE)
	, m_CardOwnerType(CharacterType::NONE)
{
	AddComponent<Transform>();
	AddComponent<CardTexture>();
	AddComponent<OBB>();
}

Card::~Card()
{
}

void Card::HandleCollisionStay(McCol::Collider* otherCollider)
{
	Deck* deck = dynamic_cast<Deck*>(m_MyOwnerDeck);
	if (deck)
	{
		deck->SetOnMouseCard(this);
		GetComponent<Transform>()->SetScale({ 1.5f, 1.5f });
	}
}

void Card::HandleCollisionEnter(McCol::Collider* otherCollider)
{
}

void Card::HandleCollisionExit(McCol::Collider* otherCollider)
{
	Deck* deck = dynamic_cast<Deck*>(m_MyOwnerDeck);
	if (deck)
	{
		deck->SetOnMouseCard(nullptr);
		GetComponent<Transform>()->SetScale({ 1.0f, 1.0f });
	}
}

void Card::Update(const float& deltaTime)
{
	GameObject::Update(deltaTime);
	MakeString();
}

void Card::Render(D2DRender* renderer)
{
	GameObject::Render(renderer);
}

void Card::Initialize()
{
	GameObject::Initialize();

	CardTexture* tr = GetComponent<CardTexture>();
	//r->SetIllustration(L"../Resource/card_illust/Fate_Acc.png", L"Fate_Acc");  // test;
	tr->SetIsCardRender(true);
	D2D1_SIZE_F bmSize = tr->GetRenderSize();
	Vector2 size = { bmSize.width, bmSize.height };
	OBB* obb = GetComponent<OBB>();
	obb->SetSize(size);
}

void Card::InitializeCard(CharacterType chT, CardType caT)
{
	m_CardOwnerType = chT;
	m_CardType = caT;
}

void Card::SetAttributeValue(Attribute attr, int value)
{
	AttributeParts* ac = GetAttribute(attr);
	if (ac)
	{
		ac->SetValue(value);
	}
}

void Card::SetAttributeType(Attribute attrTarget, Attribute attrModify)
{
	AttributeParts* ac = GetAttribute(attrTarget);
	if (ac)
	{
		ac->SetAttribute(attrModify);
	}
}

void Card::SetDestination(Attribute attrTarget, Destination dest)
{
	AttributeParts* ap = GetAttribute(attrTarget);
	if (ap && ap->GetDestination() != Destination::NONE)
	{
		ap->SetDestination(dest);
	}
}

void Card::SetDestinations(Destination dest)
{
	std::vector<AttributeParts*> allAttributes = GetAttributes();

	if (!allAttributes.empty())
	{
		for (AttributeParts* ap : allAttributes)
		{
			if (ap->GetDestination() != Destination::NONE && ap->GetDestination() != Destination::SELF)
			{
				ap->SetDestination(dest);
			}
		}
	}
}

Rarity Card::GetRarity() const
{
	return m_Rarity;
}

Destination Card::GetDestination() const
{
	for (Component* co : m_Components)
	{
		AttributeParts* ap = dynamic_cast<AttributeParts*>(co);
		if (ap)
		{
			Destination dp = ap->GetDestination();
			if (dp != Destination::NONE && dp != Destination::SELF)
			{
				return dp;
			}
		}
	}
	return Destination::NONE;
}

AttributeParts* Card::GetAttribute(Attribute attr) const
{
	for (Component* co : m_Components)
	{
		AttributeParts* ap = dynamic_cast<AttributeParts*>(co);
		if (ap && ap->GetAttribute() == attr)
		{
			return ap;
		}
	}
	return nullptr;
}

std::vector<AttributeParts*> Card::GetAttributes() const
{
	std::vector<AttributeParts*> Attributes;

	for (Component* co : m_Components)
	{
		AttributeParts* ap = dynamic_cast<AttributeParts*>(co);
		if (ap)
		{
			Attributes.push_back(ap);
		}
	}
	return Attributes;
}

int Card::GetCharacterIndex() const
{
	return SIZE(m_OwnerCharacterIndex);
}

void Card::SetCharacterIndex(CharacterIndex ci)
{
	m_OwnerCharacterIndex = ci;
}

CharacterType Card::GetCardOwnerType() const
{
	return m_CardOwnerType;
}

CardType Card::GetCardType() const
{
	return m_CardType;
}

void Card::SetMyOwnerDeck(McCol::GameObject* deck)
{
	m_MyOwnerDeck = deck;
}
