#include "pch.h"
#include "BaseRenderer.h"
#include "GameObject.h"
#include "Transform.h"
#include "CameraSystem.h"
#include "../RenderEngine/D2DRender.h"

McCol::BaseRenderer::BaseRenderer(GameObject* owner)
	: Component(owner)
	, m_pTransform(nullptr)
	, m_SrcRect{ 0.f, 0.f, 0.f, 0.f }
	, m_TextureScale{ 1.f, 1.f }
	, m_Offset{ 0.f, 0.f }
	, m_Opacity(1)
	, m_ProgressTime(0)
	, m_FadeDuration(0)
	, m_IsFadeIn(false)
	, m_IsFadeOut(false)
{
}

McCol::BaseRenderer::~BaseRenderer()
{
}

void McCol::BaseRenderer::Initialize()
{
	if (GetOwner() == nullptr)
		return;

	m_pTransform = m_Owner->GetComponent<Transform>();
}

void McCol::BaseRenderer::FixedUpdate(const float& deltaTime)
{
	m_ProgressTime += deltaTime;

	// FADE IN
	if (m_IsFadeIn)
	{
		if (m_ProgressTime <= m_FadeDuration)
		{
			m_Opacity = m_ProgressTime / m_FadeDuration; // 0 ~ 1 까지 점점 증가
		}
		else
		{
			m_Opacity = 1.0f; // 최대값으로 설정
			m_IsFadeIn = false; // FadeIn 완료
		}
	}
	// FADE OUT
	else if (m_IsFadeOut)
	{
		if (m_ProgressTime <= m_FadeDuration)
		{
			m_Opacity = 1.0f - (m_ProgressTime / m_FadeDuration); // 1 ~ 0 까지 점점 감소

			if(m_IsMakeSmaller)
				SetTextureScale({ m_Opacity, m_Opacity });
		}
		else
		{
			m_Opacity = 0.0f; // 최소값으로 설정
			SetTextureScale({ 1.0f, 1.0f });
			m_IsFadeOut = false; // FadeOut 완료
		}
	}
}

void McCol::BaseRenderer::Render(D2DRender* renderer)
{
	renderer->GetContext()->SetTransform(m_pTransform->GetMatrix() * CameraSystem::GetInstance()->GetCameraMatrix());
}

void McCol::BaseRenderer::SetSrcRect(const float& left, const float& top, const float& right, const float& bottom)
{
	m_SrcRect = { left, top, right, bottom };
}

void McCol::BaseRenderer::SetSrcRect(const D2D1_RECT_F& srcRect)
{
	m_SrcRect = srcRect;
}

void McCol::BaseRenderer::SetTextureScale(const float& x, const float& y)
{
	m_TextureScale = { x, y };
}

void McCol::BaseRenderer::SetTextureScale(const D2D1_VECTOR_2F& scale)
{
	m_TextureScale = scale;
}

void McCol::BaseRenderer::SetOffset(const float& x, const float& y)
{
	m_Offset = { x, y };
}

void McCol::BaseRenderer::SetOffset(const D2D1_VECTOR_2F& offset)
{
	m_Offset = offset;
}

void McCol::BaseRenderer::SetFadeIn(const float& fadeInTime)
{
	m_FadeDuration = fadeInTime;
	m_Opacity = 0.0f;
	m_IsFadeIn = true;
}

void McCol::BaseRenderer::SetFadeOut(const float& fadeOutTime)
{
	m_FadeDuration = fadeOutTime;
	m_Opacity = 1.0f;
	m_IsFadeOut = true;
}

void McCol::BaseRenderer::SetSmaller(bool isSmaller)
{
	m_IsMakeSmaller = isSmaller;
}

void McCol::BaseRenderer::SetOpacity(const float& opacity)
{
	m_Opacity = opacity;
}

D2D1_RECT_F McCol::BaseRenderer::GetSrcRect() const
{
	return m_SrcRect;
}

D2D1_VECTOR_2F McCol::BaseRenderer::GetOffset() const
{
	return m_Offset;
}



