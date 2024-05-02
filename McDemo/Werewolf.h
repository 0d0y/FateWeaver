#pragma once
#include "Character.h"

class Werewolf : public Character
{
public:
	Werewolf(CharacterIndex battleIndex);
	~Werewolf() override = default;
	void Initialize() override;
};
