#include "pch.h"
#include "AABB.h"
#include "Transform.h"

McCol::AABB::AABB(GameObject* owner)
	: Collider(owner)
{
	m_Name = stringToWstring(typeid(*this).name());
}

McCol::AABB::~AABB()
{

}

bool McCol::AABB::CheckCollision(Collider* other)
{
	AABB* otherAABB = dynamic_cast<AABB*>(other);
	if (!otherAABB)
		return false;

	D2D1_RECT_F thisRect;

	thisRect.left = m_WorldMatrix.dx - m_Size.x / 2.f;
	thisRect.top = m_WorldMatrix.dy - m_Size.y / 2.f;
	thisRect.right = m_WorldMatrix.dx + m_Size.x / 2.f;
	thisRect.bottom = m_WorldMatrix.dy + m_Size.y / 2.f;

	D2D1_RECT_F otherRect;
	D2D1_MATRIX_3X2_F otherMatrix = other->GetMatrix();
	Vector2 otherSize = other->GetSize();

	otherRect.left = otherMatrix.dx - otherSize.x / 2.f;
	otherRect.top = otherMatrix.dy - otherSize.y / 2.f;
	otherRect.right = otherMatrix.dx + otherSize.x / 2.f;
	otherRect.bottom = otherMatrix.dy + otherSize.y / 2.f;

	if (thisRect.left < otherRect.right &&
		thisRect.right > otherRect.left &&
		thisRect.top < otherRect.bottom &&
		thisRect.bottom > otherRect.top)
	{
		return true;
	}

	return false;
}

void McCol::AABB::Initialize()
{
	__super::Initialize();
}

void McCol::AABB::FixedUpdate(const float& deltaTime)
{
	if (m_OwnerTransform)
	{
		m_WorldMatrix = m_OwnerTransform->GetMatrix() * m_LocalMatrix;
	}
	//m_color = D2D1::ColorF(D2D1::ColorF::Blue);
}


