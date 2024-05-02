#include "FateCard.h"
#include "ValueMod.h"
#include "Hand.h"
#include "KeywordParts.h"

#include <vector>
#include <algorithm>

#include "../Engine/Transform.h"
#include "../Engine/Obb.h"
#include "../Engine/Collider.h"
#include "../Engine/CameraSystem.h"
#include "../Engine/TextureRenderer.h"
#include "../RenderEngine/D2DRender.h"

using namespace McCol;

FateCard::FateCard(std::wstring_view name)
	: Card(name)
	, m_Cost(0)
	, m_IsParadox(false)
	, m_HandOrder(-1)
{
}

FateCard::~FateCard()
{
}

void FateCard::HandleCollisionStay(McCol::Collider* otherCollider)
{
	Card::HandleCollisionStay(otherCollider);
	if (!m_Iscollidable)
		return;

	Hand* handDeck = dynamic_cast<Hand*>(m_MyOwnerDeck);
	std::vector<int> collidingCardIndex;

	if (handDeck)
	{
		collidingCardIndex = handDeck->GetCollidingCardIndex();
		find(collidingCardIndex.begin(), collidingCardIndex.end(), m_HandOrder);
		if (collidingCardIndex.end() == find(collidingCardIndex.begin(), collidingCardIndex.end(), m_HandOrder))
		{
			handDeck->PushBackCollidingCardIndex(m_HandOrder);
		}
	}

	if (handDeck)
	{
		std::vector<int> collidingCardIndex = handDeck->GetCollidingCardIndex();
		for (int index : collidingCardIndex)
		{
			if ((index != m_HandOrder && index > m_HandOrder) || handDeck->GetClickedCard() == this)
			{
				return;
			}
		}
		handDeck->SetOnMouseCard(this);
	}
}

void FateCard::HandleCollisionEnter(McCol::Collider* otherCollider)
{
	Card::HandleCollisionEnter(otherCollider);
	if (!m_Iscollidable)
		return;

	Hand* handDeck = dynamic_cast<Hand*>(m_MyOwnerDeck);
	if (handDeck)
	{
		std::vector<int> collidingCardIndex = handDeck->GetCollidingCardIndex();

		for (int index : collidingCardIndex)
		{
			if (index != m_HandOrder && index > m_HandOrder)
			{
				return;
			}
		}
	}
}

void FateCard::HandleCollisionExit(McCol::Collider* otherCollider)
{
	Card::HandleCollisionExit(otherCollider);
	if (!m_Iscollidable)
		return;

	Hand* handDeck = dynamic_cast<Hand*>(m_MyOwnerDeck);
	if (handDeck)
	{
		handDeck->ResetCollidingCardIndex();
		handDeck->SetOnMouseCard(nullptr);
	}
}


void FateCard::SetHandOrder(int handOrder)
{
	m_HandOrder = handOrder;
}

int FateCard::GetHandOrder() const
{
	return m_HandOrder;
}

McCol::GameObject* FateCard::GetMyOwnerDeck() const
{
	return m_MyOwnerDeck;
}

void FateCard::Play(GameObject* targetObj)
{
	for (McCol::Component* co : m_Components)
	{
		CardFuncComponent* cc = dynamic_cast<CardFuncComponent*>(co);
		if (cc)
		{
			cc->ApplyEffect(targetObj);
		}
	}
}

void FateCard::InitializeFateCard(Rarity rarity, int cost, CharacterType chT, CardType caT, bool isParadox)
{
	InitializeCard(chT, caT);
	m_Rarity = rarity;
	m_Cost = cost;
	m_IsParadox = isParadox;
}

void FateCard::ParadoxOn()
{
	m_IsParadox = true;
}

std::wstring FateCard::MakeString()
{
	std::vector<CardFuncComponent*> cardFuncComponents = GetComponents<CardFuncComponent>();
	KeywordParts* kp = GetComponent<KeywordParts>();
	std::wstring keywordString = L"";
	std::wstring result;

	for (auto it = cardFuncComponents.begin(); it != cardFuncComponents.end(); ++it)
	{
		auto cfc = *it;
		result += cfc->ExtractString();

		if (std::next(it) != cardFuncComponents.end())
		{
			result += L'\n';
		}

	}
	//if (m_Name == L"고대의 회중시계")
	//{
	//	result += L"운명 카드를\n패러독스 카드로\n만듭니다.";
	//}
	if (kp)
	{
		result += L'\n' + kp->ExtractString();
	}

	if (m_IsParadox)
	{
		result += L"\n패러독스";
	}


	return result;
}

std::wstring FateCard::GetCostString() const
{
	return std::to_wstring(m_Cost);
}
