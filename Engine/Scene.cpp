#include "pch.h"
#include "Scene.h"

#include "GameObject.h"

McCol::Scene::Scene(std::wstring_view sceneName)
	: Entity(sceneName)
{
	m_GameObjects.resize(static_cast<size_t>(Layer::END));
}

McCol::Scene::~Scene()
{
}

void McCol::Scene::Exit()
{
	for (auto& layer : m_GameObjects)
	{
		for (auto& go : layer)
		{
			SAFE_DELETE(go)
		}
		layer.clear();
	}
}

void McCol::Scene::Update(const float& deltaTime)
{
	for(const auto& layer : m_GameObjects)
	{
		for(const auto go : layer)
		{
			go->Update(deltaTime);
		}
	}
}

void McCol::Scene::FixedUpdate(const float& deltaTime)
{
	for (const auto& layer : m_GameObjects)
	{
		for (const auto go : layer)
		{
			go->FixedUpdate(deltaTime);
		}
	}
}

void McCol::Scene::LateUpdate(const float& deltaTime)
{
	// todo : 구현 예정
}

void McCol::Scene::Render(D2DRender* renderer)
{
	for (const auto& layer : m_GameObjects)
	{
		for (const auto go : layer)
		{
			go->Render(renderer);
		}
	}
}

std::vector<std::list<McCol::GameObject*>>& McCol::Scene::GetContainer()
{
	return m_GameObjects;
}

void McCol::Scene::EventCreateOBJ(GameObject* go)
{
	EventSystem::GetInstance()->PublishEvent(L"CREATE_OBJ", go);
}

void McCol::Scene::EventDeleteOBJ(GameObject* go)
{
	EventSystem::GetInstance()->PublishEvent(L"DELETE_OBJ", go);
}
