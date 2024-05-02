#include "StateParts.h"

StateParts::StateParts(McCol::GameObject* owner)
	: CardPartsComponent(owner)
	, m_State(State::NONE)
	, m_Duration(0)
	, m_Destination(Destination::NONE)
{
}

StateParts::~StateParts()
{
}

void StateParts::InitializeStateParts(State state, int duration, Destination destination)
{
	m_State = state;
	m_Duration = duration;
	m_Destination = destination;
}

void StateParts::Initialize()
{
}

void StateParts::SetState(State state)
{
	m_State = state;
}

State StateParts::GetState() const
{
	return m_State;
}

void StateParts::SetDuration(int duration)
{
	m_Duration = duration;
}

int StateParts::GetDuration() const
{
	return m_Duration;
}

void StateParts::SetDestination(Destination destination)
{
	m_Destination = destination;
}

Destination StateParts::GetDestination() const
{
	return m_Destination;
}

std::wstring StateParts::ExtractString()
{
	std::wstring result;

	std::wstring stateString;
	switch (m_State)
	{
	case State::NONE:
		stateString = L"";
		break;
	case State::QUICK:
		stateString = L"재빠름";
		break;
	case State::DISRUPTION:
		stateString = L"흐트러짐";
		break;
	case State::CONFUSION:
		stateString = L"혼란";
		break;
	case State::ENCHANTMENT:
		stateString = L"마력 충전";
		break;
	case State::STUNNED:
		stateString = L"기절";
		break;
	case State::IMPENDING_RUIN:
		stateString = L"파멸의 예언 : 패러독스";
		break;
	case State::WILL_OF_RUIN:
		stateString = L"파멸의 의지 : 패러독스";
		break;
	case State::ENGINE_OVERLOAD:
		stateString = L"파멸의 예언 : 패러독스";
		break;
	case State::END:
		stateString = L"";
		break;
	default:
		stateString = L"";
		break;
	}

	std::wstring destinationString;
	switch (m_Destination)
	{
	case Destination::NONE:
		destinationString = L"";
		break;
	case Destination::PLAYER:
		destinationString = L"플레이어";
		break;
	case Destination::SELF:
		destinationString = L"자기 자신";
		break;
	case Destination::NEAREST_ENEMY:
		destinationString = L"가장 앞의 적";
		break;
	case Destination::FARTHEST_ENEMY:
		destinationString = L"가장 뒤의 적";
		break;
	case Destination::ALL_ENEMIES:
		destinationString = L"모든 적";
		break;
	default:
		destinationString = L"";
		break;
	}

	if (m_State == State::IMPENDING_RUIN ||
		m_State == State::WILL_OF_RUIN ||
		m_State == State::ENGINE_OVERLOAD)
	{
		result = stateString;
	}
	else
		result = destinationString + L" " + stateString + L" : " + std::to_wstring(m_Duration) + L" 턴";

	return result;
}

void StateParts::SetOriginValue()
{
}

void StateParts::ResetToOriginValue()
{
}

