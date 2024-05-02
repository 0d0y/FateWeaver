#pragma once
#include "Entity.h"
#include "EventHandler.h"

namespace McCol
{
	class GameObject;
	class D2DRender;

	class Scene : public Entity, public EventHandler
	{
	public:
		Scene(std::wstring_view sceneName);
		~Scene() override;

	protected:
		std::vector<std::list<GameObject*>> m_GameObjects;

	public:
		virtual void Enter() = 0;
		virtual void Exit() = 0;	// 상속 클래스에서 Scene::Exit() 호출시 m_GameObjects 내 오브젝트 제거 (구현 참조)

		virtual void Update(const float& deltaTime);
		virtual void FixedUpdate(const float& deltaTime);
		virtual void LateUpdate(const float& deltaTime);
		virtual void Render(D2DRender* renderer);

		std::vector<std::list<GameObject*>>& GetContainer();
		static void EventCreateOBJ(GameObject* go);	// 지연 생성 이벤트 호출 (SceneSystem::DelayedCreate 참조)
		static void EventDeleteOBJ(GameObject* go);	// 지연 삭제 이벤트 호출 (SceneSystem::DelayedDelete 참조)
	};
}


