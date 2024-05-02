#include "pch.h"
#include "AnimationRenderer.h"
#include "Transform.h"
#include "CameraSystem.h"
#include "../RenderEngine/D2DRender.h"

McCol::AnimationRenderer::AnimationRenderer(GameObject* owner)
    : BaseRenderer(owner)
    , m_CurAnimState(nullptr)
    , m_d2dBitmap(nullptr)
    , m_ClipIndex(0)
    , m_PlaySpeed(1)
    , m_ProgressTime(0)
    , IsFlipX(false)
{
    m_Name = typeid(*this).name();
}

McCol::AnimationRenderer::~AnimationRenderer()
{
}

void McCol::AnimationRenderer::Initialize()
{
    if (GetOwner() == nullptr)
        return;

    m_pTransform = m_Owner->GetComponent<Transform>();
}

void McCol::AnimationRenderer::FixedUpdate(const float& deltaTime)
{
    const float durationTest = m_CurAnimState->Clips[m_ClipIndex].m_Length / m_PlaySpeed;

    if (m_ProgressTime > durationTest)
    {
        m_ProgressTime -= durationTest;
        if (m_ClipIndex == m_CurAnimState->Clips.size() - 1)
        {
            if (m_CurAnimState->IsLoop)
            {
                m_ClipIndex = 0;
            }
        }
        else
        {
            m_ClipIndex++;
        }
    }

    m_ProgressTime += deltaTime;
}

void McCol::AnimationRenderer::Render(D2DRender* renderer)
{
    renderer->GetContext()->SetTransform(m_pTransform->GetMatrix() * CameraSystem::GetInstance()->GetCameraMatrix());

    

    const D2D1_RECT_F srcRect = {
        m_CurAnimState->Clips[m_ClipIndex].m_LT.x,
        m_CurAnimState->Clips[m_ClipIndex].m_LT.y,
        m_CurAnimState->Clips[m_ClipIndex].m_RB.x,
        m_CurAnimState->Clips[m_ClipIndex].m_RB.y
         };

    const D2D1_RECT_F dstRect = {
        (BaseRenderer::GetOffset().x - ((srcRect.right - srcRect.left) / 2)),
        (BaseRenderer::GetOffset().y - ((srcRect.bottom - srcRect.top) / 2)),
        (BaseRenderer::GetOffset().x + ((srcRect.right - srcRect.left) / 2)),
        (BaseRenderer::GetOffset().y + ((srcRect.bottom - srcRect.top) / 2)) };

    renderer->GetContext()->DrawBitmap(m_d2dBitmap, dstRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, srcRect);
}

void McCol::AnimationRenderer::Play(const std::string& name)
{
}

void McCol::AnimationRenderer::Stop()
{
}

int McCol::AnimationRenderer::GetSpeed()
{
    return 0;
}

void McCol::AnimationRenderer::SetSpeed(const float& speed)
{
    m_PlaySpeed = speed;
}

void McCol::AnimationRenderer::SetFlip()
{
}

void McCol::AnimationRenderer::SetFrameInfo(ID2D1Bitmap1* bitmap, const float& frameWidth, const float& frameHeight)
{
    int row = bitmap->GetSize().width / frameWidth;
    int col = bitmap->GetSize().height / frameHeight;

    for (int j = 0; j < col; j++)
    {
        std::pair<int, int> frameInfo;
        frameInfo.first = j * frameHeight;
        for (int i = 0; i < row; i++)
        {
            frameInfo.second = i * frameWidth;
            m_FrameInfo.push_back(frameInfo);
        }
    }
}

ID2D1Bitmap* McCol::AnimationRenderer::GetBitmap()
{
    return m_d2dBitmap;
}

void McCol::AnimationRenderer::SetBitmap(ID2D1Bitmap* bitmap)
{
    m_d2dBitmap = bitmap;
}

void McCol::AnimationRenderer::SetAnimState(AnimationState* animstate)
{
    m_CurAnimState = animstate;
}
