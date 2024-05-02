#include "pch.h"
#include "Animation.h"
#include "Transform.h"
#include "CameraSystem.h"
#include "../RenderEngine/D2DRender.h"
#include "../RenderEngine/D2DTextureSystem.h"

McCol::Animation::Animation(GameObject* owner)
	: BaseRenderer(owner)
	, m_CurState(nullptr)
	, m_d2dBitmap(nullptr)
	, m_ClipIndex(0)
	, m_PlaySpeed(1)
	, m_IsFlipX(false)
	, m_AnimScale(1.0f)
{
	m_Name = stringToWstring(typeid(*this).name());
}

McCol::Animation::~Animation()
{
}

void McCol::Animation::Initialize()
{
	BaseRenderer::Initialize();
}

void McCol::Animation::FixedUpdate(const float& deltaTime)
{
	BaseRenderer::FixedUpdate(deltaTime);

	const float durationTest = m_CurState->Clips[m_ClipIndex].m_Length / m_PlaySpeed;

	if (m_ProgressTime > durationTest)
	{
		m_ProgressTime -= durationTest;
		if (m_ClipIndex == m_CurState->Clips.size() - 1)
		{
			if (m_CurState->IsLoop)
			{
				m_ClipIndex = 0;
			}
		}
		else
		{
			m_ClipIndex++;
		}
	}
}

void McCol::Animation::Render(D2DRender* renderer)
{
	const auto& mirror = m_IsFlipX ? D2D1::Matrix3x2F::Scale(-1.0f, 1.0f) : D2D1::Matrix3x2F::Scale(1.0f, 1.0f);
	const auto& animScale = D2D1::Matrix3x2F::Scale(m_AnimScale, m_AnimScale);
	renderer->GetContext()->SetTransform(mirror * animScale * m_pTransform->GetMatrix() * CameraSystem::GetInstance()->GetCameraMatrix());

	const D2D1_RECT_F srcRect = {
		m_CurState->Clips[m_ClipIndex].m_LT.x,
		m_CurState->Clips[m_ClipIndex].m_LT.y,
		m_CurState->Clips[m_ClipIndex].m_RB.x,
		m_CurState->Clips[m_ClipIndex].m_RB.y
	};

	const D2D1_RECT_F dstRect = {
		(BaseRenderer::GetOffset().x - ((srcRect.right - srcRect.left) / 2)),
		(BaseRenderer::GetOffset().y - ((srcRect.bottom - srcRect.top) / 2)),
		(BaseRenderer::GetOffset().x + ((srcRect.right - srcRect.left) / 2)),
		(BaseRenderer::GetOffset().y + ((srcRect.bottom - srcRect.top) / 2)) };

	renderer->GetContext()->DrawBitmap(m_d2dBitmap, dstRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, srcRect);
}

int McCol::Animation::GetSpeed()
{
	return 0;
}

void McCol::Animation::SetSpeed(const float& speed)
{
	m_PlaySpeed = speed;
}

void McCol::Animation::SetFlip(bool flipX)
{
	m_IsFlipX = flipX;
}

//void McCol::Animation::SetFrameInfo(ID2D1Bitmap1* bitmap, const float& frameWidth, const float& frameHeight)
//{
//    int row = bitmap->GetSize().width / frameWidth;
//    int col = bitmap->GetSize().height / frameHeight;
//
//    for (int j = 0; j < col; j++)
//    {
//        std::pair<int, int> frameInfo;
//        frameInfo.first = j * frameHeight;
//        for (int i = 0; i < row; i++)
//        {
//            frameInfo.second = i * frameWidth;
//            m_FrameInfo.push_back(frameInfo);
//        }
//    }
//}

void McCol::Animation::Load(const std::wstring& strFilePath, std::wstring_view bitmapKey)
{
	m_d2dBitmap = D2DTextureSystem::GetInstance()->LoadTexture(strFilePath, bitmapKey);
}

void McCol::Animation::SetAnimState(std::wstring_view stateKey)
{
	m_CurState = &m_States[stateKey];
}

void McCol::Animation::AddAnimState(std::wstring_view stateKey, const AnimationState& state)
{
	m_States.emplace(stateKey, state);
}

void McCol::Animation::SetAnimScale(const float& scale)
{
	m_AnimScale = scale;
}



/*  화이팅~! 간바레~! 힘내~! */