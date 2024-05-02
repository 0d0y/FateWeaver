#pragma once

#include <fmod.hpp>

namespace McCol
{
	class SoundSystem
	{
	private:
		SoundSystem();
		~SoundSystem() = default;

	private:
		static SoundSystem* m_Instance;

		FMOD::System*	m_System;
		FMOD_RESULT		m_Result;
		unsigned int	m_Version;
		std::map<std::string_view, FMOD::Channel*>		m_Channels;
		std::map<std::string_view, FMOD::Sound*>		m_Sounds;
		std::map<std::string_view, std::string_view>	m_RelatedChannel;

	public:
		static SoundSystem* GetInstance()
		{
			if (m_Instance == nullptr)
				m_Instance = new SoundSystem;

			return m_Instance;
		}

		void Initialize();
		void Update();
		void Finalize();

		// info : sound 와 channel 은 1:1 관계일 필요는 없으나 재생, 정지는 같은 channel 내 모든 sound 가 동시에 영향을 받음
		// 사운드를 개별로 관리해야 할 필요가 있을 경우 1:1 로 생성해야 함
		void CreateSound(const std::string& filePath, FMOD_MODE mode, std::string_view soundName, std::string_view channelName);
		void DeleteSound(std::string_view soundName);						// sound 삭제
		void PlaySoundM(std::string_view soundName);						// sound 가 포함된 channel 활성화 및 재생
		void Play(std::string_view soundName);								// sound 가 포함된 channel 이 일시정지 상태일 경우 이어서 재생
		void Pause(std::string_view soundName);								// sound 가 포함된 channel 일시정지
		void Stop(std::string_view soundName);								// sound 가 포함된 channel 비활성화(Play 하려면 활성화 필요)
		void Replay(std::string_view soundName);							// sound 가 포함된 channel 비활성화 해당 sound 만 처음부터 재생
		void SetVolume(std::string_view channelName, float volume);			// channel 볼륨 설정
	};
}
