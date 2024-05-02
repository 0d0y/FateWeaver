#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/EventHandler.h"


#include "Elements.h"

class StateIconManager;
class StateManager;
class HpRenderer;

class Character : public McCol::GameObject, public McCol::EventHandler
{
public:
	Character(std::wstring_view name, CharacterIndex battleIndex, CharacterType type);
	~Character() override;

protected:
	int m_MaxHealth;
	int m_Health;
	int m_Defense;
	CharacterIndex m_BattleIndex;
	CharacterType m_Type;
	bool m_IsAlive;

	std::queue<int> m_DamagedQueue;
	float m_ProgressTime = 0.0f;
	float m_DelayedTime = 0.5f;
	StateIconManager* m_StateIconManager;
	HpRenderer* m_HpRenderer;

public:
	void Initialize() override;
	void FixedUpdate(const float& deltaTime) override;

public:
	void ApplyOwnerState(CardInfo& info);
	//void ReceiveCard(CardInfo info);

	void SetMaxHealth(int maxHealth);
	void SetCurrentHealth(int curHealth);
	void Heal(int heal);
	int GetHealth();
	int GetMaxHealth();
	void SetDefense(int def);
	bool IsAlive();

	void QueuedDamage(CardInfo& info);
	void ApplyCardInfo(CardInfo& info);

	CharacterIndex GetBattleIndex();
	CharacterType GetType();
	StateIconManager* GetIconManager();


private:
	void ApplyDelayedDamage(const float& deltaTime);
	void ApplyDefense(int& damage);
	void StartTurn(std::any param);
};
