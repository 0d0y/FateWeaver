#pragma once
#include "Entity.h"
#include <vector>

#include "IFixedUpdatable.h"
#include "IRenderable.h"
#include "IUpdatable.h"
#include "ICollidable.h"

#include <vector>

namespace McCol
{
	enum class Layer {
		DEFAULT,
		BACKGROUND,
		CHARACTER,
		CARD,
		DIM,
		DECK,
		UI,
		EFFECT,
		MOUSE,
		POPUP,
		END,
	};

	class D2DRender;
	class Component;
	class D2DRender;
	class Camera;
	class Collider;

	class GameObject : public Entity, public IUpdatable, public IFixedUpdatable, public IRenderable, public ICollidable
	{
	public:
		GameObject(std::wstring_view name, Layer layer);
		GameObject(std::wstring_view name);
		~GameObject() override;

	protected:
		GameObject* m_Parent;
		std::vector<GameObject*> m_Children;

		// 전체 컴포넌트 컨테이너
		std::vector<Component*> m_Components;

		// 실행 주기별 컴포넌트 컨테이너
		std::vector<IUpdatable*> m_Updatables;
		std::vector<IFixedUpdatable*> m_FixedUpdatables;
		std::vector<IRenderable*> m_Renderables;

	protected:
		Layer m_Layer;
		bool m_IsAble; // 활성화 / 비활성화

	public: // 실행 주기 함수
		virtual void Initialize();
		void Update(const float& deltaTime) override;
		void FixedUpdate(const float& deltaTime) override;
		void Render(D2DRender* renderer) override;
		void HandleCollisionStay(Collider* otherCollider) override;
		void HandleCollisionEnter(Collider* otherCollider) override;
		void HandleCollisionExit(Collider* otherCollider) override;

	public:
		GameObject* GetParent() const;
		void AddChild(GameObject* child);
		void SetParent(GameObject* parent);
		bool IsAble();
		void SetAble(bool able);
		void SetLayer(Layer layer);
		Layer GetLayer();

	public:
		template <typename T>
		T* AddComponent();

		template <typename T>
		T* GetComponent();

		template <typename T>
		std::vector<T*> GetComponents();

		template <typename T>
		T* GetComponentInParent();

		std::vector<Component*>& GetContainer();

	};
}

template<typename T>
T* McCol::GameObject::AddComponent()
{
	// 널 포인터 또는 컴포넌트 클래스를 상속받지 않았는지 확인함
	if (!std::is_base_of_v<Component, T>)
	{
		return nullptr;
	}

	// 생성 및 주인 설정
	T* component = new T(this);

	// 전체 컴포넌트 컨테이너 등록
	m_Components.push_back(component);

	// 실행 주기별 컴포넌트 컨테이너 등록
	if (IUpdatable* ua = dynamic_cast<IUpdatable*>(component))
		m_Updatables.push_back(ua);
	if (IFixedUpdatable* fua = dynamic_cast<IFixedUpdatable*>(component))
		m_FixedUpdatables.push_back(fua);
	if (IRenderable* ra = dynamic_cast<IRenderable*>(component))
		m_Renderables.push_back(ra);

	return component;
}

template<typename T>
T* McCol::GameObject::GetComponent()
{
	// 컴포넌트 클래스를 상속받지 않았는지 확인함
	if (!std::is_base_of_v<Component, T>)
	{
		return nullptr;
	}

	// 게임 오브젝트에 존재하는 컴포넌트인지 확인함
	for (Component* existingComponent : m_Components)
	{
		if (dynamic_cast<T*>(existingComponent) != nullptr)
		{
			// 존재하는 첫번째 동일한 컴포넌트 반환
			return static_cast<T*>(existingComponent);
		}
	}

	return nullptr;
}

template <typename T>
std::vector<T*> McCol::GameObject::GetComponents()
{
	std::vector<T*> findComponents;

	// 게임 오브젝트에 존재하는 컴포넌트인지 확인함
	for (Component* existingComponent : m_Components)
	{
		if (dynamic_cast<T*>(existingComponent) != nullptr)
		{
			// 존재하는 모든 동일한 컴포넌트 반환
			findComponents.push_back(static_cast<T*>(existingComponent));
		}
	}

	return findComponents;
}

template<typename T>
T* McCol::GameObject::GetComponentInParent()
{
	// 부모가 널 포인터인지 확인함
	if (m_Parent == nullptr)
	{
		return nullptr;
	}

	return m_Parent->GetComponent<T>();
}

inline std::vector<McCol::Component*>& McCol::GameObject::GetContainer()
{
	return m_Components;
}
