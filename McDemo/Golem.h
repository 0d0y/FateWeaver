#pragma once
#include "Character.h"

class Golem : public Character
{
public:
	Golem(CharacterIndex battleIndex);
	~Golem() override = default;

private:
	static int m_GolemImpending;

public:
	void Initialize() override;
	void GetWill(int count);
};
