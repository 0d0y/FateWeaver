#include "pch.h"
#include "TextRenderer.h"

#include <dwrite.h>

#include "Transform.h"
#include "CameraSystem.h"
#include "TextureRenderer.h"
#include "../RenderEngine/D2DRender.h"

#define TEXT_LENGTH(T) static_cast<UINT32>((T).length())

#pragma comment(lib, "dwrite.lib")

McCol::TextRenderer::TextRenderer(GameObject* owner)
	: BaseRenderer(owner)
	, m_Brush(nullptr)
	, m_BrushColor(D2D1::ColorF::Black)
	, m_IsShowLayout(false)
	, m_LayoutRect{}
	, m_LayoutWidth(0.f)
	, m_LayoutHeight(0.f)
	, IsTextChange(true)
	, m_FontWeightIndex(3)
	, m_FontStyleIndex(0)
	, m_FontSize(0.f)
	, m_StartRange(0)
	, m_EndRange(TEXT_LENGTH(m_SrcText))
{
	m_FontWeights[FONT_ENUM(FontWeight::NORMAL)] = DWRITE_FONT_WEIGHT_NORMAL;
	m_FontWeights[FONT_ENUM(FontWeight::LIGHT)] = DWRITE_FONT_WEIGHT_LIGHT;
	m_FontWeights[FONT_ENUM(FontWeight::REGULAR)] = DWRITE_FONT_WEIGHT_REGULAR;
	m_FontWeights[FONT_ENUM(FontWeight::BOLD)] = DWRITE_FONT_WEIGHT_BOLD;
	m_FontWeights[FONT_ENUM(FontWeight::BLACK)] = DWRITE_FONT_WEIGHT_BLACK;

	m_FontStyles[FONT_ENUM(FontStyle::NORMAL)] = DWRITE_FONT_STYLE_NORMAL;
	m_FontStyles[FONT_ENUM(FontStyle::OBLIQUE)] = DWRITE_FONT_STYLE_OBLIQUE;
	m_FontStyles[FONT_ENUM(FontStyle::ITALIC)] = DWRITE_FONT_STYLE_ITALIC;
}

McCol::TextRenderer::~TextRenderer()
{
	if (m_pDWriteTextLayout != nullptr) m_pDWriteTextLayout->Release();
}

void McCol::TextRenderer::Initialize()
{
	BaseRenderer::Initialize();
}


void McCol::TextRenderer::Render(D2DRender* renderer)
{
	if (IsTextChange)
	{
		CreateTextLayout(renderer);
	}

	renderer->GetContext()->SetTransform(m_pTransform->GetMatrix() * CameraSystem::GetInstance()->GetCameraMatrix());
	renderer->GetContext()->DrawTextLayout(D2D1::Point2F(-(m_LayoutWidth / 2) + m_Offset.x, -(m_LayoutHeight / 2) + m_Offset.y), m_pDWriteTextLayout, renderer->GetBrush(m_BrushColor));

	// 텍스트 레이아웃 rect 출력
	if (m_IsShowLayout)
	{
		const D2D1_RECT_F layoutRect = { -(m_LayoutWidth / 2), m_LayoutHeight / 2, m_LayoutWidth / 2, -(m_LayoutHeight / 2) };
		renderer->GetContext()->DrawRectangle(&layoutRect, m_Brush);
	}
}

void McCol::TextRenderer::SetSrcText(const std::wstring_view srcText)
{
	m_SrcText = srcText;
	m_EndRange = TEXT_LENGTH(m_SrcText);
	IsTextChange = true;
}

void McCol::TextRenderer::SetLayoutRect(const float& layoutWidth, const float& layoutHeight)
{
	m_LayoutWidth = layoutWidth;
	m_LayoutHeight = layoutHeight;
	IsTextChange = true;
}

void McCol::TextRenderer::SetBrushColor(D2D1::ColorF::Enum brushColor)
{
	m_BrushColor = brushColor;
}

void McCol::TextRenderer::ShowLayoutRect(const bool& isShowLayout)
{
	m_IsShowLayout = isShowLayout;
}

void McCol::TextRenderer::SetFontName(const std::wstring_view fontName)
{
	m_FontName = fontName;
}

void McCol::TextRenderer::SetFontWeight(FontWeight fontWeight)
{
	m_FontWeightIndex = FONT_ENUM(fontWeight);
}

void McCol::TextRenderer::SetFontStyle(FontStyle fontStyle)
{
	m_FontStyleIndex = FONT_ENUM(fontStyle);
}

void McCol::TextRenderer::SetFontSize(const float& fontSize)
{
	m_FontSize = fontSize;
}

void McCol::TextRenderer::SetFontRange(const UINT32& start, const UINT32& end)
{
	m_StartRange = start;
	m_EndRange = end;
}

void McCol::TextRenderer::SetTextAttribute(const std::wstring_view srcText, const float& fontSize,
	FontWeight fontWeight)
{
	m_SrcText = srcText;
	m_FontSize = fontSize;
	m_FontWeightIndex = FONT_ENUM(fontWeight);
	SetFontRange(0, TEXT_LENGTH(srcText));
}

void McCol::TextRenderer::CreateTextLayout(D2DRender* renderer)
{
	if (m_pDWriteTextLayout != nullptr)
		m_pDWriteTextLayout->Release();

	auto hr = renderer->GetDWriteFactory()->CreateTextLayout(
		m_SrcText.c_str(),
		TEXT_LENGTH(m_SrcText),
		renderer->GetDWriteTextFormat(),
		m_LayoutWidth,	// Layout Rect Width 설정
		m_LayoutHeight,	// Layout Rect Height 설정
		&m_pDWriteTextLayout);

	m_pDWriteTextLayout->SetFontFamilyName(m_FontName.c_str(), { m_StartRange, m_EndRange });		                // 폰트 이름(설치된 폰트 사용)
	m_pDWriteTextLayout->SetFontWeight(m_FontWeights[m_FontWeightIndex], { m_StartRange, m_EndRange });          // 폰트 두께(Bold, Light)
	m_pDWriteTextLayout->SetFontStyle(m_FontStyles[m_FontStyleIndex], { m_StartRange, m_EndRange });             // 폰트 스타일(기울기)
	m_pDWriteTextLayout->SetFontSize(m_FontSize, { m_StartRange, m_EndRange });			                        // 폰트 크기
	//m_pDWriteTextLayout->SetDrawingEffect(renderer->GetWhiteBrush(), { m_StartRange, m_EndRange });	            // 특정 구간 폰트 색상 설정

	IsTextChange = false;
}

