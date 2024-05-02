#include "Mouse.h"
#include <windows.h>
#include "../Engine/Macro.h"
#include "../Engine/Transform.h"
#include "../Engine/OBB.h"
#include "../Engine/TextureRenderer.h"
#include "../Engine/PrimitiveRenderer.h"
#include "../Engine/InputSystem.h"
#include "../RenderEngine/D2DRender.h"
#include "../Engine/MouseCollisionSystem.h"
#include "Card.h"

using namespace McCol;

Mouse::Mouse(std::wstring_view name)
	: GameObject(L"Mouse", Layer::MOUSE)
	, m_IsMouseVisible(true)
	, m_Size{ 4.f, 4.f }
	, m_CollisionArea{ 0, }
{
	Transform* transform = AddComponent<Transform>();
	AddComponent<OBB>();
	TextureRenderer* tr = AddComponent<TextureRenderer>();
	tr->LoadTexture(L"../Resource/FW_Cursor.ico", L"Mouse Cursor");
	tr->SetTextureScale(0.5f);
	tr->SetOffset({ 73.f, 73.f });
	PrimitiveRenderer* pr = AddComponent<PrimitiveRenderer>(); //TODO: PrimitiveRenderer ¾ø¾Ö±â
	pr->SetPmRectangle(m_Size.x, m_Size.y);
	ShowCursor(false);
}

Mouse::~Mouse()
{
}

void Mouse::Initialize()
{
	__super::Initialize();
	GetComponent<OBB>()->SetSize(m_Size);
	MouseCollisionSystem::GetInstance()->SetMouseOBB(GetComponent<OBB>());
}

void Mouse::Update(const float& deltaTime)
{
	__super::Update(deltaTime);

	m_Pos = InputSystem::GetInstance()->GetMousePos();
	GetComponent<Transform>()->SetPosition(m_Pos);
	m_CollisionArea.left = m_Pos.x - m_Size.x / 2;
	m_CollisionArea.top = m_Pos.y - m_Size.y / 2;
	m_CollisionArea.right = m_CollisionArea.left + m_Size.x;
	m_CollisionArea.bottom = m_CollisionArea.top + m_Size.y;
}

void Mouse::FixedUpdate(const float& deltaTime)
{
	__super::FixedUpdate(deltaTime);
}

void Mouse::Render(McCol::D2DRender* renderer)
{
	__super::Render(renderer);
}

void Mouse::HandleCollisionStay(McCol::Collider* otherCollider)
{
	//if (m_CollidingCard)
	//{
	//	DEBUGPRINT("Stay \n");
	//	//m_CollidingCard->GetComponent<McCol::Transform>()->SetScale({ 0.5f,0.5f });
	//}
}

void Mouse::HandleCollisionEnter(McCol::Collider* otherCollider)
{
	/*m_CollidingCard = dynamic_cast<Card*>(otherCollider->GetOwner());
	if (m_CollidingCard)
	{
		DEBUGPRINT("Enter \n");
	}*/

}

void Mouse::HandleCollisionExit(McCol::Collider* otherCollider)
{
	//if (m_CollidingCard)
	//{
	//	//m_CollidingCard->GetComponent<McCol::Transform>()->SetScale({ 0.3f, 0.3f });
	//	DEBUGPRINT("exit \n");
	//	m_CollidingCard = nullptr;

	//}
}

void Mouse::ToggleMouseVisibility()
{
	m_IsMouseVisible = !m_IsMouseVisible;
	ShowCursor(m_IsMouseVisible);
}