#include "pch.h"
#include "Entity.h"

#include <sstream>

unsigned int McCol::Entity::m_NextID = 0;

McCol::Entity::Entity()
{
	m_ID = std::wstring(8 - std::to_wstring(m_NextID).length(), L'0') + std::to_wstring(m_NextID++);
}

McCol::Entity::Entity(std::wstring_view name)
	: m_Name(name)
{
	m_ID = std::wstring(8 - std::to_wstring(m_NextID).length(), L'0') + std::to_wstring(m_NextID++);
}

std::wstring McCol::Entity::GetID() const
{
	return m_ID;
}

std::wstring_view McCol::Entity::GetName() const
{
	return m_Name;
}
