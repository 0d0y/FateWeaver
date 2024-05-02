#include "pch.h"
#include "../RenderEngine/D2DRender.h"
#include "PrimitiveRenderer.h"
#include "Transform.h"
#include "CameraSystem.h"

McCol::PrimitiveRenderer::PrimitiveRenderer(GameObject* owner)
    : BaseRenderer(owner)
    , m_Rectangle({ 0.f, 0.f, 0.f, 0.f })
    , m_Center({ 0.f, 0.f })
    , m_Ellipse({ m_Center, 0.f, 0.f })
    , m_Start({ 0.f, 0.f })
    , m_End({ 0.f, 0.f })
    , m_BrushColor{ 0.f, 0.f, 0.f, 1.f }
    , m_Brush(nullptr)
    , m_PmScale(1.f)
    , m_IsRectangle(false)
    , m_IsEllipse(false)
{
    m_Name = stringToWstring(typeid(*this).name());
}

McCol::PrimitiveRenderer::~PrimitiveRenderer()
{
}

void McCol::PrimitiveRenderer::Initialize()
{
    BaseRenderer::Initialize();
}

void McCol::PrimitiveRenderer::Render(D2DRender* renderer)
{
    const auto& pmScale = D2D1::Matrix3x2F::Scale(m_PmScale, m_PmScale);

    renderer->GetContext()->SetTransform(pmScale * m_pTransform->GetMatrix() * CameraSystem::GetInstance()->GetCameraMatrix());

    HRESULT hr = renderer->GetContext()->CreateSolidColorBrush(m_BrushColor, &m_Brush);

    if (FAILED(hr))
    {
        return;
    }

    renderer->GetContext()->DrawRectangle(&m_Rectangle, m_Brush);
    renderer->GetContext()->DrawEllipse(&m_Ellipse, m_Brush);
    renderer->GetContext()->DrawLine(m_Start, m_End, m_Brush);
}

void McCol::PrimitiveRenderer::SetPmRectangle(const float& width, const float& height)
{
    m_Rectangle = { -(width / 2), -(height / 2), width / 2, height / 2 };
    m_IsRectangle = true;
}

void McCol::PrimitiveRenderer::SetPmRectangle(const D2D1_RECT_F& rect)
{
    m_Rectangle = rect;
}

void McCol::PrimitiveRenderer::SetPmEllipse(const float& centerX, const float& centerY, const float& radiusX, const float& radiusY)
{
    m_Center = { centerX, centerY };
    m_Ellipse = { m_Center, radiusX, radiusY };
    m_IsEllipse = true;
}

void McCol::PrimitiveRenderer::SetPmLine(const float& startX, const float& startY, const float& endX, const float& endY)
{
    m_Start = { startX, startY };
    m_End = { endX, endY };
}

void McCol::PrimitiveRenderer::SetPmBrushColor(D2D1::ColorF brushcolor)
{
    m_BrushColor = brushcolor;
}

void McCol::PrimitiveRenderer::SetPmScale(const float& pmScale)
{
    m_PmScale = pmScale;
}

D2D1_RECT_F McCol::PrimitiveRenderer::GetPmRectangle()
{
    if (m_IsRectangle)
    {
        return m_Rectangle;
    }
    return D2D1_RECT_F{ 0.f, 0.f, 0.f, 0.f };
}

D2D1_ELLIPSE McCol::PrimitiveRenderer::GetPmEllipse()
{
    if (m_IsEllipse)
    {
        return m_Ellipse;
    }
    return D2D1_ELLIPSE{ {0.f, 0.f}, 0.f, 0.f };
}

float McCol::PrimitiveRenderer::GetPmScale()
{
    return m_PmScale;
}


