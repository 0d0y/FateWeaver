#include "TestSceneSH.h"

#include "../Engine/InputSystem.h"
#include "../Engine/SoundSystem.h"
#include "../RenderEngine/D2DTextureSystem.h"
#include "../Engine/TextureRenderer.h"

#include "../Engine/GameObject.h"
#include "../Engine/Transform.h"
#include "../Engine/Camera.h"
#include "../Engine/Macro.h"

#include "GameManager.h"

#include "Character.h"
#include "StateManager.h"

#include "PlayCard.h"
#include "Future.h"
#include "CardTexture.h"
#include "Mouse.h"

using namespace McCol;

TestSceneSH::TestSceneSH()
	: Scene(L"상학이의 테스트 씬")
{
}

TestSceneSH::~TestSceneSH()
{
}


void TestSceneSH::Enter()
{
	GameObject* camera = new GameObject(L"Camera");
	camera->AddComponent<Camera>();
	camera->AddComponent<Transform>();
	EventCreateOBJ(camera);

	
}

void TestSceneSH::Exit()
{
	Scene::Exit();
}

void TestSceneSH::Update(const float& deltaTime)
{
	Scene::Update(deltaTime);

	if (InputSystem::GetInstance()->IsKeyDown('1'))
	{
		EffectInfo info;
		info.Type = EffectType::Damaged;
		info.X = InputSystem::GetInstance()->GetMousePos().x;
		info.Y = InputSystem::GetInstance()->GetMousePos().y;
		EventSystem::GetInstance()->PublishEvent(L"EFFECT", info);
	}

	if (InputSystem::GetInstance()->IsKeyHold('2'))
	{
		EffectInfo info;
		info.Type = EffectType::SLASH_1;
		info.X = InputSystem::GetInstance()->GetMousePos().x;
		info.Y = InputSystem::GetInstance()->GetMousePos().y;
		EventSystem::GetInstance()->PublishEvent(L"EFFECT", info);
	}

	if (InputSystem::GetInstance()->IsKeyHold('3'))
	{
		EffectInfo info;
		info.Type = EffectType::GainLife_15;
		info.X = 0;
		info.Y = 0;
		EventSystem::GetInstance()->PublishEvent(L"EFFECT", info);
	}

	if (InputSystem::GetInstance()->IsKeyDown('4'))
	{

	}

	if (InputSystem::GetInstance()->IsKeyDown('5'))
	{
		SoundSystem::GetInstance()->Replay("Hit_Slash");
		
	}
	if (InputSystem::GetInstance()->IsKeyDown('6'))
	{
		
	}

	if (InputSystem::GetInstance()->IsKeyDown('7'))
	{
		SoundSystem::GetInstance()->Stop("BGM_02");
		SoundSystem::GetInstance()->PlaySoundM("BGM_01");
		//SoundSystem::GetInstance()->SetVolume("BGM", 0.1f);
	}
	if (InputSystem::GetInstance()->IsKeyDown('8'))
	{
		SoundSystem::GetInstance()->Stop("BGM_01");
		SoundSystem::GetInstance()->PlaySoundM("BGM_02");
	}
}
