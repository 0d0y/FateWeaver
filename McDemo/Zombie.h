#pragma once
#include "Character.h"

class Zombie : public Character
{
public:
	Zombie(CharacterIndex battleIndex);
	~Zombie() override = default;
};
