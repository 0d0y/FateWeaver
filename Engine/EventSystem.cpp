#include "pch.h"
#include "EventSystem.h"



McCol::EventSystem* McCol::EventSystem::m_Instance = nullptr;

McCol::EventSystem::EventSystem()
{
}

void McCol::EventSystem::Initialize()
{
}

void McCol::EventSystem::Update(const float& deltaTime)
{
	ProcessEvent(deltaTime);
}

void McCol::EventSystem::Finalize()
{
	RemoveAllEvents();
	RemoveAllSubscribes();

	SAFE_DELETE(m_Instance)
}

void McCol::EventSystem::PublishEvent(std::wstring_view evtID, const std::any& param, const float& delayed)
{
	m_CustomEvents.push_back({evtID, param, delayed});
}

void McCol::EventSystem::Subscribe(std::wstring_view evtID, const ListenerInfo& listenerInfo)
{
	// 유효성 및 중복 검사
	if(listenerInfo.Listener == nullptr || CheckSubscribe(evtID, listenerInfo.Listener))
	{
		return;
	}

	m_Listeners.emplace(evtID, listenerInfo);
}

void McCol::EventSystem::Unsubscribe(std::wstring_view evtID, const EventHandler* listener)
{
	auto [first, last] = m_Listeners.equal_range(evtID);

	for(auto& it = first; it != last;)
	{
		if(it->second.Listener == listener)
		{
			it = m_Listeners.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void McCol::EventSystem::RemoveListener(const EventHandler* listener)
{
	// info : EventHandler 를 상속받은 객체가 소멸될 경우 자동으로 호출되는 함수
	// info : listener 의 구독목록을 받아온다면 성능상 개선의 여지가 있음, 현재는 O(N)
	for(auto it = m_Listeners.begin(); it != m_Listeners.end();)
	{
		if(it->second.Listener == listener)
		{
			it = m_Listeners.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void McCol::EventSystem::RemoveListenersAtEvent(std::wstring_view evtID)
{
	auto [first, last] = m_Listeners.equal_range(evtID);

	for (auto& it = first; it != last;)
	{
		it = m_Listeners.erase(it);
	}
}

void McCol::EventSystem::RemoveAllEvents()
{
	while(!m_CustomEvents.empty())
	{
		m_CustomEvents.clear();
	}
}

void McCol::EventSystem::RemoveAllSubscribes()
{
	m_Listeners.clear();
}

void McCol::EventSystem::ProcessEvent(const float& deltaTime)
{
	std::vector<McCol::Event> tempEvents = m_CustomEvents;
	m_CustomEvents.clear();

	for (auto& evt : tempEvents)
	{
		evt.DelayedTime -= deltaTime;

		if (evt.DelayedTime <= 0)
		{
			DispatchEvent(evt);
		}
		else
		{
			m_CustomEvents.push_back(evt);
		}
	}
}

void McCol::EventSystem::DispatchEvent(const McCol::Event& evt)
{
	auto [first, last] = m_Listeners.equal_range(evt.EventID);

	for (auto& it = first; it != last; ++it)
	{
		// 이벤트 함수 호출
		// EventFunction : 해당 이벤트를 구독한 Listener 가 실행할 함수
		// evt.Publisher : 해당 이벤트에 대해 EventSystem::Publish 한 객체
		it->second.EventFunction(evt.Parameter);
	}
}

bool McCol::EventSystem::CheckSubscribe(std::wstring_view evtID, const EventHandler* listener)
{
	auto [first, last] = m_Listeners.equal_range(evtID);

	for (auto& it = first; it != last; ++it)
	{
		if (it->second.Listener == listener)
		{
			return true;
		}
	}

	return false;
}
