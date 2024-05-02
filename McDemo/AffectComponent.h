///*-------------------------------------------------------
//Affect Component
//
//- 효과는 PlayCard에서만 사용되므로 멤버 변수로 존재함
//- 생성자에서 게임 오브젝트(카드 및 캐릭터)를 설정해줌
//- 생성자에서 수정할 Attribute와 Affect, value 설정해줌
//- 생성자에서 value를 받아와 Affect enum class에서 해당하는 Affect를 설정해줌
//- None이면, Affect enum class에서 해당하는 Affect가 없다는 뜻으로 value만 저장하고 있으면 됨
//------------------------------------------------------ - */
//
//#pragma once
//#include "CardComponent.h"
//#include "Card.h"
//
//class McCol::GameObject;
//class AffectComponent :
//    public CardComponent
//{
//public:
//    enum class Affect
//    {
//        None,
//        AllDamageMinus3,
//        AllDamagePlus3,
//        NextDamagePlus2,
//        HealthPlus2,
//        For1Turn,
//        For2Turn,
//        For3Turn,
//        InitiativePlus1,
//        DamageMinus30Percent,
//        FirstCardRemove,
//        Paradox
//    };
//
//private:
//    Card::Attribute m_Attribute;
//    Affect m_Affect;
//    int m_ValueToModify;
//
//public:
//    AffectComponent(McCol::GameObject* owner, Card::Attribute attr, Affect affect, int value);
//
//public:
//    void ApplyEffect(McCol::GameObject* targetObj) override;
//};
//
