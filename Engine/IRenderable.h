#pragma once

namespace McCol
{
	class D2DRender;

	class IRenderable
	{
	public:
		virtual ~IRenderable() = default;
		virtual void Render(D2DRender* renderer) = 0;
	};
}
