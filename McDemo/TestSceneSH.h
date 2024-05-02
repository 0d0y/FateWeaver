#pragma once
#include "../Engine/Scene.h"

class Future;

class TestSceneSH : public McCol::Scene
{
public:
	TestSceneSH();
	~TestSceneSH() override;

private:
	//Future* m_FutureArea;

	void Enter() override;
	void Exit() override;

	void Update(const float& deltaTime) override;
};
