#pragma once
#include <string_view>

namespace McCol
{
	class Entity
	{
	public:
		Entity();
		Entity(std::wstring_view name);
		virtual ~Entity() = default;

	private:
		static unsigned int m_NextID;

	protected:
		std::wstring m_ID;
		std::wstring m_Name;
			 
	public:	 
		std::wstring GetID() const;
		std::wstring_view GetName() const;
	};
}

