#pragma once

// FMOD 헤더 파일 포함
#pragma comment(lib, "fmod_vc.lib")
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
        // 사운드 객체 해제
        for (auto& sound : m_SoundMap) {
            sound.second->release();
        }
        // FMOD 시스템 해제
        m_System->close();
        m_System->release();
    }

public:
    // 싱글톤 인스턴스 가져오기
    static SoundManager& GetInstance() {
        static SoundManager instance;
        return instance;
    }

    // 복사 및 이동 금지
    SoundManager(const SoundManager&) = delete;
    SoundManager& operator=(const SoundManager&) = delete;
    SoundManager(SoundManager&&) = delete;
    SoundManager& operator=(SoundManager&&) = delete;

    // 사운드 로드
    bool LoadSound(const std::wstring& baseName, const std::wstring& filePath);

    // 사운드 재생
    void PlaySoundW(const std::wstring& baseName, bool loop = false);

    // 사운드 정지
    void StopSound(const std::wstring& name);

    // 볼륨 설정
    void SetVolume(const std::wstring& name, float volume);

    // 시스템 업데이트
    void Update();

    // 사운드 해제
    void ReleaseSound(const std::wstring& name);
};
