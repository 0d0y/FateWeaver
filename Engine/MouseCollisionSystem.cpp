#include "pch.h"
#include "MouseCollisionSystem.h"
#include "Collider.h"

McCol::MouseCollisionSystem* McCol::MouseCollisionSystem::m_Instance = nullptr;

McCol::MouseCollisionSystem::MouseCollisionSystem()
	:m_MouseOBB(nullptr)
{
}

McCol::MouseCollisionSystem* McCol::MouseCollisionSystem::GetInstance()
{
	if (m_Instance == nullptr)
		m_Instance = new MouseCollisionSystem;

	return m_Instance;
}

void McCol::MouseCollisionSystem::Update(const float& deltaTime)
{
	for (auto& collider : m_Colliders)
	{
		if (!collider->GetOwner()->IsAble())
			continue;

		collider->ResetCollisionState();
		for (auto& otherCollider : m_Colliders)
		{
			if (collider == otherCollider)
				continue;

			if (collider != m_MouseOBB && otherCollider != m_MouseOBB)
				continue;

			if (collider->CheckCollision(otherCollider))
			{
				if (collider->IsColliding())
				{
					collider->SetCollisionState(Collider::CollisionState::Stay);
					collider->GetOwner()->HandleCollisionStay(otherCollider);
				}
				else
				{
					collider->SetCollisionState(Collider::CollisionState::Enter);
					collider->GetOwner()->HandleCollisionEnter(otherCollider);
				}

				collider->SetColliding(true);
			}
			else if (collider->IsColliding())
			{
				collider->SetCollisionState(Collider::CollisionState::Exit);
				collider->GetOwner()->HandleCollisionExit(otherCollider);
				collider->SetColliding(false);
			}
		}
	}
}

void McCol::MouseCollisionSystem::SetMouseOBB(McCol::Collider* mouseOBB)
{
	m_MouseOBB = mouseOBB;
}

