#pragma once

// FMOD 헤더 파일 포함
#pragma comment (lib, "fmod_vc.lib")
#include "fmod.hpp"
#include <map>
#include <string>

class SoundManager
{
private:
    FMOD::System* m_System = nullptr;

    std::map<std::wstring, FMOD::Sound*> m_SoundMap;   // 사운드 이름과 FMOD::Sound 객체를 매핑하는 맵
    std::map<std::wstring, FMOD::Channel*> m_ChannelMap; // 사운드 이름과 FMOD::Channel 객체를 매핑하는 맵

    SoundManager() {
        // FMOD 시스템 객체 생성
        FMOD::System_Create(&m_System);
        m_System->init(512, FMOD_INIT_NORMAL, nullptr);
    }

    ~SoundManager() {
        for (auto& sound : m_SoundMap) {
            sound.second->release();
        }
        m_System->close();
        m_System->release();
    }

public:
    static SoundManager& GetInstance() {
        static SoundManager instance;
        return instance;
    }
    
    bool LoadSound(const std::wstring& name, const std::wstring& filePath);
    void PlaySoundW(const std::wstring& name, bool loop = false);
    void StopSound(const std::wstring& name);
    void SetVolume(const std::wstring& name, float volume);
    void Update();
    void ReleaseSound(const std::wstring& name);
};

