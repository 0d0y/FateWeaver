#include "pch.h"
#include "TimeSystem.h"

#include <string>

McCol::TimeSystem::TimeSystem()
	: m_CurCount{}
	, m_PrevCount{}
	, m_Frequency{}
	, m_DeltaTime(0.0)
	, m_Acc(0.0)
	, m_CallCount(0)
{
}

void McCol::TimeSystem::Initialize()
{
	// 현재 카운트
	QueryPerformanceCounter(&m_PrevCount);

	// 초당 카운트 횟수
	QueryPerformanceFrequency(&m_Frequency);
}

void McCol::TimeSystem::Update()
{
	QueryPerformanceCounter(&m_CurCount);
	m_DeltaTime = static_cast<double>(m_CurCount.QuadPart - m_PrevCount.QuadPart) / static_cast<double>(m_Frequency.QuadPart);
	m_PrevCount = m_CurCount;

	m_CallCount++;

	if (m_Acc > 1.0)
	{
		m_Acc -= 1.0;
		SetWindowTextA(GetActiveWindow(), ("FPS : " + std::to_string(m_CallCount)).c_str());
		m_CallCount = 0;
	}
	m_Acc += m_DeltaTime;


#ifdef _DEBUG
	if (m_DeltaTime > 1.0 / 60.0)
		m_DeltaTime = 1.0 / 60.0;
#endif
}
void McCol::TimeSystem::Finalize()
{
}

float McCol::TimeSystem::GetDeltaTime()
{
	return static_cast<float>(m_DeltaTime);
}