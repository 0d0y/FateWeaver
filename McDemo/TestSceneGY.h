#pragma once
#include "../Engine/Scene.h"
#include "../Engine/GameObject.h"

class FateCard;
class PlayCard;
class Deck;
class Hand;
class CardFactory;

class TestSceneGY
	: public McCol::Scene
{
private:
	McCol::GameObject* m_Camera;
	Hand* m_Hand;

	CardFactory* m_CardFactory;

public:
	TestSceneGY();
	~TestSceneGY() override;

	void Enter() override;
	void Exit() override;

	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
	void Render(McCol::D2DRender* renderer) override;
};