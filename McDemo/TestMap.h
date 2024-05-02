#pragma once
#include "../Engine/Scene.h"

namespace McCol
{
    class UI;
    class Button;
    class MapButton;
    class BattleButton;
    class BattleButton;
    class BattleButton;
    class PopUp;
    class Panel;
    class EventSystem;
}

class Mouse;

enum class CharacterType;

class TestMap : public McCol::Scene
{
public:
    TestMap();
    ~TestMap() override;

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

    // Map 
    std::unordered_map<int, std::vector<McCol::MapButton*>> m_WholeStages;

    McCol::UI* m_WholeFrame;
    McCol::UI* m_MapFrame;

    McCol::BattleButton* m_Stage1;
    McCol::BattleButton* m_Stage2;
    McCol::BattleButton* m_Stage3;
    McCol::BattleButton* m_Stage4;
    McCol::BattleButton* m_Stage5;
    McCol::BattleButton* m_Stage6;
    McCol::BattleButton* m_Stage7;
    McCol::BattleButton* m_Stage8;
    McCol::BattleButton* m_Stage9;
    McCol::BattleButton* m_Stage10;
    McCol::BattleButton* m_Stage11;
    McCol::BattleButton* m_Stage12;
    McCol::BattleButton* m_Stage13;
    McCol::BattleButton* m_Stage14;
    McCol::BattleButton* m_Stage15;
    McCol::BattleButton* m_Stage16;
    McCol::BattleButton* m_Stage17;
    McCol::BattleButton* m_Stage18;
    McCol::BattleButton* m_Stage19;
    McCol::BattleButton* m_Stage20;
    McCol::BattleButton* m_Stage21;
    McCol::BattleButton* m_Stage22;
    McCol::BattleButton* m_Stage23;
    McCol::BattleButton* m_Stage24;
    McCol::BattleButton* m_Stage25;
    McCol::BattleButton* m_Stage26;
    McCol::BattleButton* m_BossStage;

    // UI 상단
    McCol::UI* UIUpperSector;
    McCol::UI* UIUpperIconLogo;
    McCol::UI* UIUpperIconHP;
    McCol::UI* UIUpperHPText;
    //McCol::UI* UIUpperIconNowFloor;
    //McCol::UI* UIUpperFloorText;
    McCol::Button* UIUpperTutorial;
    McCol::Button* UIUpperIconMap;
    McCol::Button* UIUpperFdeck;
    McCol::Button* UIUpperPdeck;
    McCol::Button* UIUpperExit;

    // 튜토리얼 팝업
    McCol::PopUp* UITutorialPopup;
    McCol::Button* UITutorialLeftButton;
    McCol::Button* UITutorialRightButton;
    McCol::Button* UITutorialBackButton;
    McCol::UI* UITutorialPageText;

    int m_LeftButtonCount = 1;
    int m_RightButtonCount = 1;

    std::vector<CharacterType> m_TypeArrange;

    // 랜덤 인카운터
    McCol::UI* UICultBg;
    McCol::UI* UILabBg;
    McCol::UI* UINexusBg;

    McCol::Button* m_UIClutFirstButton;
    McCol::Button* m_UIClutSecondButton;
    McCol::Button* m_UIClutThirdButton;

    McCol::Button* m_UILabFirstButton;
    McCol::Button* m_UILabSecondButton;
    McCol::Button* m_UILabThirdButton;

    McCol::Button* m_UINexusFirstButton;
    McCol::Button* m_UINexusSecondButton;


public:
    // UI Upper
    void UpperTutorialOn(std::any any);
    void UpperFdeckOn(std::any any);
    void UpperPdeckOn(std::any any);
    void UpperExitOn(std::any any);

    // 튜토리얼 팝업 내 버튼 이벤트
    void TutorialLeftButtonOn(std::any any);
    void TutorialRightButtonOn(std::any any);
    void TutorialBackButtonOn(std::any any);

    void ReserveButtonCount(int count);

    void AddCharacterType(CharacterType characterType);

    void BattleStart(std::any any);

    void ClutFirstButtonOn(std::any any);
    void ClutSecondButtonOn(std::any any);
    void ClutThirdButtonOn(std::any any);

    void LabFirstButtonOn(std::any any);
    void LabSecondButtonOn(std::any any);
    void LabThirdButtonOn(std::any any);

    void NexusFirstButtonOn(std::any any);
    void NexusSecondButtonOn(std::any any);

    void CrackStart(std::any any);
    void RandomStart(std::any any);
};

