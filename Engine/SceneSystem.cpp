#include "pch.h"
#include "SceneSystem.h"

#include "Component.h"
#include "GameObject.h"
#include "Scene.h"
#include "CollisionSystem.h"

McCol::SceneSystem::SceneSystem()
	: m_CurScene(nullptr)
	, m_ProgressTime(0.0f)
	, m_FixedTime(1.0f / 60.0f)
{
}

void McCol::SceneSystem::Initialize()
{
	EventSystem::GetInstance()->Subscribe(L"CREATE_OBJ", MakeListenerInfo(&SceneSystem::DelayedCreate));
	EventSystem::GetInstance()->Subscribe(L"DELETE_OBJ", MakeListenerInfo(&SceneSystem::DelayedDelete));
	EventSystem::GetInstance()->Subscribe(L"CHANGE_SCENE", MakeListenerInfo(&SceneSystem::DelayedChange));
}

void McCol::SceneSystem::Finalize()
{
	m_CurScene->Exit();

	for (auto& [name, scene] : m_Scenes)
	{
		SAFE_DELETE(scene)
	}

	m_Scenes.clear();
}

void McCol::SceneSystem::Update(const float& deltaTime)
{
	if (m_CurScene == nullptr)
		return;

	m_CurScene->Update(deltaTime);
}

void McCol::SceneSystem::LateUpdate(const float& deltaTime)
{
	if (m_CurScene != nullptr)
		m_CurScene->LateUpdate(deltaTime);

	DelayedProcess();
}

void McCol::SceneSystem::FixedUpdate(const float& deltaTime)
{
	if (m_CurScene == nullptr)
		return;

	m_ProgressTime += deltaTime;

	while (m_ProgressTime > m_FixedTime)
	{
		m_CurScene->FixedUpdate(deltaTime);
		m_ProgressTime -= m_FixedTime;
	}
}

void McCol::SceneSystem::Render(McCol::D2DRender* renderer)
{
	if (m_CurScene == nullptr)
		return;

	m_CurScene->Render(renderer);
}


void McCol::SceneSystem::AddScene(McCol::Scene* scene)
{
	m_Scenes.insert({ scene->GetName(), scene });
}

void McCol::SceneSystem::ChangeScene(std::wstring_view sceneName)
{
	if (m_Scenes.find(sceneName) == m_Scenes.end())
	{
		return;
	}

	if (m_CurScene != nullptr)
	{
		m_CurScene->Exit();
	}

	m_CurScene = m_Scenes[sceneName];

	m_CurScene->Enter();
}

void McCol::SceneSystem::DelayedCreate(std::any newGO)
{
	if (!newGO.has_value())
		return;

	if (m_CurScene == nullptr)
		return;

	m_Delayed.push({ newGO, SceneEvent::CREATE_EVENT });
}

void McCol::SceneSystem::DelayedDelete(std::any delGO)
{
	if (!delGO.has_value())
		return;

	if (m_CurScene == nullptr)
		return;

	const auto go = std::any_cast<GameObject*>(delGO);

	// 오브젝트 비활성화
	go->SetAble(false);

	m_Delayed.push({ delGO, SceneEvent::DELETE_EVENT });
}

void McCol::SceneSystem::DelayedChange(std::any sceneName)
{
	m_Delayed.push({ sceneName, SceneEvent::CHANGE_EVENT });
}

void McCol::SceneSystem::DelayedProcess()
{
	// 지연 처리 큐 비우기
	while (!m_Delayed.empty())
	{
		auto& [obj, event] = m_Delayed.front();

		if (!obj.has_value())
		{
			m_Delayed.pop();
			continue;
		}

		switch (event)
		{
		case SceneEvent::CREATE_EVENT:
		{
			const auto go = std::any_cast<GameObject*>(obj);
			auto& container = m_CurScene->GetContainer();

			auto layerIndex = static_cast<size_t>(go->GetLayer());

			if (layerIndex < container.size()) {
				// Component 초기화
				go->Initialize();

				// 속해있는 레이어에 생성
				container[static_cast<size_t>(go->GetLayer())].push_back(go);
			}
		}
		break;

		case SceneEvent::DELETE_EVENT:
		{
			auto go = std::any_cast<GameObject*>(obj);
			auto& container = m_CurScene->GetContainer();

			// 속해있는 레이어에서 제거

			auto layerIndex = static_cast<size_t>(go->GetLayer());

			if (layerIndex < container.size()) {
				container[layerIndex].remove(go);
				SAFE_DELETE(go)
			}
		}
		break;

		case SceneEvent::CHANGE_EVENT:
		{
			const auto sceneName = std::any_cast<std::wstring>(obj);

			ChangeScene(sceneName);
		}
		break;
		}

		m_Delayed.pop();
	}
}
