#pragma once
#include "CardPartsComponent.h"
class KeywordParts :
    public CardPartsComponent
{
private:
    Keyword m_Keyword;

public:
    KeywordParts(McCol::GameObject* owner);
    ~KeywordParts();

    void InitializeKeywordParts(Keyword keyword);
    void Initialize() override;

public:
    void SetKeyword(Keyword keyword);
    Keyword GetKeyword() const;

    std::wstring ExtractString() override;

    void SetOriginValue() override;
    void ResetToOriginValue() override;
};

