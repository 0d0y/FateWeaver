#pragma once
#include "..\Engine\GameObject.h"
#include "..\Engine\Vector2.h"
#include <d2d1.h>

class Card;

class Mouse :
	public McCol::GameObject
{
private:
	bool m_IsMouseVisible;
	McCol::Vector2 m_Pos;
	McCol::Vector2 m_Size;
	D2D1_RECT_F m_CollisionArea;

	Card* m_CollidingCard;

public:
	Mouse(std::wstring_view name);
	~Mouse() override;

public:
	void Initialize() override;
	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;
	void Render(McCol::D2DRender* renderer) override;
	void HandleCollisionStay(McCol::Collider* otherCollider) override;
	void HandleCollisionEnter(McCol::Collider* otherCollider) override;
	void HandleCollisionExit(McCol::Collider* otherCollider) override;
public:
	void ToggleMouseVisibility();
	Card* GetCollidingCard() const { return m_CollidingCard; }
};

