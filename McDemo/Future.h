#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/EventHandler.h"
#include "../Engine/Vector2.h"

#include <list>

class PlayCard;

// todo : 이월 및 즉시실행

class Future : public McCol::GameObject, public McCol::EventHandler
{
public:
	Future();
	~Future() override = default;

private:
	int m_PrevInitiative;
	int m_DuplicateInitiative;
	std::list<PlayCard*> m_CardsOnFuture;

	PlayCard* m_OnMouseCard;
	PlayCard* m_ClickedCard;

public:
	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;
	void Render(McCol::D2DRender* renderer) override;

	bool IsMoment();
	PlayCard* GetCarryOverCard();

	void AddCard(PlayCard* card);
	PlayCard* PopFrontCard();
	bool ShowFrontCard();
	size_t Size() { return m_CardsOnFuture.size(); }

	// Event Func
	void Sort(std::any param = nullptr);

	void PopCard(PlayCard* cardToPop)
	{
		auto cardIterator = std::find(m_CardsOnFuture.begin(), m_CardsOnFuture.end(), cardToPop);

		if (cardIterator != m_CardsOnFuture.end())
		{
			m_CardsOnFuture.erase(cardIterator);
		}
	}

public:
	std::list<PlayCard*>& GetFutureDeckList();

	void SetOnMouseCard(PlayCard* pc);
	PlayCard* GetOnMouseCard() const;

	void SetClickedCard(PlayCard* pc);
	PlayCard* GetClickedCard() const;


	void SetFutureCollidable(bool isCollidable);

private:
	McCol::Vector2 GetRenderPos(int initiative);


	// Event Func
	void PopEffect(std::any param);
	void PlayCardEffect(std::any param);
};
