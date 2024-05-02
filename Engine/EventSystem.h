#pragma once

#include <functional>
#include <queue>
#include <map>
#include <string_view>
#include <any>

namespace McCol
{
	class EventHandler;

	struct Event
	{
		std::wstring_view EventID;						// 이벤트명
		std::any Parameter;								// 이벤트 생성 객체(필요시 적절한 캐스팅으로 사용)
		float DelayedTime;

		Event(std::wstring_view id, std::any param, const float& delayed)
			: EventID(id), Parameter(param), DelayedTime(delayed) {}
	};

	struct ListenerInfo
	{
		const EventHandler* Listener = nullptr;				// 이벤트를 받을 객체(dangling 포인터를 방지하기 위한 객체 검사용, 실제 사용 X)
		std::function<void(std::any)> EventFunction;		// 이벤트를 받을 시 수행할 함수

		ListenerInfo(const EventHandler* listener, const std::function<void(std::any)>& func)
			: Listener(listener), EventFunction(func) {}
	};

	class EventSystem
	{
	private:
		EventSystem();
		~EventSystem() = default;

	private:
		static EventSystem* m_Instance;
		std::vector<Event> m_CustomEvents;						// 사용자 정의 이벤트
		std::multimap<std::wstring_view, ListenerInfo> m_Listeners;		// 이벤트 구독자 정보 컨테이너

	public:
		static EventSystem* GetInstance()
		{
			if (m_Instance == nullptr)
				m_Instance = new EventSystem;

			return m_Instance;
		}

		void Initialize();
		void Update(const float& deltaTime);
		void Finalize();

	public:
		// 이벤트 발행
		void PublishEvent(std::wstring_view evtID, const std::any& param = nullptr, const float& delayed = 0.0f);
		void Subscribe(std::wstring_view evtID, const ListenerInfo& listenerInfo);			// 이벤트 구독

		void Unsubscribe(std::wstring_view evtID, const EventHandler* listener);			// 해당 이벤트 구독 해지
		void RemoveListener(const EventHandler* listener);									// 해당 리스너가 구독한 모든 구독 취소
		void RemoveListenersAtEvent(std::wstring_view evtID);								// 해당 이벤트 모든 구독자 제거
		void RemoveAllEvents();																// 모든 이벤트 제거
		void RemoveAllSubscribes();															// 모든 구독 취소

	private: // 내부 함수
		void ProcessEvent(const float& deltaTime);																// 이벤트 큐 확인
		void DispatchEvent(const Event& evt);												// 이벤트 처리
		bool CheckSubscribe(std::wstring_view evtID, const EventHandler* listener);			// 이벤트 중복 구독 확인
	};
}


