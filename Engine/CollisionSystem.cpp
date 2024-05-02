#include "pch.h"
#include "CollisionSystem.h"
#include "Collider.h"
#include "../McDemo/Card.h"

McCol::CollisionSystem* McCol::CollisionSystem::m_Instance = nullptr;

McCol::CollisionSystem::CollisionSystem()
{
}

McCol::CollisionSystem* McCol::CollisionSystem::GetInstance()
{
    if (m_Instance == nullptr)
        m_Instance = new CollisionSystem;

    return m_Instance;
}

void McCol::CollisionSystem::AddCollider(Collider* collider)
{
    m_Colliders.push_back(collider);
}

void McCol::CollisionSystem::RemoveCollider(Collider* collider)
{
    auto it = std::find(m_Colliders.begin(), m_Colliders.end(), collider);
    if (it != m_Colliders.end())
    {
        m_Colliders.erase(it);
    }
}

void McCol::CollisionSystem::Update(const float& deltaTime)
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

            if (IsBothCards(collider, otherCollider))
            {
                continue;
            }

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

bool McCol::CollisionSystem::IsBothCards(Collider* collider1, Collider* collider2)
{
    GameObject* obj1 = collider1->GetOwner();
    GameObject* obj2 = collider2->GetOwner();

    return (dynamic_cast<Card*>(obj1) != nullptr) && (dynamic_cast<Card*>(obj2) != nullptr);
}

void McCol::CollisionSystem::Finalize()
{
    SAFE_DELETE(m_Instance);
}

void McCol::CollisionSystem::Initialize()
{
    EventSystem::GetInstance()->Subscribe(L"CHANGE_SCENE", MakeListenerInfo(&CollisionSystem::Clear));
}

void McCol::CollisionSystem::Clear(std::any param)
{
    m_Colliders.clear();
}
