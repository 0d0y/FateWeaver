#pragma once
#include "../Engine/Scene.h"

namespace McCol
{
    class UI;
    class Button;
    class Panel;
    class EventSystem;
}

class Card;
class Deck;
class Mouse;
class CardFactory;

class RewardScene : public McCol::Scene
{
public:
    RewardScene();
    ~RewardScene() override;

private:
    McCol::GameObject* m_BgObj;
    McCol::GameObject* m_CameraObj;
    Mouse* m_MouseObj;

    McCol::Button* m_FateCardReward;
    McCol::Button* m_PlayCardReward;
    McCol::Button* m_RemoveReward;
    McCol::Button* m_SkipRewardButton;
    McCol::Button* m_BackButton;

    McCol::UI* m_SelectableReward;

    int m_RewardCount = 2;
    bool m_IsSelectableReward = true;

    //Card Test
    CardFactory* m_CardFactory;
    Deck* m_FateCardDeck;
    Deck* m_PlayCardDeck;

    int m_RewardIndex;

    bool m_IsFateCardReward;
    bool m_IsPlayCardReward;
    bool m_IsRemoveReward;

    Card* m_RewardFateCard;
    Card* m_RewardPlayCard;

public:
    void Enter() override;
    void Exit() override;
    void Update(const float& deltaTime) override;
    void FixedUpdate(const float& deltaTime) override;
    void LateUpdate(const float& deltaTime) override;
    void Render(McCol::D2DRender* renderer) override;

public:
    void FateCardRewardClick(std::any any);
    void PlayCardRewardClick(std::any any);
    void RemoveRewardClick(std::any any);

    void SkipButtonClick(std::any any);
    void BackButtonClick(std::any any);
};

