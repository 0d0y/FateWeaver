#pragma once
#include "Character.h"

class Stalker : public Character
{
public:
	Stalker(CharacterIndex battleIndex);
	~Stalker() override = default;
	void Initialize() override;
};
