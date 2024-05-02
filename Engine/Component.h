#pragma once
#include "GameObject.h"
#include <typeinfo>

namespace McCol
{
	class Component : public Entity
	{
	public:
		Component(GameObject* owner) : m_Owner(owner), m_IsOn(true) {}
		~Component() override = default;

	protected:
		GameObject* m_Owner; // 종속된 게임 오브젝트
		bool m_IsOn;		 // 토글 기능(필요시 각자 사용)

	public:
		virtual void Initialize() = 0;

	public:
		void SetOwner(GameObject* go);
		GameObject* GetOwner() const;

		void SetIsOn(bool isOn);
		bool GetInOn() const;

		template <typename T>
		T* AddComponent();

		template <typename T>
		T* GetComponent() const;

		template <typename T>
		T* GetComponentInParent() const;
	};

	inline void Component::SetOwner(GameObject* go)
	{
		m_Owner = go;
	}

	inline GameObject* Component::GetOwner() const
	{
		return m_Owner;
	}

	inline void Component::SetIsOn(bool isOn)
	{
		m_IsOn = isOn;
	}

	inline bool Component::GetInOn() const
	{
		return m_IsOn;
	}

	template <typename T>
	T* Component::AddComponent()
	{
		return m_Owner->AddComponent<T>();
	}

	template <typename T>
	T* Component::GetComponent() const
	{
		return m_Owner->GetComponent<T>();
	}

	template <typename T>
	T* Component::GetComponentInParent() const
	{
		return m_Owner->GetComponentInParent<T>();
	}
}

