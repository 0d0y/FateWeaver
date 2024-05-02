#include "DestinationMod.h"
#include "Card.h"
#include "FateCard.h"
#include "Elements.h"
#include "AttributeParts.h"

#include <vector>

DestinationMod::DestinationMod(McCol::GameObject* owner)
	: CardFuncComponent(owner)
	, m_DestinationTarget(CardType::NONE)
	, m_DestinationToModify(Destination::NONE)
{
}

DestinationMod::~DestinationMod()
{
}

void DestinationMod::InitializeDestinationMod(CardType destinationTarget, Destination destinationToModify)
{
	m_DestinationTarget = destinationTarget;
	m_DestinationToModify = destinationToModify;
}

void DestinationMod::Initialize()
{
}

void DestinationMod::ApplyEffect(McCol::GameObject* targetObj)
{
	Card* targetCard = dynamic_cast<Card*>(targetObj);

	if (targetCard && targetCard->GetCardType() == m_DestinationTarget)
	{
		std::vector<AttributeParts*> Atrributes = targetCard->GetAttributes();
		if (!Atrributes.empty())
		{
			for (auto ap : Atrributes)
			{
				if (ap->GetDestination() != Destination::SELF
					|| ap->GetDestination() != m_DestinationToModify)
					ap->SetDestination(m_DestinationToModify);
			}
		}
		if (dynamic_cast<FateCard*>(GetOwner())->IsParadox())
		{
			for (auto ap : Atrributes)
			{
				ap->SetOriginValue();
			}

		}


	}
}

std::wstring DestinationMod::ExtractString()
{
	std::wstring result;

	std::wstring destinationToModifyString;
	switch (m_DestinationToModify)
	{
	case Destination::NONE:
		destinationToModifyString = L"";
		break;
	case Destination::NEAREST_ENEMY:
		destinationToModifyString = L"대상 수정 : 가장 앞에 있는 아군";
		break;
	case Destination::FARTHEST_ENEMY:
		destinationToModifyString = L"대상 수정 : 맨 뒤의 적";
		break;
	case Destination::ALL_ENEMIES:
		destinationToModifyString = L"대상 수정 : 모든 적";
		break;
	case Destination::SELF:
		destinationToModifyString = L"대상 수정 : 자기 자신";
		break;
	default:
		break;
	}

	std::wstring targetCardType;
	switch (m_DestinationTarget)
	{
	case CardType::NONE:
		targetCardType = L"즉시";
		break;
	case CardType::PLAYER_PLAY_CARD:
		targetCardType = L"내 행동 카드";
		break;
	case CardType::PLAYER_FATE_CARD:
		targetCardType = L"운명 카드";
		break;
	case CardType::ENEMY_PLAY_CARD:
		targetCardType = L"적 행동 카드";
		break;
	case CardType::PLAY_CARD:
		targetCardType = L"행동 카드";
		break;
	default:
		break;
	}


	result = targetCardType + L"\n" + destinationToModifyString;

	return result;
}

void DestinationMod::SetOriginValue()
{
}

void DestinationMod::ResetToOriginValue()
{
}
