#pragma once
#include <vector>
#include "IUpdatable.h"
#include "EventHandler.h"

namespace McCol
{
	class Collider;

	class CollisionSystem
		: public IUpdatable, public EventHandler
	{
	protected:
		std::vector<Collider*> m_Colliders;

		static CollisionSystem* m_Instance;

		CollisionSystem();

	public:

		CollisionSystem(const CollisionSystem&) = delete;
		CollisionSystem& operator=(const CollisionSystem&) = delete;

		static CollisionSystem* GetInstance();

		void AddCollider(Collider* collider);
		void RemoveCollider(Collider* collider);
		virtual void Update(const float& deltaTime) override;

		bool IsBothCards(Collider* collider1, Collider* collider2);

		void Finalize();

		void Initialize();
	private:
		void Clear(std::any param);
	};
}