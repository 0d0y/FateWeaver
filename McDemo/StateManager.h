#pragma once
#include "../Engine/Component.h"
#include "../Engine/EventHandler.h"

#include "Elements.h"

class Character;

class StateManager : public McCol::Component, public McCol::IRenderable, public McCol::EventHandler
{
public:
	StateManager(McCol::GameObject* owner);
	~StateManager() override;

private:
	int m_CharacterStates[SIZE(State::END)];

public:
	void Initialize() override;
	void Render(McCol::D2DRender* renderer) override;

	void SendCard(CardInfo& info);
	//void ReceiveCard(CardInfo& info);

	bool IsState(State state);

	void SetState(State state, int count);
	void TakeState(CardInfo& info);
	void ApplyQuickState(int& damage);

private:
	void AddState(const CardInfo& info);

	// Event Func
	void EndTurn(std::any publisher);

public:
};
