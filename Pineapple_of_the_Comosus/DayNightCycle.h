#pragma once
#include "../D2DEngine/Component.h"
#include <iostream>
class Scene;
class GameObject;
class SpriteRenderer;
class DayNightCycle : public Component {
private:
    bool isNight;          // 밤/낮 상태를 나타내는 변수
    bool isMorningBgmLoaded = false;   // 아침 사운드가 로드되었는지 추적
    bool isNightBgmLoaded = false;  // 밤 사운드가 로드되었는지 추적
    std::wstring currentPlayingBgm = L""; // 현재 재생 중인 BGM을 추적

    float elapsedTime = 0.f;
    int prevPeriod = 0;
public:
    float sunLocation[4] = {750.0f,400.0f,50.f,-300.f};
    float moonLocation[4] = { 750.0f,400.0f,-750.f,-750.0f };
    //WaveSystem* waveSystem; // 웨이브 시스템에 대한 포인터
    Scene* scene;
    GameObject* m_Sun;
    GameObject* m_Moon;
    DayNightCycle() {};
    //DayNightCycle(WaveSystem* waveSystem);
    //backGround
    
    GameObject* cloudDay;
    GameObject* cloudNight;

    GameObject* backGroundDay;
    GameObject* backGroundNight;
    
    GameObject* Earth;
    
    GameObject* Mountain1Day;
    GameObject* Mountain2Day;
    GameObject* Mountain3Day;

    GameObject* Mountain1Night;
    GameObject* Mountain2Night;
    GameObject* Mountain3Night;



    void Update(float deltaTime) override; // Update 함수 오버라이드
    bool IsNight() const; // 현재 밤인지 낮인지 여부를 반환
    void ApplyNightEffects(int wave); // 밤이 되었을 때 적용할 효과
    void RemoveNightEffects(int wave); // 낮이 되었을 때 제거할 효과

    void SunMove(float deltaTime,int period);

    void SunReset();

    void MoonMove(float deltaTime, int period);

    void MoonReset();
    
    void SwitchBackGround(float deltaTime, int period);

};
