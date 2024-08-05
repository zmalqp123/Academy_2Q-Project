#include "pch.h"
#include "SoundManager.h"

bool SoundManager::LoadSound(const std::wstring& name, const std::wstring& filePath) {
    if (m_SoundMap.find(name) != m_SoundMap.end()) {
        return false; // 이미 로드된 사운드
    }

    FMOD::Sound* sound = nullptr;
    FMOD_RESULT result = m_System->createSound(std::string(filePath.begin(), filePath.end()).c_str(), FMOD_DEFAULT, 0, &sound);
    if (result != FMOD_OK) {
        return false; // 사운드 로드 실패
    }

    m_SoundMap[name] = sound;
    return true;
}

void SoundManager::PlaySound(const std::wstring& name, bool loop) {
    auto it = m_SoundMap.find(name);
    if (it != m_SoundMap.end()) {
        FMOD::Sound* sound = it->second;
        FMOD::Channel* channel = nullptr;
        m_System->playSound(sound, 0, false, &channel);
        if (loop) {
            channel->setMode(FMOD_LOOP_NORMAL);
        }
        m_ChannelMap[name] = channel;
    }
}

void SoundManager::StopSound(const std::wstring& name) {
    auto it = m_ChannelMap.find(name);
    if (it != m_ChannelMap.end()) {
        it->second->stop();
    }
}

void SoundManager::SetVolume(const std::wstring& name, float volume) {
    auto it = m_ChannelMap.find(name);
    if (it != m_ChannelMap.end()) {
        it->second->setVolume(volume);
    }
}

void SoundManager::Update() {
    m_System->update();
}

void SoundManager::ReleaseSound(const std::wstring& name) {
    auto it = m_SoundMap.find(name);
    if (it != m_SoundMap.end()) {
        it->second->release();
        m_SoundMap.erase(it);
    }
}
