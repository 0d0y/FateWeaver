#pragma once

namespace McCol
{
	class Collider;
	class ICollidable
	{
	public:
		virtual ~ICollidable() = default;
		virtual void HandleCollisionStay(Collider* otherCollider) = 0;
		virtual void HandleCollisionEnter(Collider* otherCollider) = 0;
		virtual void HandleCollisionExit(Collider* otherCollider) = 0;
	};
}
