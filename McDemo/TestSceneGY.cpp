#include "TestSceneGY.h"

#include "FateCard.h"
#include "PlayCard.h"
#include "Deck.h"
#include "CardComponentHeader.h"
#include "CardFactory.h"
#include "Hand.h"
#include "Mouse.h"

#include "../Engine/MouseCollisionSystem.h"
#include "../Engine/Collider.h"
#include "../Engine/OBB.h"
#include "../Engine/Transform.h"
#include "../Engine/TextureRenderer.h"
#include "../RenderEngine/D2DTextureSystem.h"
#include "../Engine/Camera.h"
#include "../Engine/InputSystem.h"
#include "../Engine/PrimitiveRenderer.h"



using namespace McCol;

TestSceneGY::TestSceneGY()
	: Scene(L"근영이의 테스트 씬")

{
}

TestSceneGY::~TestSceneGY()
{
}

void TestSceneGY::Enter()
{
	m_CardFactory = new CardFactory;
	//PlayCard* card = new PlayCard(L"카드");
	//card->AddComponent<TextureRenderer>();
	//card->AddComponent<Transform>();
	//card->GetComponent<Transform>()->SetPosition({ 0.f, 0.f });
	//card->GetComponent<Transform>()->SetScale({ 1.0f, 1.0f });
	//card->GetComponent<TextureRenderer>()->SetBitmap(D2DTextureSystem::GetInstance()->LoadTexture(L"../Resource/FateCardExample.png", L"FateCardExample"));
	//card->GetComponent<TextureRenderer>()->SetTextureScale(1.0f);

	m_Camera = new GameObject(L"카메라");
	m_Camera->AddComponent<PrimitiveRenderer>();
	m_Camera->AddComponent<Transform>();
	m_Camera->AddComponent<Camera>();
	m_Camera->GetComponent<Transform>()->SetPosition({ 0.f, 0.f });
	m_Camera->GetComponent<Transform>()->SetScale({ 1.f, 1.f });


	//m_Hand = new Hand(L"손패", this);

	//TempGO* rect1 = new TempGO(L"Rect1");
	//m_Objects.push_back(rect1);
	//Transform* rectTransform1 = rect1->AddComponent<Transform>();
	//rectTransform1->SetPosition(Vector2(500, 700));
	//rectTransform1->SetScale({ 1.f, 1.f });
	//rectTransform1->SetSize({ 100.f, 100.f });
	//OBB* Colli1 = rect1->AddComponent<OBB>();
	//Colli1->Initialize();
	//m_CollisionSystem->AddCollider(Colli1);
	////Colli1->SetColliPosOffset({ 100.f, 0.f });
	//Colli1->SetColliScaleOffset({ 1.1f, 1.1f });

	//TempGO* rect2 = new TempGO(L"Rect2");
	//m_Objects.push_back(rect2);
	//Transform* rectTransform2 = rect2->AddComponent<Transform>();
	//rectTransform2->SetPosition(Vector2(1000, 700));
	//rectTransform2->SetScale({ 1.f, 1.f });
	//rectTransform2->SetSize({ 100.f, 100.f });
	//OBB* Colli2 = rect2->AddComponent<OBB>();
	//Colli2->Initialize();
	//m_CollisionSystem->AddCollider(Colli2);
	//Colli2->SetColliScaleOffset({ 1.1f, 1.1f });

	Scene::EventCreateOBJ(m_Camera);
	//Scene::EventCreateOBJ(m_Hand);
}

void TestSceneGY::Exit()
{
	Scene::Exit();
}

void TestSceneGY::Update(const float& deltaTime)
{
	Scene::Update(deltaTime);

	if (InputSystem::GetInstance()->IsKeyHold('1'))
	{
		m_Hand->AddCard(m_CardFactory->MakeTestPlayerFateCard());
	}

	if (InputSystem::GetInstance()->IsKeyHold('2'))
	{
		PlayCard* card = m_CardFactory->MakeTestPlayerPlayCard();
		Scene::EventCreateOBJ(card);
	}

	if (InputSystem::GetInstance()->IsKeyHold('3'))
	{
		PlayCard* card = m_CardFactory->MakeTestMonsterPlayCard();
		Scene::EventCreateOBJ(card);
	}

	if (InputSystem::GetInstance()->IsKeyHold('4'))
	{
		m_Hand->RemoveCard();
	}

	MouseCollisionSystem::GetInstance()->Update(deltaTime);
}

void TestSceneGY::FixedUpdate(const float& deltaTime)
{
	Scene::FixedUpdate(deltaTime);
}

void TestSceneGY::LateUpdate(const float& deltaTime)
{
	Scene::LateUpdate(deltaTime);
}

void TestSceneGY::Render(McCol::D2DRender* renderer)
{
	Scene::Render(renderer);
}
