#include "ValueMod.h"
#include "Card.h"
#include "FateCard.h"
#include "Elements.h"
#include "AttributeParts.h"
#include "GameManager.h"

ValueMod::ValueMod(McCol::GameObject* owner)
	: CardFuncComponent(owner)
	, m_AttributeTarget(Attribute::NONE)
	, m_Operation(Operation::NONE)
	, m_ValueToModify(0)
{
}

ValueMod::~ValueMod()
{
}

void ValueMod::Initialize()
{
}

void ValueMod::InitializeValueMod(Attribute attr, Operation op, int value, CardType targetCard)
{
	m_AttributeTarget = attr;
	m_Operation = op;
	m_ValueToModify = value;
	m_TargetCard = targetCard;
}

Operation ValueMod::GetOperation() const
{
	return m_Operation;
}

void ValueMod::SetOperation(Operation operation)
{
	m_Operation = operation;
}

int ValueMod::GetValueToModify() const
{
	return m_ValueToModify;
}

void ValueMod::SetValueToModify(int valueToModify)
{
	m_ValueToModify = valueToModify;
}

void ValueMod::ApplyEffect(McCol::GameObject* targetObj)
{
	Card* targetCard = dynamic_cast<Card*>(targetObj);

	if (targetCard /* && targetCard->GetCardType() == m_TargetCard*/)
	{
		AttributeParts* AttributeTarget = targetCard->GetAttribute(m_AttributeTarget);

		//파멸의 예언
		if (m_AttributeTarget == Attribute::VALUE)
		{
			std::vector<ValueMod*> cfcs = targetCard->GetComponents<ValueMod>();

			if (!cfcs.empty())
			{
				for (auto cfc : cfcs)
				{
					if (cfc->GetAttribute() == Attribute::INITIATIVE)
						continue;
					else
					{
						cfc->SetValueToModify(cfc->GetValueToModify() * 2);
					}
				}
				if (dynamic_cast<FateCard*>(GetOwner())->IsParadox())
				{
					for (auto cfc : cfcs)
					{
						cfc->SetOriginValue();
					}
				}
			}
		}

		if (AttributeTarget)
		{
			switch (m_Operation)
			{
			case Operation::ADD:
			{
				AttributeTarget->SetValue(AttributeTarget->GetValue() + m_ValueToModify);
				break;
			}
			case Operation::SUB:
			{
				AttributeTarget->SetValue(AttributeTarget->GetValue() - m_ValueToModify);
				break;
			}
			case Operation::MUL:
			{
				AttributeTarget->SetValue(AttributeTarget->GetValue() * m_ValueToModify);
			}
			break;
			case Operation::DIV:
			{
				if (m_ValueToModify != 0)
				{
					AttributeTarget->SetValue(AttributeTarget->GetValue() / m_ValueToModify);
				}
			}
			break;
			case Operation::SET:
			{
				AttributeTarget->SetValue(m_ValueToModify);
			}
			break;
			}
			if (dynamic_cast<FateCard*>(GetOwner())->IsParadox())
				AttributeTarget->SetOriginValue();
		}
	}
}


std::wstring ValueMod::ExtractString()
{
	std::wstring result;

	std::wstring targetCardstring;
	switch (m_TargetCard)
	{
	case CardType::NONE:
		targetCardstring = L"즉시";
		break;
	case CardType::PLAYER_PLAY_CARD:
		targetCardstring = L"내 행동 카드";
		break;
	case CardType::PLAYER_FATE_CARD:
		targetCardstring = L"운명 카드";
		break;
	case CardType::ENEMY_PLAY_CARD:
		targetCardstring = L"적 행동 카드";
		break;
	case CardType::PLAY_CARD:
		targetCardstring = L"행동 카드";
		break;
	default:
		break;
	}

	std::wstring attributeTargetString;
	switch (m_AttributeTarget)
	{
	case Attribute::NONE:
		attributeTargetString = L"";
		break;
	case Attribute::INITIATIVE:
		attributeTargetString = L"주도력";
		break;
	case Attribute::DAMAGE:
		attributeTargetString = L"데미지";
		break;
	case Attribute::DEFENSE:
		attributeTargetString = L"방어도";
		break;
	case Attribute::ATTACK_COUNT:
		attributeTargetString = L"공격 횟수";
		break;
	case Attribute::FATE_ENERGY:
		attributeTargetString = L"운명 에너지";
		break;
	case Attribute::VALUE:
		attributeTargetString = L"모든 수정치";
		break;
	case Attribute::END:
		attributeTargetString = L"";
		break;
	default:
		break;
	}

	std::wstring OperationString;
	switch (m_Operation)
	{
	case Operation::NONE:
		OperationString = L"";
		break;
	case Operation::ADD:
		OperationString = L"+";
		break;
	case Operation::SUB:
		OperationString = L"-";
		break;
	case Operation::MUL:
		OperationString = L"×";
		break;
	case Operation::DIV:
		OperationString = L"÷";
		break;
	default:
		OperationString = L"";
		break;
	}

	FateCard* owner = dynamic_cast<FateCard*>(GetOwner());

	if (owner->GetName() == L"운명 절단" || owner->GetName() == L"미래 예지" || owner->GetName() == L"가능성 개화")
	{
		if (m_AttributeTarget == Attribute::DAMAGE)
		{
			return attributeTargetString + L' ' + OperationString + std::to_wstring(m_ValueToModify);
		}
	}

	if (!owner)
		result = L"";
	else if (m_AttributeTarget == Attribute::DEFENSE && m_Operation == Operation::SET)
	{
		return L"대상의 방어도를 0으로 한다.";
	}


	result += targetCardstring + L'\n' + attributeTargetString + L' ' + OperationString + std::to_wstring(m_ValueToModify);

	if (owner->GetName() == L"효율 증가")
	{
		result += L"\n패러독스 기능이\n추가될 수 없습니다.";
	}

	return result;
}

void ValueMod::SetOriginValue()
{
	m_OriginAttributeTarget = m_AttributeTarget;
	m_OriginOperation = m_Operation;
	m_OriginValueToModify = m_ValueToModify;
	m_OriginTargetCard = m_TargetCard;

}

void ValueMod::ResetToOriginValue()
{
	m_AttributeTarget = m_OriginAttributeTarget;
	m_Operation = m_OriginOperation;
	m_ValueToModify = m_OriginValueToModify;
	m_TargetCard = m_OriginTargetCard;
}
