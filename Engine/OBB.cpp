#include "pch.h"
#include "OBB.h"
#include "Transform.h"
#include <cmath>
#include <limits>

McCol::OBB::OBB(GameObject* owner)
	: Collider(owner)
{
	m_Name = stringToWstring(typeid(*this).name());
}

McCol::OBB::~OBB()
{

}


bool McCol::OBB::CheckCollision(Collider* other)
{
	OBB* otherOBB = dynamic_cast<OBB*>(other);
	if (!otherOBB)
		return false;

	Vector2 thisAxes[] = { Vector2(m_WorldMatrix._11, m_WorldMatrix._12), Vector2(m_WorldMatrix._21, m_WorldMatrix._22) };
	Vector2 otherAxes[] = { Vector2(otherOBB->GetMatrix()._11, otherOBB->GetMatrix()._12), Vector2(otherOBB->GetMatrix()._21, otherOBB->GetMatrix()._22) };

	Vector2 axes[4] = { thisAxes[0], thisAxes[1], otherAxes[0], otherAxes[1] };

	for (int i = 0; i < 4; ++i)
	{
		Vector2 axis = axes[i].Perpendicular();

		float thisMin = (std::numeric_limits<float>::max)();
		float thisMax = -(std::numeric_limits<float>::max)();
		float otherMin = (std::numeric_limits<float>::max)();
		float otherMax = -(std::numeric_limits<float>::max)();

		for (int j = 0; j < 4; ++j)
		{
			float thisProjection = this->GetVertex(j).Dot(axis);
			float otherProjection = otherOBB->GetVertex(j).Dot(axis);

			thisMin = std::min<float>(thisMin, thisProjection);
			thisMax = std::max<float>(thisMax, thisProjection);
			otherMin = std::min<float>(otherMin, otherProjection);
			otherMax = std::max<float>(otherMax, otherProjection);
		}

		if (!(thisMin <= otherMax && thisMax >= otherMin))
			return false;
	}

	return true;
}

McCol::Vector2 McCol::OBB::GetVertex(int index) const
{
	float halfWidth = m_Size.x* m_ColliScaleOffset.x / 2.0f;
	float halfHeight = m_Size.y* m_ColliScaleOffset.y / 2.0f;

	Vector2 localVertex;

	switch (index)
	{
	case 0: localVertex = Vector2(-halfWidth, -halfHeight); break;
	case 1: localVertex = Vector2(halfWidth, -halfHeight); break;
	case 2: localVertex = Vector2(-halfWidth, halfHeight); break;
	case 3: localVertex = Vector2(halfWidth, halfHeight); break;
	default: localVertex = Vector2(); break;
	}

	Vector2 worldVertex;
	worldVertex.x = m_WorldMatrix._11 * localVertex.x + m_WorldMatrix._21 * localVertex.y + m_WorldMatrix.dx;
	worldVertex.y = m_WorldMatrix._12 * localVertex.x + m_WorldMatrix._22 * localVertex.y + m_WorldMatrix.dy;

	return worldVertex;
}


void McCol::OBB::Initialize()
{
	__super::Initialize();
}

void McCol::OBB::FixedUpdate(const float& deltaTime)
{
	if (m_OwnerTransform)
	{
		m_WorldMatrix = m_OwnerTransform->GetMatrix() * m_LocalMatrix;
	}
	//m_color = D2D1::ColorF(D2D1::ColorF::Blue);
}