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
class Mouse;

class CardFactory;
class Deck;

class TestMain : public McCol::Scene
{
public:
    TestMain();
    ~TestMain() override;

    void Enter() override;
    void Exit() override;
    void Update(const float& deltaTime) override;
    void FixedUpdate(const float& deltaTime) override;
    void LateUpdate(const float& deltaTime) override;
    void Render(McCol::D2DRender* renderer) override;

private:
    McCol::GameObject* m_BgObj;
    McCol::GameObject* m_CameraObj;
    Mouse* m_MouseObj;

    McCol::Button* m_PlayButton;
    McCol::Button* m_ArchiveButton;
    McCol::Button* m_ExitButton;

    McCol::UI* m_PlayButtonArrow;
    McCol::UI* m_ArchiveButtonArrow;
    McCol::UI* m_ExitButtonArrow;

    McCol::UI* m_PopUpFrame;
    McCol::UI* m_FateCardArchive;
    McCol::UI* m_PlayCardArchive;
    McCol::Button* m_FateCardArchiveButton;
    McCol::Button* m_PlayCardArchiveButton;
    McCol::Button* m_BackButton;

    McCol::Button* m_PageLeftButton;
    McCol::Button* m_PageRightButton;

    McCol::Panel* m_ArchiveCardTest;

    McCol::GameObject* test;

    CardFactory* m_CardFactory;
    Deck* m_FateCardDeck;
    Deck* m_PlayCardDeck;

    int m_FateCardPageIndex = 1; // Max : 3
    int m_PlayCardPageIndex = 1; // Max : 3

    bool m_IsFateCardAble;
    bool m_IsPlayCardAble;


public:
    void PlayButtonClickEvent(std::any any);
    void ArchiveButtonClickEvent(std::any any);
    void ExitButtonClickEvent(std::any any);

    void PlayButtonOnEvent(std::any any);
    void ArchiveButtonOnEvent(std::any any);
    void ExitButtonOnEvent(std::any any);

    void PlayButtonOutEvent(std::any any);
    void ArchiveButtonOutEvent(std::any any);
    void ExitButtonOutEvent(std::any any);

    void BackButtonClickEvent(std::any any);
    void FateCardButtonOnEvent(std::any any);
    void PlayCardButtonOnEvent(std::any any);
    void PageLeftButtonOnEvent(std::any any);
    void PageRightButtonOnEvent(std::any any);
    


};

