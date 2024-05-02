#include "Future.h"

#include "CardTexture.h"
#include "PlayCard.h"
#include "Character.h"
#include "Elements.h"

#include "../Engine/EventSystem.h"
#include "../Engine/Transform.h"
#include "../Engine/OBB.h"
#include "../Engine/TextureRenderer.h"
#include "../Engine/InputSystem.h"

using namespace McCol;

Future::Future()
	: GameObject(L"Future Area", McCol::Layer::DECK)
	, m_PrevInitiative(-1)
	, m_DuplicateInitiative(0)
{
	EventSystem::GetInstance()->Subscribe(L"FUTURE_SORT", MakeListenerInfo(&Future::Sort));
	EventSystem::GetInstance()->Subscribe(L"FUTURE_POP", MakeListenerInfo(&Future::PopEffect));
	EventSystem::GetInstance()->Subscribe(L"EXECUTE_PLAY_CARD", MakeListenerInfo(&Future::PlayCardEffect));
	AddComponent<TextureRenderer>()->LoadTexture(L"../Resource/UI/UI_FutureTerritory.png", L"UI_FutureTerritory");
	AddComponent<Transform>()->SetPosition({ 1.5f, 370.f });
}

void Future::Update(const float& deltaTime)
{
	for (const auto& playCard : m_CardsOnFuture)
	{
		playCard->Update(deltaTime);
	}

	if (McCol::InputSystem::GetInstance()->IsKeyDown(VK_LBUTTON))
	{
		if (m_OnMouseCard)
			m_ClickedCard = m_OnMouseCard;
		else
			m_ClickedCard = nullptr;
	}
}

void Future::FixedUpdate(const float& deltaTime)
{
	for (const auto& playCard : m_CardsOnFuture)
	{
		playCard->FixedUpdate(deltaTime);
	}
}

void Future::Render(McCol::D2DRender* renderer)
{
	GameObject::Render(renderer);

	for (const auto& card : m_CardsOnFuture)
	{
		card->Render(renderer);
	}
	if (m_OnMouseCard)
		m_OnMouseCard->Render(renderer);
}

bool Future::IsMoment()
{
	if (m_CardsOnFuture.empty())
		return false;

	if (m_CardsOnFuture.front()->GetInitiative() <= 0)
		return true;

	return false;
}

PlayCard* Future::GetCarryOverCard()
{
	if (m_CardsOnFuture.empty())
		return nullptr;

	if (m_CardsOnFuture.back()->GetInitiative() >= 10)
	{
		auto overCard = m_CardsOnFuture.back();
		m_CardsOnFuture.pop_back();

		return overCard;
	}

	return nullptr;
}

void Future::AddCard(PlayCard* card)
{
	if (card == nullptr)
		return;

	m_CardsOnFuture.push_back(card);
	card->Initialize();
	card->SetAble(false);
	card->SetMyOwnerDeck(this);
	auto cardTexture = card->GetComponent<CardTexture>();
	cardTexture->SetIsFutureRender(true);
	cardTexture->SetIsCardRender(false);
	auto illust = cardTexture->GetIllustration();
	card->GetComponent<Transform>()->SetScale({ 0.5f, 0.5f });
	card->GetComponent<OBB>()->SetSize({ illust->GetSize().width * 0.9f, illust->GetSize().height * 0.6f });
}

PlayCard* Future::PopFrontCard()
{
	PlayCard* frontCard = nullptr;

	if (!m_CardsOnFuture.empty())
	{
		frontCard = m_CardsOnFuture.front();
		frontCard->GetComponent<CardTexture>()->SetIsFutureRender(false);
		frontCard->GetComponent<CardTexture>()->SetIsCardRender(true);
		frontCard->GetComponent<Transform>()->SetScale({ 1.0f, 1.0f });
		auto frame = frontCard->GetComponent<CardTexture>()->GetFrame();
		frontCard->GetComponent<OBB>()->SetSize({ frame->GetSize().width, frame->GetSize().height });
		m_CardsOnFuture.pop_front();
	}

	return frontCard;
}

bool Future::ShowFrontCard()
{
	if (!m_CardsOnFuture.empty())
	{
		for (auto cf : m_CardsOnFuture)
		{
			if (!cf->IsAble())
			{
				cf->SetAble(true);
				return true;
			}
		}
		return false;
	}

	return false;
}

struct Compare {
	// 주도력 -> 카드 주인 위치 기준 오름차순 정렬
	bool operator()(const PlayCard* lhs, const PlayCard* rhs) const {

		if (lhs->GetInitiative() && rhs->GetInitiative())
			if (lhs->GetInitiative() == rhs->GetInitiative()) {
				if (lhs->GetCharacterIndex() == 0) return false; // lhs가 0이면 우선순위를 낮춥니다.
				if (rhs->GetCharacterIndex() == 0) return true;  // rhs가 0이면 우선순위를 높입니다.
				return lhs->GetCharacterIndex() < rhs->GetCharacterIndex();
			}
		return lhs->GetInitiative() < rhs->GetInitiative();
	}
};

void Future::Sort(std::any param)
{
	m_CardsOnFuture.sort(Compare());

	for (const auto& card : m_CardsOnFuture)
	{
		auto curPos = GetRenderPos(card->GetInitiative());
		card->GetComponent<Transform>()->SetPosition(curPos);
	}
}

std::list<PlayCard*>& Future::GetFutureDeckList()
{
	return m_CardsOnFuture;
}

void Future::SetOnMouseCard(PlayCard* pc)
{
	m_OnMouseCard = pc;
}

PlayCard* Future::GetOnMouseCard() const
{
	return m_OnMouseCard;
}

void Future::SetClickedCard(PlayCard* pc)
{
	m_ClickedCard = pc;
}

PlayCard* Future::GetClickedCard() const
{
	return m_ClickedCard;
}

McCol::Vector2 Future::GetRenderPos(int initiative)
{
	Vector2 cardPos = { -585, 370.f };

	// 카드 가로축 + 이동
	cardPos.x += static_cast<float>(initiative * 130);

	// 이전 카드와 중복 카드일시
	if (initiative == m_PrevInitiative)
	{
		m_DuplicateInitiative++;

		// 카드 세로축 - 이동
		cardPos.y -= static_cast<float>(m_DuplicateInitiative * 85);
	}
	else
	{
		m_DuplicateInitiative = 0;
	}

	m_PrevInitiative = initiative;

	return cardPos;
}

void Future::SetFutureCollidable(bool isCollidable)
{
	for (auto card : m_CardsOnFuture)
	{
		card->Setcollidable(isCollidable);
	}

}
void Future::PopEffect(std::any param)
{

}

void Future::PlayCardEffect(std::any param)
{
}

