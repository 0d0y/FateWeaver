#include "Effect.h"

#include <string>

#include "../Engine/Transform.h"
#include "../Engine/Animation.h"
#include "../Engine/TextureRenderer.h"
#include "../Engine/Scene.h"
#include "../Engine/RandomGenerator.h"

#include "../Engine/TextRenderer.h"

#include "Elements.h"

using namespace McCol;

Effect::Effect()
	: GameObject(L"Effect", McCol::Layer::EFFECT)
	, m_PlayTime(0)
	, m_ProgressTime(0)
{
	m_Transform = AddComponent<Transform>();
}

void Effect::Initialize()
{
	GameObject::Initialize();
}

void Effect::FixedUpdate(const float& deltaTime)
{
	GameObject::FixedUpdate(deltaTime);
	m_ProgressTime += deltaTime;

	if (m_ProgressTime > m_PlayTime)
	{
		Scene::EventDeleteOBJ(this);
	}
}

void Effect::Render(McCol::D2DRender* renderer)
{
	GameObject::Render(renderer);
}

void Effect::LoadEffect(EffectType type)
{
	if (type == EffectType::Damaged)
	{
		m_Animation = AddComponent<Animation>();
		AnimationState damagedEffect;
		damagedEffect.IsLoop = true;

		damagedEffect.Clips.emplace_back(382 * 0, 358 * 0, 382 * 1, 358 * 1, FRAME(1));
		damagedEffect.Clips.emplace_back(382 * 1, 358 * 0, 382 * 2, 358 * 1, FRAME(1));
		damagedEffect.Clips.emplace_back(382 * 2, 358 * 0, 382 * 3, 358 * 1, FRAME(1));
		damagedEffect.Clips.emplace_back(382 * 3, 358 * 0, 382 * 4, 358 * 1, FRAME(1));
		damagedEffect.Clips.emplace_back(382 * 4, 358 * 0, 382 * 5, 358 * 1, FRAME(1));

		damagedEffect.Clips.emplace_back(382 * 0, 358 * 1, 382 * 1, 358 * 2, FRAME(1));
		damagedEffect.Clips.emplace_back(382 * 1, 358 * 1, 382 * 2, 358 * 2, FRAME(1));
		damagedEffect.Clips.emplace_back(382 * 2, 358 * 1, 382 * 3, 358 * 2, FRAME(1));
		damagedEffect.Clips.emplace_back(382 * 3, 358 * 1, 382 * 4, 358 * 2, FRAME(1));
		damagedEffect.Clips.emplace_back(382 * 4, 358 * 1, 382 * 5, 358 * 2, FRAME(1));

		damagedEffect.Clips.emplace_back(382 * 0, 358 * 2, 382 * 1, 358 * 3, FRAME(1));
		damagedEffect.Clips.emplace_back(382 * 1, 358 * 2, 382 * 2, 358 * 3, FRAME(1));
		damagedEffect.Clips.emplace_back(382 * 2, 358 * 2, 382 * 3, 358 * 3, FRAME(1));
		damagedEffect.Clips.emplace_back(382 * 3, 358 * 2, 382 * 4, 358 * 3, FRAME(1));
		damagedEffect.Clips.emplace_back(382 * 4, 358 * 2, 382 * 5, 358 * 3, FRAME(1));

		damagedEffect.Clips.emplace_back(382 * 0, 358 * 3, 382 * 1, 358 * 4, FRAME(1));
		damagedEffect.Clips.emplace_back(382 * 1, 358 * 3, 382 * 2, 358 * 4, FRAME(1));
		damagedEffect.Clips.emplace_back(382 * 2, 358 * 3, 382 * 3, 358 * 4, FRAME(1));
		damagedEffect.Clips.emplace_back(382 * 3, 358 * 3, 382 * 4, 358 * 4, FRAME(1));
		damagedEffect.Clips.emplace_back(382 * 4, 358 * 3, 382 * 5, 358 * 4, FRAME(1));

		damagedEffect.Clips.emplace_back(382 * 0, 358 * 4, 382 * 1, 358 * 5, FRAME(1));
		damagedEffect.Clips.emplace_back(382 * 1, 358 * 4, 382 * 2, 358 * 5, FRAME(1));
		damagedEffect.Clips.emplace_back(382 * 2, 358 * 4, 382 * 3, 358 * 5, FRAME(1));
		damagedEffect.Clips.emplace_back(382 * 3, 358 * 4, 382 * 4, 358 * 5, FRAME(1));
		damagedEffect.Clips.emplace_back(382 * 4, 358 * 4, 382 * 5, 358 * 5, FRAME(1));

		m_Animation->AddAnimState(L"Damaged_Effect", damagedEffect);
		m_Animation->SetAnimState(L"Damaged_Effect");
		m_Animation->Load(L"../Resource/Effect/Effect_Damaged.png", L"Damaged");
		m_PlayTime = FRAME(1) * static_cast<float>(damagedEffect.Clips.size());

		const int rotation = RandomGenerator::GetInstance()->GetRandomNumber(0, 360);
		m_Transform->SetRotation(static_cast<float>(rotation));
	}
	else if (type == EffectType::SLASH_1)
	{
		m_TextureRenderer = AddComponent<TextureRenderer>();
		m_TextureRenderer->LoadTexture(L"../Resource/Effect/Effect_Slash_01.png", L"Slash_01");
		m_TextureRenderer->SetSmaller(true);
		m_PlayTime = 0.5f;

		const int rotation = RandomGenerator::GetInstance()->GetRandomNumber(-30, 30);
		m_Transform->SetRotation(static_cast<float>(rotation));
	}
	else if (type == EffectType::재빠름시작)
	{
		m_TextureRenderer = AddComponent<TextureRenderer>();
		m_TextureRenderer->LoadTexture(L"../Resource/icon/Effect_Agillity.png", L"QUICK_EFFECT");
		m_TextureRenderer->SetSmaller(true);

		auto quickStart = AddComponent<TextureRenderer>();
		quickStart->LoadTexture(L"../Resource/Effect/In_Agillity.png", L"QUICK_EFFECT_START");
		quickStart->SetSmaller(true);
		quickStart->SetOffset(0, -120);
		m_PlayTime = 0.5f;
	}
	else if (type == EffectType::재빠름종료)
	{

	}
	else if (type == EffectType::마력충전시작)
	{
		m_TextureRenderer = AddComponent<TextureRenderer>();
		m_TextureRenderer->LoadTexture(L"../Resource/icon/Effect_Charge.png", L"ENCHANTMENT_EFFECT");
		m_TextureRenderer->SetSmaller(true);


		auto enchantmentStart = AddComponent<TextureRenderer>();
		enchantmentStart->LoadTexture(L"../Resource/Effect/In_Charge.png", L"ENCHANTMENT_EFFECT_START");
		enchantmentStart->SetSmaller(true);
		enchantmentStart->SetOffset(0, -120);
		m_PlayTime = 0.5f;
	}
	else if (type == EffectType::마력충전종료)
	{

	}
	else if (type == EffectType::혼란시작)
	{
		m_TextureRenderer = AddComponent<TextureRenderer>();
		m_TextureRenderer->LoadTexture(L"../Resource/icon/Effect_Confuse.png", L"CONFUSION_EFFECT");
		m_TextureRenderer->SetSmaller(true);


		auto confusionStart = AddComponent<TextureRenderer>();
		confusionStart->LoadTexture(L"../Resource/Effect/In_Confuse.png", L"CONFUSION_EFFECT_START");
		confusionStart->SetSmaller(true);
		confusionStart->SetOffset(0, -120);
		m_PlayTime = 0.5f;
	}
	else if (type == EffectType::혼란종료)
	{

	}
	else if (type == EffectType::흐트러짐시작)
	{
		m_TextureRenderer = AddComponent<TextureRenderer>();
		m_TextureRenderer->LoadTexture(L"../Resource/icon/Effect_Falling.png", L"DISRUPTION_EFFECT");
		m_TextureRenderer->SetSmaller(true);


		auto disruptionStart = AddComponent<TextureRenderer>();
		disruptionStart->LoadTexture(L"../Resource/Effect/In_Falling.png", L"DISRUPTION_EFFECT_START");
		disruptionStart->SetSmaller(true);
		disruptionStart->SetOffset(0, -120);
		m_PlayTime = 0.5f;
	}
	else if (type == EffectType::흐트러짐종료)
	{
		m_TextureRenderer = AddComponent<TextureRenderer>();
		m_TextureRenderer->LoadTexture(L"../Resource/icon/Effect_Falling.png", L"DISRUPTION_EFFECT");
		m_TextureRenderer->SetSmaller(true);


		auto disruptionStart = AddComponent<TextureRenderer>();
		disruptionStart->LoadTexture(L"../Resource/Effect/In_Falling.png", L"DISRUPTION_EFFECT_START");
		disruptionStart->SetSmaller(true);
		disruptionStart->SetOffset(0, -120);
		m_PlayTime = 0.5f;
	}
	else if (type == EffectType::파멸의예언시작)
	{
		m_TextureRenderer = AddComponent<TextureRenderer>();
		m_TextureRenderer->LoadTexture(L"../Resource/icon/Effect_Prophecy.png", L"IMPENDING_RUIN_EFFECT");
		m_TextureRenderer->SetSmaller(true);


		auto disruptionStart = AddComponent<TextureRenderer>();
		disruptionStart->LoadTexture(L"../Resource/Effect/In_Predict.png", L"IMPENDING_RUIN_EFFECT_START");
		disruptionStart->SetSmaller(true);
		disruptionStart->SetOffset(0, -120);
		m_PlayTime = 0.5f;
	}
	else if (type == EffectType::파멸의의지시작)
	{
		m_TextureRenderer = AddComponent<TextureRenderer>();
		m_TextureRenderer->LoadTexture(L"../Resource/icon/Effect_Will.png", L"WILL_OF_RUIN_EFFECT");
		m_TextureRenderer->SetSmaller(true);


		//auto disruptionStart = AddComponent<TextureRenderer>();
		//disruptionStart->LoadTexture(L"../Resource/Effect/In_Predict.png", L"WILL_OF_RUIN_EFFECT_START");
		//disruptionStart->SetSmaller(true);
		//disruptionStart->SetOffset(0, -120);
		m_PlayTime = 0.5f;
	}
	else if (type == EffectType::엔진과부하시작)
	{
		m_TextureRenderer = AddComponent<TextureRenderer>();
		m_TextureRenderer->LoadTexture(L"../Resource/icon/Effect_Prophecy.png", L"IMPENDING_RUIN_EFFECT");
		m_TextureRenderer->SetSmaller(true);


		auto disruptionStart = AddComponent<TextureRenderer>();
		disruptionStart->LoadTexture(L"../Resource/Effect/In_Predict.png", L"IMPENDING_RUIN_EFFECT_START");
		disruptionStart->SetSmaller(true);
		disruptionStart->SetOffset(0, -120);
		m_PlayTime = 0.5f;
	}
	else if (type == EffectType::Effect_GetCard)
	{
		AnimationState getEffect;
		getEffect.IsLoop = true;

		getEffect.Clips.emplace_back(820 * 0, 0, 820 * 1, 549 * 1, FRAME(1));
		getEffect.Clips.emplace_back(820 * 1, 0, 820 * 2, 549 * 1, FRAME(1));
		getEffect.Clips.emplace_back(820 * 2, 0, 820 * 3, 549 * 1, FRAME(1));
		getEffect.Clips.emplace_back(820 * 3, 0, 820 * 4, 549 * 1, FRAME(1));

		m_Animation = AddComponent<Animation>();
		m_Animation->Load(L"../Resource/Effect/Effect_GetCard.png", L"Effect_GetCard");
		m_Animation->AddAnimState(L"Effect_GetCard", getEffect);
		m_Animation->SetAnimState(L"Effect_GetCard");
		m_PlayTime = FRAME(1) * static_cast<float>(getEffect.Clips.size());
	}
	else if (type == EffectType::Effect_DisCard)
	{
		AnimationState discardEffect;
		discardEffect.IsLoop = true;

		discardEffect.Clips.emplace_back(900 * 0, 0, 900 * 1, 569 * 1, FRAME(1));
		discardEffect.Clips.emplace_back(900 * 1, 0, 900 * 2, 569 * 1, FRAME(1));
		discardEffect.Clips.emplace_back(900 * 2, 0, 900 * 3, 569 * 1, FRAME(1));
		discardEffect.Clips.emplace_back(900 * 3, 0, 900 * 4, 569 * 1, FRAME(1));

		m_Animation = AddComponent<Animation>();
		m_Animation->Load(L"../Resource/Effect/Effect_DisCard.png", L"Effect_DisCard");
		m_Animation->AddAnimState(L"Effect_DisCard", discardEffect);
		m_Animation->SetAnimState(L"Effect_DisCard");
		m_PlayTime = FRAME(1) * static_cast<float>(discardEffect.Clips.size());
	}
	else if (type == EffectType::Effect_DrawCard)
	{
		AnimationState drawEffect;
		drawEffect.IsLoop = true;

		drawEffect.Clips.emplace_back(810 * 0, 0, 820 * 1, 549 * 1, FRAME(1));
		drawEffect.Clips.emplace_back(810 * 1, 0, 820 * 2, 549 * 1, FRAME(1));
		drawEffect.Clips.emplace_back(810 * 2, 0, 820 * 3, 549 * 1, FRAME(1));

		m_Animation = AddComponent<Animation>();
		m_Animation->Load(L"../Resource/Effect/Effect_DrawCard.png", L"Effect_DrawCard");
		m_Animation->AddAnimState(L"Effect_DrawCard", drawEffect);
		m_Animation->SetAnimState(L"Effect_DrawCard");
		m_PlayTime = FRAME(1) * static_cast<float>(drawEffect.Clips.size());
	}
	else if (type == EffectType::GainLife_15)
	{
		m_PlayTime = 0.5f;
		m_TextureRenderer = AddComponent<TextureRenderer>();
		m_TextureRenderer->LoadTexture(L"../Resource/Effect/Effect_Heal_Screen.png", L"Effect_Heal_Screen");
		m_TextureRenderer->SetFadeOut(m_PlayTime);

		auto gainLife15 = AddComponent<TextureRenderer>();
		gainLife15->LoadTexture(L"../Resource/Effect/GainLife_15.png", L"GainLife_15");
		gainLife15->SetSmaller(true);
	}
	else if (type == EffectType::GainLife_25)
	{
		m_PlayTime = 0.5f;
		m_TextureRenderer = AddComponent<TextureRenderer>();
		m_TextureRenderer->LoadTexture(L"../Resource/Effect/Effect_Heal_Screen.png", L"Effect_Heal_Screen");
		m_TextureRenderer->SetFadeOut(m_PlayTime);

		auto gainLife25 = AddComponent<TextureRenderer>();
		gainLife25->LoadTexture(L"../Resource/Effect/GainLife_25.png", L"GainLife_25");
		gainLife25->SetSmaller(true);
	}
	else if (type == EffectType::방어도아이콘)
	{
		m_PlayTime = 0.5f;
		m_TextureRenderer = AddComponent<TextureRenderer>();
		m_TextureRenderer->LoadTexture(L"../Resource/icon/Effect_Shield.png", L"Effect_Shield");
		m_TextureRenderer->SetFadeOut(m_PlayTime);
	}
	else if (type == EffectType::즉시발동)
	{
		m_PlayTime = 1.0f;
		m_TextureRenderer = AddComponent<TextureRenderer>();
		m_TextureRenderer->LoadTexture(L"../Resource/Effect/CardUse_RightNow.png", L"CardUse_RightNow");
		m_TextureRenderer->SetFadeOut(m_PlayTime);
	}
	else if (type == EffectType::행동카드제거)
	{
		m_PlayTime = 1.0f;
		m_TextureRenderer = AddComponent<TextureRenderer>();
		m_TextureRenderer->LoadTexture(L"../Resource/Effect/CardUse_Delayed.png", L"CardUse_Delayed");
		m_TextureRenderer->SetFadeOut(m_PlayTime);
	}
	else if (type == EffectType::차례시작)
	{
		m_PlayTime = 1.0f;
		m_TextureRenderer = AddComponent<TextureRenderer>();
		m_TextureRenderer->LoadTexture(L"../Resource/Effect/In_Turn_Start.png", L"In_Turn_Start");
		m_TextureRenderer->SetFadeOut(m_PlayTime);
	}
	else if (type == EffectType::대상없음)
	{
		m_PlayTime = 0.5f;
		m_TextureRenderer = AddComponent<TextureRenderer>();
		m_TextureRenderer->LoadTexture(L"../Resource/Effect/Effect_Iligal.png", L"Effect_Iligal");
		m_TextureRenderer->SetFadeOut(m_PlayTime);
	}
	else if (type == EffectType::에너지부족)
	{
		m_PlayTime = 0.5f;
		m_TextureRenderer = AddComponent<TextureRenderer>();
		m_TextureRenderer->LoadTexture(L"../Resource/Effect/Effect_NotEnough.png", L"Effect_NotEnough");
		m_TextureRenderer->SetFadeOut(m_PlayTime);
	}
	else if (type == EffectType::전투개시)
	{
		m_PlayTime = 1.5f;
		m_TextureRenderer = AddComponent<TextureRenderer>();
		m_TextureRenderer->LoadTexture(L"../Resource/Effect/In_Battle_Start.png", L"In_Battle_Start");
		m_TextureRenderer->SetFadeOut(m_PlayTime);
	}
	else if(type == EffectType::행동개시)
	{
		m_PlayTime = 1.5f;
		m_TextureRenderer = AddComponent<TextureRenderer>();
		m_TextureRenderer->LoadTexture(L"../Resource/Effect/in_Act_Start.png", L"in_Act_Start");
		m_TextureRenderer->SetFadeOut(m_PlayTime);
	}
	else if(type == EffectType::패배)
	{
		m_PlayTime = 3.0f;
		auto gainLife25 = AddComponent<TextureRenderer>();
		gainLife25->LoadTexture(L"../Resource/UI/death_popup_bg.png", L"death_popup_bg");
		gainLife25->SetSmaller(true);

		m_TextureRenderer = AddComponent<TextureRenderer>();
		m_TextureRenderer->LoadTexture(L"../Resource/UI/death_popup_text.png", L"death_popup_text");
		m_TextureRenderer->SetFadeIn(m_PlayTime);

	}
}

void Effect::SetPosition(float x, float y)
{
	if(x == 0 && y == 0)
	{
		m_Transform->SetPosition({ x, y });
		return;
	}

	const float alphaX = static_cast<float>(RandomGenerator::GetInstance()->GetRandomNumber(-30, 30));
	const float alphaY = static_cast<float>(RandomGenerator::GetInstance()->GetRandomNumber(-30, 30));
	m_Transform->SetPosition({ x + alphaX, y + alphaY });
}

void Effect::SetValue(int value)
{
	auto text = AddComponent<TextRenderer>();
	text->SetOffset(0, -100);
	text->SetBrushColor(D2D1::ColorF::Aqua);
	text->SetLayoutRect(100, 100);
	text->SetTextAttribute(std::to_wstring(value), 50, FontWeight::BOLD);
}

void Effect::OnFadeOut()
{
	if (m_TextureRenderer)
		m_TextureRenderer->SetFadeOut(m_PlayTime);
	if (m_Animation)
		m_Animation->SetFadeOut(m_PlayTime);
}
