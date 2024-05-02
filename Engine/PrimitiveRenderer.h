#pragma once
#include "BaseRenderer.h"

namespace McCol
{
	class PrimitiveRenderer : public McCol::BaseRenderer
	{
	public:
		PrimitiveRenderer(GameObject* owner);
		~PrimitiveRenderer() override;

	private:
		D2D1_RECT_F m_Rectangle;
		D2D1_POINT_2F m_Center;
		D2D1_ELLIPSE m_Ellipse;
		D2D1_POINT_2F m_Start;
		D2D1_POINT_2F m_End;
		ID2D1SolidColorBrush* m_Brush;
		D2D1_COLOR_F m_BrushColor;
		float m_PmScale;

		bool m_IsRectangle;
		bool m_IsEllipse;

	public:
		void Initialize() override;
		void Render(D2DRender* renderer) override;

	public:
		void SetPmRectangle(const float& width, const float& height);
		void SetPmRectangle(const D2D1_RECT_F& rect);
		void SetPmEllipse(const float& centerX, const float& centerY, const float& radiusX, const float& radiusY);
		void SetPmLine(const float& startX, const float& startY, const float& endX, const float& endY);
		void SetPmBrushColor(D2D1::ColorF brushcolor);
		void SetPmScale(const float& pmScale);

		D2D1_RECT_F GetPmRectangle();
		D2D1_ELLIPSE GetPmEllipse();
		float GetPmScale();
	};
}

