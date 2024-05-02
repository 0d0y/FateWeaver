#pragma once
#include "Component.h"
#include <d2d1_1.h>

namespace McCol
{
	class Transform;
	class D2DRender;

	class BaseRenderer : public Component, public IFixedUpdatable, public IRenderable
	{
	public:
		BaseRenderer(GameObject* owner);
		~BaseRenderer() override;

	protected:
		Transform* m_pTransform;
		D2D1_RECT_F m_SrcRect;          // 비트맵이 그려지는 범위
		D2D1_VECTOR_2F m_TextureScale;
		D2D1_VECTOR_2F m_Offset;

		float m_Opacity;
		float m_ProgressTime;
		float m_FadeDuration;
		bool m_IsFadeIn;
		bool m_IsFadeOut;
		bool m_IsMakeSmaller;

	public:
		void Initialize() override;
		void FixedUpdate(const float& deltaTime) override;
		void Render(D2DRender* renderer) override;

		D2D1_RECT_F GetSrcRect() const;
		D2D1_VECTOR_2F GetOffset() const;

		void SetSrcRect(const float& left, const float& top, const float& right, const float& bottom);
		void SetSrcRect(const D2D1_RECT_F& srcRect);
		void SetTextureScale(const float& x, const float& y);
		void SetTextureScale(const D2D1_VECTOR_2F& scale);
		void SetOffset(const float& x, const float& y);
		void SetOffset(const D2D1_VECTOR_2F& offset);

		void SetFadeIn(const float& fadeInTime);
		void SetFadeOut(const float& fadeOutTime);
		void SetSmaller(bool isSmaller);

		void SetOpacity(const float& opacity);
	};
}


