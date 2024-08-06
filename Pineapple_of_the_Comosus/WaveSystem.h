#pragma once
#include"../D2DEngine/Component.h"
#include <vector>

class Monster;

class WaveSystem : public Component
{
private:
    float waveTimer = 1.0f;   // Wave 타이머
    int currentWave = 1;       // 현재 진행 중인 wave
    static const int maxWave = 56; // 최대 wave 수

public:
    virtual void Update(float deltaTime); // 매 프레임 호출, wave 타이머 업데이트
    void SpawnWave();              // 새로운 wave 스폰
    bool IsMapEmpty();             // 맵에 몬스터가 하나도 없는지 확인 (추후 필요할 경우 사용)

private:
    void StartNextWave();          // 다음 wave로 넘어가기
};

