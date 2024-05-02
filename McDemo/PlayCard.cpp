#include "PlayCard.h"



#include "CardPartsComponent.h"
#include "CardFuncComponent.h"
#include "KeywordParts.h"
#include "AttributeParts.h"
#include "StateParts.h"
#include "Future.h"
#include "Deck.h"
#include "CardTexture.h"
#include "../Engine/OBB.h"
#include "../Engine/Transform.h"

#include <vector>
#include <map>

PlayCard::PlayCard(std::wstring_view name)
	: Card(name)
{
}

PlayCard::~PlayCard()
{
}

void PlayCard::HandleCollisionStay(McCol::Collider* otherCollider)
{
	Card::HandleCollisionStay(otherCollider);
	if (!m_Iscollidable)
		return;

	Future* future = dynamic_cast<Future*>(m_MyOwnerDeck);
	if (future)
	{
		future->SetOnMouseCard(this);
	}
}

void PlayCard::HandleCollisionEnter(McCol::Collider* otherCollider)
{
	Card::HandleCollisionEnter(otherCollider);
	if (!m_Iscollidable)
		return;

	Future* future = dynamic_cast<Future*>(m_MyOwnerDeck);
	if (future)
	{
		CardTexture* cardTexture = GetComponent<CardTexture>();
		cardTexture->SetIsFutureRender(false);
		cardTexture->SetIsCardRender(true);
		GetComponent<McCol::Transform>()->SetScale({ 1.0f, 1.0f });
		GetComponent<McCol::OBB>()->SetColliScaleOffset({ 1.f, 1.0f });
	}

}

void PlayCard::HandleCollisionExit(McCol::Collider* otherCollider)
{
	Card::HandleCollisionExit(otherCollider);
	if (!m_Iscollidable)
		return;

	Future* future = dynamic_cast<Future*>(m_MyOwnerDeck);
	if (future)
	{
		CardTexture* cardTexture = GetComponent<CardTexture>();
		cardTexture->SetIsFutureRender(true);
		cardTexture->SetIsCardRender(false);
		GetComponent<McCol::Transform>()->SetScale({ 0.5f, 0.5f });
		GetComponent<McCol::OBB>()->SetColliScaleOffset({ 1.0f, 1.0f });
		future->SetOnMouseCard(nullptr);
	}
}

void PlayCard::InitializePlayCard(Rarity rarity, CharacterType ct, CardType caT)
{
	InitializeCard(ct, caT);
	m_Rarity = rarity;
}

void PlayCard::Play(GameObject* targetObj)
{
}

int PlayCard::GetInitiative() const
{
	if (!GetAttribute(Attribute::INITIATIVE))
		return 0;

	return GetAttribute(Attribute::INITIATIVE)->GetValue();
}

void PlayCard::SetInitiative(int value)
{
	GetAttribute(Attribute::INITIATIVE)->SetValue(value);
}

std::map<Destination, CardInfo> PlayCard::GetCardInfo()
{
	std::map<Destination, CardInfo> cardInfoToDest;

	std::vector<AttributeParts*> ap = GetComponents<AttributeParts>();

	for (const auto& a : ap)
	{
		cardInfoToDest[a->GetDestination()].Attributes[SIZE(a->GetAttribute())] = a->GetValue();
	}

	std::vector<StateParts*> sp = GetComponents<StateParts>();

	for (const auto& s : sp)
	{
		cardInfoToDest[s->GetDestination()].States[SIZE(s->GetState())] = s->GetDuration();
	}

	return cardInfoToDest;
}

std::wstring PlayCard::MakeString()
{
	std::vector<CardPartsComponent*> cardPartsComponents = GetComponents<CardPartsComponent>();

	std::wstring result = L"";
	std::wstring attackCountString = L"";
	std::wstring keywordString = L"";

	for (auto it = cardPartsComponents.begin(); it != cardPartsComponents.end(); ++it)
	{
		auto cpc = *it;

		AttributeParts* ap = dynamic_cast<AttributeParts*>(cpc);

		if (ap && ap->GetAttribute() == Attribute::INITIATIVE)
		{
			continue;
		}
		if (typeid(*cpc) == typeid(KeywordParts))
		{
			keywordString = cpc->ExtractString();
			continue;
		}
		else if (ap && ap->GetAttribute() == Attribute::ATTACK_COUNT)
		{
			attackCountString = ap->ExtractString();
		}
		else
		{
			result += cpc->ExtractString();
			if (std::next(it) != cardPartsComponents.end())
			{
				result += L'\n';
			}
		}
	}
	if (attackCountString != L"")
	{
		if (result.back() != L'\n')
			result += L'\n';
		result += attackCountString;
	}

	if (keywordString != L"")
	{
		result = keywordString + L'\n' + result;
	}

	std::vector<CardFuncComponent*> cardFuncComponents = GetComponents<CardFuncComponent>();

	if (!cardFuncComponents.empty())
	{
		for (auto cfc : cardFuncComponents)
		{
			result += L'\n' + cfc->ExtractString();
		}
	}

	return result;
}
