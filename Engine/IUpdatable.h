#pragma once

namespace McCol
{
	class IUpdatable
	{
	public:
		virtual ~IUpdatable() = default;
		virtual void Update(const float& deltaTime) = 0;
	};
}