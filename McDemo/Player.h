#pragma once
#include "Character.h"

class Player : public Character
{
public:
	Player(CharacterIndex battleIndex);
	~Player();

private:
	int m_FateEnergy;

public:
	void Initialize() override;
	void SetFateEnergy(int number);
	int GetFateEnergy();

private:
	void EndTurn(std::any param);
};
