#include "KeywordParts.h"

KeywordParts::KeywordParts(McCol::GameObject* owner)
	: CardPartsComponent(owner)
	, m_Keyword(Keyword::NONE)
{
}

KeywordParts::~KeywordParts()
{
}

void KeywordParts::InitializeKeywordParts(Keyword keyword)
{
	m_Keyword = keyword;
}

void KeywordParts::Initialize()
{
}

void KeywordParts::SetKeyword(Keyword keyword)
{
	m_Keyword = keyword;
}

Keyword KeywordParts::GetKeyword() const
{
	return m_Keyword;
}

std::wstring KeywordParts::ExtractString()
{
	std::wstring result;

	std::wstring keywordString;
	switch (m_Keyword)
	{
	case Keyword::NONE:
		keywordString = L"";
		break;
	case Keyword::OVERLOAD:
		keywordString = L"°úÃæÀü";
		break;
	default:
		break;
	}

	result = keywordString;

	return result;
}

void KeywordParts::SetOriginValue()
{
}

void KeywordParts::ResetToOriginValue()
{
}
