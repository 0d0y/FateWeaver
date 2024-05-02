#include "EffectManager.h"


#include "../RenderEngine/D2DRender.h"
#include "../RenderEngine/D2DTextureSystem.h"

#include "../Engine/Scene.h"
#include "../Engine/GameObject.h"
#include "../Engine/Transform.h"
#include "../Engine/Animation.h"
#include "../Engine/TextRenderer.h"

#include "Effect.h"

#include "Elements.h"

using namespace McCol;

EffectManager::EffectManager()
{
	// 이펙트 출력 구조체 구성
	// 이펙트 이름, 이펙트가 나타날 위치, 표시용 수치, 이펙트 지속 시간(프레임)
}

void EffectManager::Initialize()
{
	EventSystem::GetInstance()->Subscribe(L"EFFECT", MakeListenerInfo(&EffectManager::RegisterEffect));
}

void EffectManager::Finalize()
{
}

void EffectManager::FixedUpdate(const float& deltaTime)
{
}

void EffectManager::LoadEffectBitmap()
{
}

void EffectManager::CreateEffectObject(const EffectInfo& info)
{
	Effect* effect = new Effect;

	effect->LoadEffect(info.Type);
	effect->SetPosition(info.X, info.Y);

	if(info.Value >= 0)
	{
		effect->SetValue(info.Value);
	}

	effect->OnFadeOut();

	Scene::EventCreateOBJ(effect);
}

void EffectManager::RegisterEffect(std::any info)
{
	auto effectInfo = std::any_cast<EffectInfo>(info);
	CreateEffectObject(effectInfo);
}
