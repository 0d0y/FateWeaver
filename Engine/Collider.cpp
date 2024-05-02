#include "pch.h"
#include "Collider.h"
#include "Transform.h"
#include "BaseRenderer.h"
#include "MouseCollisionSystem.h"
#include <cassert>
#include "../RenderEngine/D2DRender.h"

McCol::Collider::Collider(GameObject* owner)
	: Component(owner)
	, m_ColliPosOffset{ 0.f, 0.f }
	, m_ColliScaleOffset{ 1.0f, 1.0f }
	, m_OwnerTransform(nullptr)
	, m_OwnerRenderer(nullptr)
	, m_LocalMatrix(D2D1::Matrix3x2F::Identity())
	, m_WorldMatrix(m_LocalMatrix)
	, m_CollisionState(CollisionState::None)
	, m_IsColliding(false)
{
	//m_color = D2D1::ColorF(D2D1::ColorF::Blue);
}

McCol::Collider::~Collider()
{
	MouseCollisionSystem::GetInstance()->RemoveCollider(this);
}

void McCol::Collider::Initialize()
{
	m_OwnerTransform = GetOwner()->GetComponent<Transform>();
	assert(m_OwnerTransform);
	m_OwnerRenderer = GetOwner()->GetComponent<BaseRenderer>();

	if (m_OwnerRenderer)
	{
		D2D1_RECT_F TempRect = m_OwnerRenderer->GetSrcRect();
		m_Size = { TempRect.right - TempRect.left , TempRect.bottom - TempRect.top };
	}

	//CollisionSystem::GetInstance()->AddCollider(this);
	MouseCollisionSystem::GetInstance()->AddCollider(this);
}

void McCol::Collider::Render(D2DRender* renderer)
{
	//ID2D1SolidColorBrush* brush;
	//renderer->GetContext()->CreateSolidColorBrush(m_color, &brush);
	//renderer->GetContext()->SetTransform(m_WorldMatrix);
	//renderer->GetContext()->DrawRectangle({ -m_Size.x / 2.f, -m_Size.y / 2.f, m_Size.x / 2.f, m_Size.y / 2.f }, brush);
	//brush->Release();
}

void McCol::Collider::SetColliPosOffset(const Vector2& colliOffset)
{
	m_ColliPosOffset = colliOffset;
	m_LocalMatrix.dx += m_ColliPosOffset.x;
	m_LocalMatrix.dy += m_ColliPosOffset.y;
}

void McCol::Collider::SetColliScaleOffset(const Vector2& colliScale)
{
	m_ColliScaleOffset = colliScale;
}

void McCol::Collider::SetColliding(bool iscolliding)
{
	m_IsColliding = iscolliding;
}

bool McCol::Collider::IsColliding() const
{
	return m_IsColliding;
}

void McCol::Collider::SetCollisionState(CollisionState state)
{
	m_CollisionState = state;
}

void McCol::Collider::ResetCollisionState()
{
	m_CollisionState = CollisionState::None;
}