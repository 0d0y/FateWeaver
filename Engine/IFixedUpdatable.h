#pragma once

namespace McCol
{
	class IFixedUpdatable
	{
	public:
		virtual ~IFixedUpdatable() = default;
		virtual void FixedUpdate(const float& deltaTime) = 0;
	};
}