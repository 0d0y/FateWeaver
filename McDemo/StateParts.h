#pragma once
#include "CardPartsComponent.h"
#include "Elements.h"

class StateParts :
    public CardPartsComponent
{
private:
    State m_State;
    int m_Duration;
    Destination m_Destination;

    State m_OriginState;
    int m_OriginDuration;
    Destination m_OriginDestination;

public:
    StateParts(McCol::GameObject* owner);
    ~StateParts();

    void InitializeStateParts(State state, int duration, Destination destination = Destination::NONE);
    void Initialize() override;

public:
    void SetState(State state);
    State GetState() const;

    void SetDuration(int duration);
    int GetDuration() const;

    void SetDestination(Destination destination);
    Destination GetDestination() const;

    std::wstring ExtractString() override;

    void SetOriginValue() override;
    void ResetToOriginValue() override;
};

