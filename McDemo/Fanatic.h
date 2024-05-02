#pragma once
#include "Character.h"

class Fanatic : public Character
{
public:
	Fanatic(CharacterIndex battleIndex);
	~Fanatic() override = default;

private:
	static int m_ImpendingCount;
	static int m_WillCount;

public:
	void Initialize() override;
	void GetImpending(int count);
	void GetWill(int count);
};
