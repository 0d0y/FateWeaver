#include "pch.h"
#include "GameObject.h"

#include "Component.h"


McCol::GameObject::GameObject(std::wstring_view name, Layer layer)
	: Entity(name)
	, m_Parent(nullptr)
	, m_Layer(layer)
	, m_IsAble(true)
{
}

McCol::GameObject::GameObject(std::wstring_view name)
	: Entity(name)
	, m_Parent(nullptr)
	, m_Layer(Layer::DEFAULT)
	, m_IsAble(true)
{
}

McCol::GameObject::~GameObject()
{
	// 즉각 삭제
	for (const Component* cp : m_Components)
	{
		delete cp;
	}
}

void McCol::GameObject::Initialize()
{
	for (Component* cp : m_Components)
	{
		cp->Initialize();
	}
}

void McCol::GameObject::Update(const float& deltaTime)
{
	if (!m_IsAble)
		return;

	for (IUpdatable* ua : m_Updatables)
	{
		ua->Update(deltaTime);
	}
}

void McCol::GameObject::FixedUpdate(const float& deltaTime)
{
	if (!m_IsAble)
		return;

	for (IFixedUpdatable* cp : m_FixedUpdatables)
	{
		cp->FixedUpdate(deltaTime);
	}
}

void McCol::GameObject::Render(McCol::D2DRender* renderer)
{
	if (!m_IsAble)
		return;

	for (IRenderable* cp : m_Renderables)
	{
		cp->Render(renderer);
	}
}

void McCol::GameObject::HandleCollisionStay(Collider* otherCollider)
{
}

void McCol::GameObject::HandleCollisionEnter(Collider* otherCollider)
{
}

void McCol::GameObject::HandleCollisionExit(Collider* otherCollider)
{
}

void McCol::GameObject::SetAble(bool able)
{
	m_IsAble = able;
}

void McCol::GameObject::SetLayer(Layer layer)
{
	// 씬 실행중에 동적으로 변경하는 기능은 없음
	m_Layer = layer;
}

McCol::GameObject* McCol::GameObject::GetParent() const
{
	if (m_Parent == nullptr)
		return nullptr;

	return m_Parent;
}

void McCol::GameObject::AddChild(GameObject* child)
{
	m_Children.push_back(child);
	child->SetParent(this);
}

void McCol::GameObject::SetParent(GameObject* parent)
{
    m_Parent = parent;
}

bool McCol::GameObject::IsAble()
{
	return m_IsAble;
}

McCol::Layer McCol::GameObject::GetLayer()
{
	return m_Layer;
}


