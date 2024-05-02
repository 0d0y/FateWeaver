#pragma once
#include "MapButton.h"

enum class CharacterType;

enum class BattleIconType
{
    Monster,
    Elite,
    Boss
};

enum class BattleStageType
{
    START,
    FIRST,
    SECOND,
    THIRD,
    ELITE,
    BOSS
};

namespace McCol
{
    class BattleButton : public MapButton
    {
    public:
        BattleButton(std::wstring_view name, BattleIconType type, BattleStageType stageType, int stageIndex);
        ~BattleButton() override;

    private:
        BattleStageType m_StageType;
        int m_StageIndex;

    public:
        void Initialize() override;
        void Update(const float& deltaTime) override;
        void FixedUpdate(const float& deltaTime) override;
        void Render(McCol::D2DRender* renderer) override;

        void HandleCollisionEnter(McCol::Collider* otherCollider) override;
        void HandleCollisionStay(McCol::Collider* otherCollider) override;
        void HandleCollisionExit(McCol::Collider* otherCollider) override;

    };
}

