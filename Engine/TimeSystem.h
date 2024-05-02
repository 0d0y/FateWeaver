#pragma once
#include "IUpdatable.h"

namespace McCol
{
	class TimeSystem
	{
	public:
		TimeSystem();
		~TimeSystem() = default;

	private:
		LARGE_INTEGER m_CurCount;
		LARGE_INTEGER m_PrevCount;
		LARGE_INTEGER m_Frequency;

		double m_DeltaTime;				// 프레임 간의 시간 값
		double m_Acc;					// 1초 체크를 위한 누적 시간
		UINT m_CallCount;				// 함수 호출 횟수

	public:
		void Initialize();
		void Update();
		void Finalize();

	public:
		float GetDeltaTime();
	};
}
