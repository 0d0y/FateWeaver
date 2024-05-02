#pragma once
#include "Character.h"

class Monster : public Character
{
public:
	Monster(CharacterIndex battleIndex);
	~Monster() override = default;
};
