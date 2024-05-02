#include "pch.h"
#include "TextureRenderer.h"
#include "Transform.h"
#include "CameraSystem.h"

#include "../RenderEngine/D2DRender.h"
#include "../RenderEngine/D2DTextureSystem.h"

McCol::TextureRenderer::TextureRenderer(GameObject* owner)
	: BaseRenderer(owner)
{
	m_Name = stringToWstring(typeid(*this).name());
}

McCol::TextureRenderer::~TextureRenderer()
{
}

void McCol::TextureRenderer::Initialize()
{
	BaseRenderer::Initialize();
}

void McCol::TextureRenderer::Render(D2DRender* renderer)
{
	const auto& textureScale = D2D1::Matrix3x2F::Scale(m_TextureScale.x, m_TextureScale.y);

	renderer->GetContext()->SetTransform(textureScale * m_pTransform->GetMatrix() * CameraSystem::GetInstance()->GetCameraMatrix());

	const D2D1_RECT_F dstRect = {
		(m_Offset.x - ((m_SrcRect.right - m_SrcRect.left) / 2)),
		(m_Offset.y + ((m_SrcRect.bottom - m_SrcRect.top) / 2)), // 위쪽이 양의 방향
		(m_Offset.x + ((m_SrcRect.right - m_SrcRect.left) / 2)),
		(m_Offset.y - ((m_SrcRect.bottom - m_SrcRect.top) / 2))  // 아래쪽이 음의 방향
	};

	renderer->GetContext()->DrawBitmap(m_d2dBitmap, dstRect, m_Opacity);
}

D2D1_SIZE_F McCol::TextureRenderer::GetRenderSize()
{
	return { m_d2dBitmap->GetSize().width * m_TextureScale.x,  m_d2dBitmap->GetSize().height * m_TextureScale.y };
}

ID2D1Bitmap* McCol::TextureRenderer::GetBitmap()
{
	return m_d2dBitmap;
}

void McCol::TextureRenderer::SetBitmap(ID2D1Bitmap* bitmap)
{
	m_d2dBitmap = bitmap;
	SetSrcRect(0.f, 0.f, m_d2dBitmap->GetSize().width, m_d2dBitmap->GetSize().height);
}

void McCol::TextureRenderer::LoadTexture(std::wstring_view filePath, std::wstring_view key)
{
	m_d2dBitmap = D2DTextureSystem::GetInstance()->LoadTexture(filePath.data(), key);
	SetSrcRect(0.f, 0.f, m_d2dBitmap->GetSize().width, m_d2dBitmap->GetSize().height);
}

void McCol::TextureRenderer::GetTexture(std::wstring_view key)
{
	m_d2dBitmap = D2DTextureSystem::GetInstance()->GetTexture(key);
	SetSrcRect(0.f, 0.f, m_d2dBitmap->GetSize().width, m_d2dBitmap->GetSize().height);
}

void McCol::TextureRenderer::SetTextureScale(const float& scale)
{
	m_TextureScale = { scale, scale };
}

