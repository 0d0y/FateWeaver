#pragma once
#include "EventHandler.h"

#include <map>

namespace McCol
{
	class GameObject;
	class D2DRender;
	class Scene;

	class SceneSystem : public EventHandler
	{
	private:
		enum class SceneEvent
		{
			CREATE_EVENT,
			DELETE_EVENT,
			CHANGE_EVENT,
		};

	public:
		SceneSystem();
		~SceneSystem() override = default;

	private:
		std::map<std::wstring_view, Scene*> m_Scenes;
		std::queue<std::pair<std::any, SceneEvent>> m_Delayed;
		Scene* m_CurScene;

		float m_ProgressTime;
		float m_FixedTime;

	public:
		void Initialize();
		void Finalize();

		void Update(const float& deltaTime);
		void LateUpdate(const float& deltaTime);
		void FixedUpdate(const float& deltaTime);
		void Render(D2DRender* renderer);

		void AddScene(Scene* scene);
		void ChangeScene(std::wstring_view sceneName);

	private: // 내부 함수 : 오브젝트 추가, 삭제, 씬 전환 이벤트 처리
		void DelayedCreate(std::any newGO);		// 지연 생성
		void DelayedDelete(std::any delGO);		// 지연 삭제
		void DelayedChange(std::any sceneName);	// 지연 씬 전환
		void DelayedProcess();					// 지연 이벤트 처리
	};
}

