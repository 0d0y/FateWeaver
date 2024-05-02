#include "../Engine/pch.h"
#include "CardTexture.h"

#include "Player.h"
#include "FateCard.h"
#include "PlayCard.h"
#include "Elements.h"
#include "AttributeParts.h"

#include "../Engine/Transform.h"
#include "../Engine/CameraSystem.h"
#include "../RenderEngine/D2DRender.h"
#include "../RenderEngine/D2DTextureSystem.h"
#include "../Engine/TextureRenderer.h"
#include "../Engine/TextRenderer.h"
#include "../Engine/OBB.h"

using namespace McCol;

enum class TextureInfo
{
	ILLUSTRATION = 0,
	CARD_FRAME = 1,
	FUTURE_FRAME = 2,
	RARITY = 3,
	COST = 4,
	END = 5,
};

enum class TextInfo
{
	CARD_NAME,
	CARD_COST,
	CARD_DESCRIPTION,
	END,
};

CardTexture::CardTexture(McCol::GameObject* owner)
	: BaseRenderer(owner)
	, m_IsHighlighted(false)
	, m_IsOnFuture(false)
	, m_IsCardRender(false)
{
	m_Name = stringToWstring(typeid(*this).name());

	m_CardTextures.resize(SIZE(TextureInfo::END));
	m_CardTexts.resize(SIZE(TextInfo::END));

	m_CardTextures[SIZE(TextureInfo::ILLUSTRATION)] = new TextureRenderer(owner);
	m_CardTextures[SIZE(TextureInfo::CARD_FRAME)] = new TextureRenderer(owner);
	m_CardTextures[SIZE(TextureInfo::FUTURE_FRAME)] = new TextureRenderer(owner);
	m_CardTextures[SIZE(TextureInfo::RARITY)] = new TextureRenderer(owner);
	m_CardTextures[SIZE(TextureInfo::COST)] = new TextureRenderer(owner);

	m_FrameEffectTextures = new TextureRenderer(owner);
	m_MiniFrameEffectTextures = new TextureRenderer(owner);

	m_CardTexts[SIZE(TextInfo::CARD_NAME)] = new TextRenderer(owner);
	m_CardTexts[SIZE(TextInfo::CARD_COST)] = new TextRenderer(owner);
	m_CardTexts[SIZE(TextInfo::CARD_DESCRIPTION)] = new TextRenderer(owner);

	m_CardTextures[SIZE(TextureInfo::RARITY)]->SetOffset(0, -130);
	m_CardTextures[SIZE(TextureInfo::ILLUSTRATION)]->SetOffset(0, -50);
	m_CardTextures[SIZE(TextureInfo::COST)]->SetOffset(-110, -155);

	m_CardTexts[SIZE(TextInfo::CARD_NAME)]->SetOffset(0, -136);
	m_CardTexts[SIZE(TextInfo::CARD_COST)]->SetOffset(-110, -157);
	m_CardTexts[SIZE(TextInfo::CARD_DESCRIPTION)]->SetOffset(0, 90);
}

CardTexture::~CardTexture()
{
	for (auto& texture : m_CardTextures)
	{
		delete texture;
		texture = nullptr;
	}

	m_CardTextures.clear();

	for (auto& textRenderer : m_CardTexts)
	{
		delete textRenderer;
		textRenderer = nullptr;
	}

	delete m_FrameEffectTextures;
	m_FrameEffectTextures = nullptr;

	delete m_MiniFrameEffectTextures;
	m_MiniFrameEffectTextures = nullptr;

	m_CardTexts.clear();
}

void CardTexture::Initialize()
{
	BaseRenderer::Initialize();

	for (auto texture : m_CardTextures)
	{
		texture->Initialize();
	}
	for (auto text : m_CardTexts)
	{
		text->Initialize();
		text->SetBrushColor(D2D1::ColorF::Black);
	}
	// 카드가 프레임 및 일러스트 관련 정보를 모두 갖고 있다고 가정
	m_FrameEffectTextures->Initialize();
	m_MiniFrameEffectTextures->Initialize();
	// 카드 레어도
	if (auto card = dynamic_cast<Card*>(m_Owner))
	{
		/*Text*/
		m_CardTexts[SIZE(TextInfo::CARD_NAME)]->SetTextAttribute(card->GetName(), 20.f, FontWeight::BOLD);
		m_CardTexts[SIZE(TextInfo::CARD_NAME)]->SetLayoutRect(185.f, 35.f);
		m_CardTexts[SIZE(TextInfo::CARD_DESCRIPTION)]->SetTextAttribute(card->MakeString(), 15.5f, FontWeight::BOLD);
		m_CardTexts[SIZE(TextInfo::CARD_DESCRIPTION)]->SetLayoutRect(195.f, 125.f);

		switch (card->GetRarity())
		{
		case Rarity::COMMON:
			m_CardTextures[SIZE(TextureInfo::RARITY)]->
				LoadTexture(L"../Resource/card_frame/CardFrame_Header_01.png", L"Common");
			break;
		case Rarity::UNCOMMON:
			m_CardTextures[SIZE(TextureInfo::RARITY)]->
				LoadTexture(L"../Resource/card_frame/CardFrame_Header_02.png", L"Uncommon");
			break;
		case Rarity::RARE:
			m_CardTextures[SIZE(TextureInfo::RARITY)]->
				LoadTexture(L"../Resource/card_frame/CardFrame_Header_03.png", L"Rare");
			break;
		case Rarity::DEFAULT:
			m_CardTextures[SIZE(TextureInfo::RARITY)]->
				LoadTexture(L"../Resource/card_frame/CardFrame_Header_01.png", L"Common");
			break;
		}
	}

	// 코스트 / 주도력 & 기본 카드 프레임
	if (auto fateCard = dynamic_cast<FateCard*>(m_Owner))
	{
		m_CardTextures[SIZE(TextureInfo::COST)]->
			LoadTexture(L"../Resource/card_frame/CardFrame_Fate_Cost.png", L"Fate Cost"); // 코스트(=주도력)

		m_CardTextures[SIZE(TextureInfo::CARD_FRAME)]->
			LoadTexture(L"../Resource/card_frame/CardFrame_Fate.png", L"Player Fate Frame"); // 운명 카드 프레임

		/*Text*/
		m_CardTexts[SIZE(TextInfo::CARD_COST)]->SetTextAttribute(fateCard->GetCostString(), 30.f, FontWeight::BOLD);
		m_CardTexts[SIZE(TextInfo::CARD_COST)]->SetLayoutRect(35.f, 35.f);
		m_CardTexts[SIZE(TextInfo::CARD_COST)]->SetOffset(-104, -174);
	}
	else if (auto playCard = dynamic_cast<PlayCard*>(m_Owner))
	{
		m_CardTextures[SIZE(TextureInfo::COST)]->
			LoadTexture(L"../Resource/card_frame/CardFrame_Play_Agil.png", L"Play Initiative"); // 주도력(=코스트)

		AttributeParts* attrparts = playCard->GetAttribute(Attribute::INITIATIVE);
		/*Text*/
		if (attrparts) 
		{
			m_CardTexts[SIZE(TextInfo::CARD_COST)]->SetTextAttribute(attrparts->GetValueString(), 30.f, FontWeight::BOLD);
			m_CardTexts[SIZE(TextInfo::CARD_COST)]->SetLayoutRect(35.f, 35.f);
		}

		// todo : CharacterType 으로 변경
		if (playCard->GetCardOwnerType() != CharacterType::PLAYER)
		{
			m_CardTextures[SIZE(TextureInfo::FUTURE_FRAME)]->
				LoadTexture(L"../Resource/card_frame/card_frame_mini_01.png", L"Player Future Frame");

			m_CardTextures[SIZE(TextureInfo::CARD_FRAME)]->
				LoadTexture(L"../Resource/card_frame/CardFrame_Play_01.png", L"Player Play Frame"); // 카드 프레임
		}
		else
		{
			m_CardTextures[SIZE(TextureInfo::FUTURE_FRAME)]->
				LoadTexture(L"../Resource/card_frame/card_frame_mini_02.png", L"Monster Future Frame");

			m_CardTextures[SIZE(TextureInfo::CARD_FRAME)]->
				LoadTexture(L"../Resource/card_frame/CardFrame_Play_02.png", L"Monster Play Frame"); // 카드 프레임
		}
	}
}

void CardTexture::FixedUpdate(const float& deltaTime)
{
	BaseRenderer::FixedUpdate(deltaTime);

	for (auto texture : m_CardTextures)
	{
		if (texture->GetBitmap())
			texture->FixedUpdate(deltaTime);
	}

	//if (m_IsOnFuture)
	//{
	//	m_Owner->GetComponent<OBB>()->SetColliScaleOffset({ 0.5f, 0.5f });
	//}
	//else
	//{
	//	m_Owner->GetComponent<OBB>()->SetColliScaleOffset({ 1.0f, 1.0f });
	//}
}

void CardTexture::Render(McCol::D2DRender* renderer)
{
	static auto hRatio = 1.85f;
	const auto& textureScale = D2D1::Matrix3x2F::Scale(m_TextureScale.x, m_TextureScale.y);
	renderer->GetContext()->SetTransform(textureScale * m_pTransform->GetMatrix() * McCol::CameraSystem::GetInstance()->GetCameraMatrix());


	//if (m_IsHighlighted)
	//{
	//	//if (m_IsOnFuture) todo : 다른데로 옮겨야함..
	//	//{
	//	//	auto size = m_CardTextures[SIZE(TextureInfo::FUTURE_FRAME)]->GetRenderSize();
	//	//	D2D1_RECT_F rect = D2D1::RectF(-size.width / hRatio, -size.height / hRatio, size.width / hRatio, size.height / hRatio);

	//	//	renderer->GetContext()->FillRoundedRectangle(
	//	//		D2D1::RoundedRect(rect, 10.0f, 10.0f),
	//	//		renderer->GetWhiteBrush()
	//	//	);
	//	//}
	//	if (m_IsCardRender)
	//	{
	//		auto size = m_CardTextures[SIZE(TextureInfo::CARD_FRAME)]->GetRenderSize();
	//		D2D1_RECT_F rect = D2D1::RectF(-size.width / hRatio, -size.height / hRatio, size.width / hRatio, size.height / hRatio);

	//		renderer->GetContext()->FillRoundedRectangle(
	//			D2D1::RoundedRect(rect, 10.0f, 10.0f),
	//			renderer->GetWhiteBrush()
	//		);
	//	}
	//}

	// 미래 영역 프레임 렌더링
	if (m_IsOnFuture)
	{
		if (m_IsHighlighted)
		{
			m_MiniFrameEffectTextures->SetTextureScale(2.f);
			m_MiniFrameEffectTextures->Render(renderer);
		}
		m_CardTextures[SIZE(TextureInfo::ILLUSTRATION)]->SetOffset(0, 0);
		//m_CardTextures[SIZE(TextureInfo::ILLUSTRATION)]->SetTextureScale(0.378f);
		m_CardTextures[SIZE(TextureInfo::ILLUSTRATION)]->Render(renderer);
		m_CardTextures[SIZE(TextureInfo::FUTURE_FRAME)]->SetTextureScale(2.f);
		m_CardTextures[SIZE(TextureInfo::FUTURE_FRAME)]->Render(renderer);

	}

	// 기본 프레임 렌더링
	if (m_IsCardRender)
	{
		if (m_IsHighlighted)
		{
			m_FrameEffectTextures->Render(renderer);
		}
		m_CardTextures[SIZE(TextureInfo::ILLUSTRATION)]->SetOffset(0, -50);
		m_CardTextures[SIZE(TextureInfo::ILLUSTRATION)]->Render(renderer);
		m_CardTextures[SIZE(TextureInfo::CARD_FRAME)]->Render(renderer);
		m_CardTextures[SIZE(TextureInfo::RARITY)]->Render(renderer);
		m_CardTextures[SIZE(TextureInfo::COST)]->Render(renderer);


		for (auto& text : m_CardTexts)
		{
			text->Render(renderer);
		}
	}
}

void CardTexture::CardRender(McCol::D2DRender* renderer)
{
	const auto& textureScale = D2D1::Matrix3x2F::Scale(m_TextureScale.x, m_TextureScale.y);

	renderer->GetContext()->SetTransform(textureScale * m_pTransform->GetMatrix() * McCol::CameraSystem::GetInstance()->GetCameraMatrix());

	const D2D1_RECT_F dstRect = {
		(m_Offset.x - ((m_SrcRect.right - m_SrcRect.left) / 2)),
		(m_Offset.y - ((m_SrcRect.bottom - m_SrcRect.top) / 2)),
		(m_Offset.x + ((m_SrcRect.right - m_SrcRect.left) / 2)),
		(m_Offset.y + ((m_SrcRect.bottom - m_SrcRect.top) / 2)) };
}

void CardTexture::FutureRender(McCol::D2DRender* renderer)
{
	const D2D1_RECT_F dstRect = {
	(m_Offset.x - ((m_SrcRect.right - m_SrcRect.left) / 2)),
	(m_Offset.y - ((m_SrcRect.bottom - m_SrcRect.top) / 2)),
	(m_Offset.x + ((m_SrcRect.right - m_SrcRect.left) / 2)),
	(m_Offset.y + ((m_SrcRect.bottom - m_SrcRect.top) / 2)) };
}

//void CardTexture::SetIllustration(std::wstring_view filePath, std::wstring_view key)
//{
//	m_CardTextures[SIZE(TextureInfo::ILLUSTRATION)]->LoadTexture(filePath, key);
//}

void CardTexture::SetIllustration(std::wstring_view key)
{
	m_CardTextures[SIZE(TextureInfo::ILLUSTRATION)]->GetTexture(key);
}

ID2D1Bitmap* CardTexture::GetIllustration()
{
	return m_CardTextures[SIZE(TextureInfo::ILLUSTRATION)]->GetBitmap();
}

ID2D1Bitmap* CardTexture::GetFrame()
{
	return m_CardTextures[SIZE(TextureInfo::CARD_FRAME)]->GetBitmap();
}

void CardTexture::SetIsFutureRender(bool isFutureRender)
{
	m_IsOnFuture = isFutureRender;
}

void CardTexture::SetIsCardRender(bool isCardRender)
{
	m_IsCardRender = isCardRender;
}

void CardTexture::SetTextureScale(const float& scale)
{
	m_TextureScale = { scale, scale };

	for (auto& texture : m_CardTextures)
	{
		texture->SetTextureScale(scale);
	}
}

D2D1_SIZE_F CardTexture::GetRenderSize()
{
	if (m_IsOnFuture)
	{
		return m_CardTextures[SIZE(TextureInfo::FUTURE_FRAME)]->GetRenderSize();
	}
	if (m_IsCardRender)
	{
		return m_CardTextures[SIZE(TextureInfo::CARD_FRAME)]->GetRenderSize();
	}
}



void CardTexture::RenewalString()
{
	auto card = dynamic_cast<Card*>(m_Owner);
	if (card)
	{
		std::wstring description = card->MakeString();
		if (description != L"")
		{
			m_CardTexts[SIZE(TextInfo::CARD_DESCRIPTION)]->SetTextAttribute(description, 16.f, FontWeight::BOLD);
		}
		AttributeParts* attr = card->GetAttribute(Attribute::INITIATIVE);
		if (attr)
		{
			m_CardTexts[SIZE(TextInfo::CARD_COST)]->SetTextAttribute(attr->GetValueString(), 30.f, FontWeight::BOLD);
		}
	}
}

void CardTexture::IsFremeEffect(bool isFrameEffectRender, FrameEffectInfo effectInfo)
{
	m_IsHighlighted = isFrameEffectRender;

	switch (effectInfo)
	{
	case FrameEffectInfo::FRAME_GREEN:
		m_FrameEffectTextures->LoadTexture(L"../Resource/effect_card frame_green.png", L"Frame_Effect_Green");
		m_MiniFrameEffectTextures->LoadTexture(L"../Resource/effect_card frame_green_mini.png", L"Frame_Effect_Green_Mini");
		break;
	case FrameEffectInfo::FRAME_YELLOW:
		m_FrameEffectTextures->LoadTexture(L"../Resource/effect_card frame_yellow.png", L"Frame_Effect_Yellow");
		m_MiniFrameEffectTextures->LoadTexture(L"../Resource/effect_card frame_yellow_mini.png", L"Frame_Effect_Yellow_Mini");
		break;
	case FrameEffectInfo::FRAME_RED:
		m_FrameEffectTextures->LoadTexture(L"../Resource/effect_card frame_red.png", L"Frame_Effect_RED");
		m_MiniFrameEffectTextures->LoadTexture(L"../Resource/effect_card frame_red_mini.png", L"Frame_Effect_RED_Mini");
		break;
	default:
		break;
	}
}

