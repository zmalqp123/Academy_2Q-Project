#include "pch.h"
#include "SoundManager.h"

bool SoundManager::LoadSound(const std::wstring& baseName, const std::wstring& filePath) {
    // 고유한 이름을 생성하여 동일한 사운드라도 여러 번 로드할 수 있도록 함
    static int soundCounter = 0;
    std::wstring uniqueName = baseName + std::to_wstring(soundCounter++);

    // 사운드 로드
    FMOD::Sound* sound = nullptr;
    FMOD_RESULT result = m_System->createSound(std::string(filePath.begin(), filePath.end()).c_str(), FMOD_DEFAULT, 0, &sound);
    if (result != FMOD_OK) {
        return false; // 사운드 로드 실패
    }

    m_SoundMap[uniqueName] = sound;
    return true;
}

void SoundManager::PlaySoundW(const std::wstring& baseName, bool loop) {
    // baseName으로 시작하는 사운드를 찾음
    for (const auto& pair : m_SoundMap) {
        const std::wstring& name = pair.first;
        FMOD::Sound* sound = pair.second;

        // baseName으로 시작하는 사운드를 찾기
        if (name.find(baseName) == 0) {
            FMOD::Channel* channel = nullptr;
            m_System->playSound(sound, nullptr, false, &channel);
            if (loop) {
                channel->setMode(FMOD_LOOP_NORMAL);
            }
            m_ChannelMap[name] = channel;

            // 같은 baseName에 대한 첫 번째 일치 항목만 재생하도록 종료
            break;
        }
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
