#include "pch.h"
#include "SoundSystem.h"

constexpr auto MAX_CHANNEL = 5;

McCol::SoundSystem* McCol::SoundSystem::m_Instance = nullptr;

McCol::SoundSystem::SoundSystem()
	: m_System(nullptr)
	, m_Result()
	, m_Version(0)
{
}

void McCol::SoundSystem::Initialize()
{
	m_Result = FMOD::System_Create(&m_System);
	assert(m_Result == FMOD_OK);

	m_Result = m_System->getVersion(&m_Version);
	assert(m_Result == FMOD_OK);

	m_Result = m_System->init(MAX_CHANNEL, FMOD_INIT_NORMAL, nullptr);
	assert(m_Result == FMOD_OK);

	// BGM
	CreateSound("../Resource/Sound/BGM_01.wav", FMOD_LOOP_NORMAL, "BGM_01", "BGM");
	CreateSound("../Resource/Sound/BGM_02.wav", FMOD_LOOP_NORMAL, "BGM_02", "BGM");

	// FX
	CreateSound("../Resource/Sound/FX_Buff.wav", FMOD_LOOP_OFF, "FX_Buff", "FX");
	CreateSound("../Resource/Sound/FX_CC.wav", FMOD_LOOP_OFF, "FX_CC", "FX");
	CreateSound("../Resource/Sound/FX_Fail.wav", FMOD_LOOP_OFF, "FX_Fail", "FX"); // 카드 사용 불가 또는 코스트 부족
	CreateSound("../Resource/Sound/FX_Heal.wav", FMOD_LOOP_OFF, "FX_Heal", "FX");

	CreateSound("../Resource/Sound/Hit_Gun_01.wav", FMOD_LOOP_OFF, "Hit_Gun_01", "FX");
	CreateSound("../Resource/Sound/FX_Death.wav", FMOD_LOOP_OFF, "FX_Death", "FX");

	CreateSound("../Resource/Sound/FX_StartTurn.wav", FMOD_LOOP_OFF, "FX_StartTurn", "FX");

	// CARD
	CreateSound("../Resource/Sound/FX_Playuse.wav", FMOD_LOOP_OFF, "FX_Playuse", "CARD");
	CreateSound("../Resource/Sound/FX_Draw.wav", FMOD_LOOP_OFF, "FX_Draw", "CARD");
	CreateSound("../Resource/Sound/FX_Overload.wav", FMOD_LOOP_OFF, "FX_Overload", "CARD");
	CreateSound("../Resource/Sound/FX_Paradox.wav", FMOD_LOOP_OFF, "FX_Paradox", "CARD");

	// DEF
	CreateSound("../Resource/Sound/FX_Shield.wav", FMOD_LOOP_OFF, "FX_Shield", "DEF");

	// HIT
	CreateSound("../Resource/Sound/Hit_Blunt.wav", FMOD_LOOP_OFF, "Hit_Blunt", "HIT");
	CreateSound("../Resource/Sound/Hit_Slash.wav", FMOD_LOOP_OFF, "Hit_Slash", "HIT");
	
	// Interaction Sound
	CreateSound("../Resource/Sound/Interaction_AfterClick.wav", FMOD_LOOP_OFF, "Interaction_AfterClick", "MOUSE");
	CreateSound("../Resource/Sound/Interaction_CardSelection.wav", FMOD_LOOP_OFF, "Interaction_CardSelection", "MOUSE");
	CreateSound("../Resource/Sound/Interaction_GainCard.wav", FMOD_LOOP_OFF, "Interaction_GainCard", "MOUSE");
	CreateSound("../Resource/Sound/Interaction_MapPoint.wav", FMOD_LOOP_OFF, "Interaction_MapPoint", "MOUSE");
	CreateSound("../Resource/Sound/Interaction_Mouse.wav", FMOD_LOOP_OFF, "Interaction_Mouse", "MOUSE");
	CreateSound("../Resource/Sound/Interaction_Mouse_2.wav", FMOD_LOOP_OFF, "Interaction_Mouse_2", "MOUSE");
	CreateSound("../Resource/Sound/Interaction_OpenDeck.wav", FMOD_LOOP_OFF, "Interaction_OpenDeck", "MOUSE");
	CreateSound("../Resource/Sound/Interaction_OpenMap.wav", FMOD_LOOP_OFF, "Interaction_OpenMap", "MOUSE");
}

void McCol::SoundSystem::Update()
{
	m_Result = m_System->update();
	assert(m_Result == FMOD_OK);
}

void McCol::SoundSystem::Finalize()
{
	for (auto& [name, sound] : m_Sounds)
	{
		sound->release();
		sound = nullptr;
	}

	for (auto& [name, channel] : m_Channels)
	{
		channel = nullptr;
	}

	m_System->release();
	m_System = nullptr;

	SAFE_DELETE(m_Instance)
}

void McCol::SoundSystem::CreateSound(const std::string& filePath, FMOD_MODE mode, std::string_view soundName,
	std::string_view channelName)
{
	if (m_RelatedChannel.find(soundName) != m_RelatedChannel.end())
		return;

	m_Result = m_System->createSound(filePath.c_str(), mode, 0, &m_Sounds[soundName]);
	assert(m_Result == FMOD_OK);

	m_RelatedChannel.insert({ soundName, channelName });
}

void McCol::SoundSystem::DeleteSound(std::string_view soundName)
{
	const auto foundedSound = m_Sounds.find(soundName);
	const auto foundedChannel = m_RelatedChannel.find(soundName);

	if (foundedSound == m_Sounds.end() or foundedChannel == m_RelatedChannel.end())
		return;

	foundedSound->second->release();
	foundedSound->second = nullptr;

	m_Sounds.erase(foundedSound);
	m_RelatedChannel.erase(foundedChannel);
}

void McCol::SoundSystem::PlaySoundM(std::string_view soundName)
{
	if (m_RelatedChannel.find(soundName) == m_RelatedChannel.end())
		return;

	bool isPlaying;
	m_Channels[m_RelatedChannel[soundName]]->isPlaying(&isPlaying);

	if (isPlaying)
		return;

	FMOD::Sound* sound = m_Sounds[soundName];
	m_System->playSound(sound, 0, false, &m_Channels[m_RelatedChannel[soundName]]);
}

void McCol::SoundSystem::Play(std::string_view soundName)
{
	if (m_RelatedChannel.find(soundName) == m_RelatedChannel.end())
		return;

	bool isPaused = false;
	m_Channels[m_RelatedChannel[soundName]]->getPaused(&isPaused);

	if (!isPaused)
	{
		return;
	}

	m_Channels[m_RelatedChannel[soundName]]->setPaused(false);
}

void McCol::SoundSystem::Pause(std::string_view soundName)
{
	if (m_RelatedChannel.find(soundName) == m_RelatedChannel.end())
		return;

	m_Channels[m_RelatedChannel[soundName]]->setPaused(true);
}

void McCol::SoundSystem::Stop(std::string_view soundName)
{
	if (m_RelatedChannel.find(soundName) == m_RelatedChannel.end())
		return;

	m_Channels[m_RelatedChannel[soundName]]->stop();
}

void McCol::SoundSystem::Replay(std::string_view soundName)
{
	if (m_RelatedChannel.find(soundName) == m_RelatedChannel.end())
		return;

	m_Channels[m_RelatedChannel[soundName]]->stop();

	FMOD::Sound* sound = m_Sounds[soundName];
	m_System->playSound(sound, 0, false, &m_Channels[m_RelatedChannel[soundName]]);
}

void McCol::SoundSystem::SetVolume(std::string_view channelName, float volume)
{
	if (volume < 0.0f || volume > 1.0f) {
		// 볼륨 범위가 잘못되었습니다.
		return;
	}

	auto it = m_Channels.find(channelName);
	if (it != m_Channels.end() && it->second != nullptr) {
		it->second->setVolume(volume);
	}
	else {
		// 채널이 존재하지 않거나 초기화되지 않았습니다.
		return;
	}
}
