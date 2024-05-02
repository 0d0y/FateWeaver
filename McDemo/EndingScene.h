#pragma once
#include "../Engine/Scene.h"

class EndingScene : public McCol::Scene
{
public:
	explicit EndingScene()
		: Scene(L"Ending Scene")
	{
	}
private:



public:
	void Enter() override;
	void Exit() override;
};
