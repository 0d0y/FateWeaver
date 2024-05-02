//#include "AffectComponent.h"
//
//AffectComponent::AffectComponent(McCol::GameObject* owner, Card::Attribute attr, Affect affect, int value)
//    : CardComponent(owner)
//    , m_Attribute(attr)
//    , m_Affect(affect)
//    , m_ValueToModify(value)
//{
//}
//
//void AffectComponent::ApplyEffect(McCol::GameObject* targetObj)
//{
//    Card* testCard = dynamic_cast<Card*>(targetObj);
//
//    int attributeValue = testCard->GetAttribute(m_Attribute);
//    if (attributeValue)
//    {
//        switch (m_Affect)
//        {
//        case Affect::None:
//        {
//            testCard->SetAttribute(m_Attribute, 0);
//        }
//        case Affect::AllDamageMinus3:
//        {
//            testCard->SetAttribute(m_Attribute, attributeValue - 3);
//        }
//        case Affect::AllDamagePlus3:
//        {
//            testCard->SetAttribute(m_Attribute, attributeValue + 3);
//        }
//        case Affect::NextDamagePlus2:
//        {
//            testCard->SetAttribute(m_Attribute, attributeValue + 2);
//        }
//        case Affect::HealthPlus2:
//        {
//            testCard->SetAttribute(m_Attribute, attributeValue + 2);
//        }
//        case Affect::For1Turn:
//        {
//            testCard->SetAttribute(m_Attribute, attributeValue);
//        }
//        case Affect::For2Turn:
//        {
//            testCard->SetAttribute(m_Attribute, attributeValue);
//        }
//        case Affect::For3Turn:
//        {
//            testCard->SetAttribute(m_Attribute, attributeValue);
//        }
//        case Affect::InitiativePlus1:
//        {
//            testCard->SetAttribute(m_Attribute, attributeValue + 1);
//        }
//        case Affect::DamageMinus30Percent:
//        {
//            testCard->SetAttribute(m_Attribute, attributeValue - (attributeValue * 30 / 100));
//        }
//        case Affect::FirstCardRemove:
//        {
//            testCard->SetAttribute(m_Attribute, 0);
//        }
//        case Affect::Paradox:
//        {
//            testCard->SetAttribute(m_Attribute, attributeValue);
//        }
//        }
//    }
//}
//
