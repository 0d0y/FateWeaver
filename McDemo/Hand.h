#pragma once
#include "..\Engine\GameObject.h"
#include "FateCard.h"
#include "..\RenderEngine\D2DRender.h"
#include "..\Engine\Vector2.h"

class BattleScene;

class Hand :
	public McCol::GameObject
{
private:
	std::vector<FateCard*> m_Cards;
	McCol::Vector2 m_Center;
	std::vector<int> m_CollidingCardIndex;

	BattleScene* m_OwnerScene;

	FateCard* m_OnMouseCard;
	FateCard* m_ClickedCard;
	bool m_IsDown = false;

	bool m_IsRenderSelectedCard;

public:
	Hand(std::wstring_view name, BattleScene* ownerScene);
	~Hand() override;

public:
	void Update(const float& deltaTime) override;
	void Render(McCol::D2DRender* renderer) override;
	void FixedUpdate(const float& deltaTime) override;


public:
	void AddCard(FateCard* card);
	void RemoveCard();
	void PopCard(FateCard* cardToPop);
	void UpdateCardPositions();

	std::vector<int> GetCollidingCardIndex();

	FateCard* DrawCard();

	size_t Size() { return m_Cards.size(); }

	void PushBackCollidingCardIndex(int handorder);
	void ResetCollidingCardIndex();

	void SetHandCollidable(bool isCollidable);
	std::vector<FateCard*> GetHandDeckList() const;

	//const std::vector<FateCard*>& GetCards() const
	//{
	//	return m_Cards;
	//}


	void SetIsRenderSelectedCard(bool isRender) { m_IsRenderSelectedCard = isRender; }
	void SetOnMouseCard(FateCard* fc);
	FateCard* GetOnMouseCard() const;

	void SetClickedCard(FateCard* fc);
	void RemoveCollidingCardIndex(FateCard* fc);
	FateCard* GetClickedCard() const;

	void HandPosToggle();
};

