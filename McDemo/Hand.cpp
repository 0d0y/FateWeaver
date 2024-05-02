#include "Hand.h"
#include "../Engine/Transform.h"
#include "../Engine/InputSystem.h"
#include "CardTexture.h"
#include "BattleScene.h"
#define _USE_MATH_DEFINES
#include <math.h>


Hand::Hand(std::wstring_view name, BattleScene* ownerScene)
	: GameObject(name, McCol::Layer::DECK)
	, m_OwnerScene(ownerScene)
	, m_Center{ 0.f, -300.0f }
	, m_OnMouseCard(nullptr)
	, m_IsRenderSelectedCard(false)
{
}

Hand::~Hand()
{
}

void Hand::Update(const float& deltaTime)
{
	for (FateCard* card : m_Cards)
	{
		card->Update(deltaTime);
	}

	if (m_OnMouseCard)
	{
		m_OnMouseCard->GetComponent<CardTexture>()->SetOffset({ 0.f, -80.f });
		m_OnMouseCard->GetComponent<McCol::Transform>()->SetScale({ 1.25f, 1.25f });

		for (auto card : m_Cards)
		{
			if (card != m_OnMouseCard)
			{
				card->GetComponent<McCol::Transform>()->SetScale({ 1.0f, 1.0f });
				card->GetComponent<CardTexture>()->SetOffset({ 0.f, 0.f });
			}
		}
	}
	if (!m_OnMouseCard)
	{
		for (auto card : m_Cards)
		{
			card->GetComponent<McCol::Transform>()->SetScale({ 1.0f, 1.0f });
			card->GetComponent<CardTexture>()->SetOffset({ 0.f, 0.f });
		}
	}

	if (McCol::InputSystem::GetInstance()->IsKeyDown(VK_LBUTTON))
	{
		if (m_OnMouseCard)
			m_ClickedCard = m_OnMouseCard;

	}

	if (m_ClickedCard)
	{
		UpdateCardPositions();
		McCol::Transform* ClickedCardTransform = m_ClickedCard->GetComponent<McCol::Transform>();
		ClickedCardTransform->SetPosition({ 0.f, -100.f });
		ClickedCardTransform->SetRotation(0.f);
		ClickedCardTransform->SetScale({ 1.5f, 1.5f });
		m_ClickedCard->GetComponent<CardTexture>()->SetOffset({ 0.f, 0.f });
		m_CollidingCardIndex.erase(std::remove(m_CollidingCardIndex.begin(), m_CollidingCardIndex.end(), m_ClickedCard->GetHandOrder()), m_CollidingCardIndex.end());

	}

	if (m_IsRenderSelectedCard)
	{
		UpdateCardPositions();
		if (m_OwnerScene->GetSelectedCard())
		{
			McCol::Transform* ClickedCardTransform = m_OwnerScene->GetSelectedCard()->GetComponent<McCol::Transform>();
			ClickedCardTransform->SetPosition({ 0.f, -100.f });
			ClickedCardTransform->SetRotation(0.f);
			ClickedCardTransform->SetScale({ 1.5f, 1.5f });
			m_OwnerScene->GetSelectedCard()->GetComponent<CardTexture>()->SetOffset({ 0.f, 0.f });
			m_CollidingCardIndex.erase(std::remove(m_CollidingCardIndex.begin(), m_CollidingCardIndex.end(), m_OwnerScene->GetSelectedCard()->GetHandOrder()), m_CollidingCardIndex.end());
		}
	}

	if (!m_ClickedCard && !m_IsRenderSelectedCard)
	{
		UpdateCardPositions();
	}

	HandPosToggle();
}

void Hand::Render(McCol::D2DRender* renderer)
{
	for (FateCard* card : m_Cards)
	{

		if (card != m_OnMouseCard || card != m_ClickedCard)
		{
			card->Render(renderer);
		}
	}

	if (m_OnMouseCard)
	{
		m_OnMouseCard->Render(renderer);
	}

	if (m_ClickedCard)
	{
		m_ClickedCard->Render(renderer);
	}

	if (m_IsRenderSelectedCard)
	{
		if (m_OwnerScene->GetSelectedCard())
			m_OwnerScene->GetSelectedCard()->Render(renderer);
	}
}

void Hand::FixedUpdate(const float& deltaTime)
{
	for (FateCard* card : m_Cards)
	{
		card->FixedUpdate(deltaTime);
	}
}

void Hand::AddCard(FateCard* card)
{
	m_Cards.push_back(card);
	card->Initialize();
	card->SetAble(true);
	card->SetMyOwnerDeck(this);
	UpdateCardPositions();
}

void Hand::RemoveCard()
{
	if (!m_Cards.empty())
	{
		FateCard* lastCard = m_Cards.back();
		m_Cards.pop_back();
		lastCard->SetAble(false);
		UpdateCardPositions();
		//delete lastCard;
	}
}

FateCard* Hand::DrawCard()
{
	if (!m_Cards.empty())
	{
		FateCard* drawnCard = m_Cards.back();
		m_Cards.pop_back();

		return drawnCard;
	}
	return nullptr;
}

void Hand::PopCard(FateCard* cardToPop) 
{
	auto cardIterator = std::find(m_Cards.begin(), m_Cards.end(), cardToPop);

	if (cardIterator != m_Cards.end())
	{
		m_Cards.erase(cardIterator);
		UpdateCardPositions();
	}
}

void Hand::UpdateCardPositions()
{
	int totalCards = m_Cards.size();
	if (totalCards == 0)
		return;
	float incrementAngle = 3.5f;
	float startAngle = -90.f - (incrementAngle * (totalCards - 1) / 2.f);

	float maxAngle = 28.5f;

	int maxCardsWithinRange = static_cast<int>(ceil((maxAngle) / incrementAngle)) + 1;

	if (totalCards > maxCardsWithinRange)
	{
		incrementAngle = maxAngle / (totalCards - 1);
		startAngle = -90.f - (maxAngle / 2);
	}

	for (int i = 0; i < totalCards; i++)
	{
		McCol::Transform* cardTransform = m_Cards[i]->GetComponent<McCol::Transform>();
		if (cardTransform)
		{
			float radius = 2000.0f;
			float radians = (startAngle + (incrementAngle * i)) * (M_PI / 180.0f);
			float posX = radius * cosf(radians);
			float posY = radius * sinf(radians);
			float rotationAngle = -90 - (startAngle + (incrementAngle * i));

			cardTransform->SetPosition(McCol::Vector2(posX, -posY - 2520.f));
			cardTransform->SetRotation(rotationAngle);

			m_Cards[i]->SetHandOrder(static_cast<float>(i));
		}
	}
}

void Hand::SetHandCollidable(bool isCollidable)
{
	for (auto card : m_Cards)
	{
		card->Setcollidable(isCollidable);
	}
}

std::vector<FateCard*> Hand::GetHandDeckList() const
{
	return m_Cards;
}


std::vector<int> Hand::GetCollidingCardIndex()
{
	return m_CollidingCardIndex;
}

void Hand::PushBackCollidingCardIndex(int handorder)
{
	m_CollidingCardIndex.push_back(handorder);
}

void Hand::ResetCollidingCardIndex()
{
	m_CollidingCardIndex.clear();
}

void Hand::SetOnMouseCard(FateCard* fc)
{
	m_OnMouseCard = fc;
}

FateCard* Hand::GetOnMouseCard() const
{
	return m_OnMouseCard;
}

FateCard* Hand::GetClickedCard() const
{
	return m_ClickedCard;
}

void Hand::SetClickedCard(FateCard* fc)
{
	m_ClickedCard = fc;
}

void Hand::RemoveCollidingCardIndex(FateCard* fc)
{
	m_CollidingCardIndex.erase(std::remove(m_CollidingCardIndex.begin(), m_CollidingCardIndex.end(), fc->GetHandOrder()), m_CollidingCardIndex.end());
}
void Hand::HandPosToggle()
{
	static float downLine = -300.f;
	static float sideLine = 350.f;

	auto mousePosY = McCol::InputSystem::GetInstance()->GetMousePos().y;
	auto mousePosX = McCol::InputSystem::GetInstance()->GetMousePos().x;

	if (mousePosY < downLine && mousePosX < sideLine && mousePosX > -sideLine)
	{
		for (auto card : m_Cards)
		{
			if (card == m_ClickedCard || card == m_OwnerScene->GetSelectedCard())
				continue;
			auto cardPos = card->GetComponent<McCol::Transform>()->GetPosition();
			card->GetComponent<McCol::Transform>()->SetPosition({ cardPos.x, cardPos.y + 170 });
		}
	}
}