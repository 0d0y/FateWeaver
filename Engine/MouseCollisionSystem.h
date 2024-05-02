#pragma once
#include "CollisionSystem.h"

namespace McCol
{
	class Collider;

	class MouseCollisionSystem :
		public CollisionSystem
	{
	private:
		Collider* m_MouseOBB;

		static MouseCollisionSystem* m_Instance;

		MouseCollisionSystem();
	public:

		MouseCollisionSystem(const MouseCollisionSystem&) = delete;
		MouseCollisionSystem& operator=(const MouseCollisionSystem&) = delete;

		static MouseCollisionSystem* GetInstance();

		void Update(const float& deltaTime) override;

		void SetMouseOBB(Collider* mouseOBB);
	};
}

