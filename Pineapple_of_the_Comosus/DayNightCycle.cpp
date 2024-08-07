#include "DayNightCycle.h"
#include "../D2DEngine/Scene.h"
#include"../D2DEngine/SpriteRenderer.h"
#include "iostream"

DayNightCycle::DayNightCycle(WaveSystem* waveSystem)
    : isNight(false), waveSystem(waveSystem) {}

void DayNightCycle::Update(float deltaTime) {
    int curWave = waveSystem->getCurrentWave();

    std::cout << curWave;
    // 4의 배수 웨이브에서 밤이 된다.
    if (curWave % 4 == 0 && curWave != 0) {
        if (!isNight) {
            isNight = true;
            ApplyNightEffects();
        }
    }
    else {
        if (isNight) {
            isNight = false;
            RemoveNightEffects();
        }
    }
}

bool DayNightCycle::IsNight() const {
    return isNight;
}

void DayNightCycle::ApplyNightEffects() {
    // 추가하기
    /*waveSystem->IncreaseEnemyAttackPower(0.25f);
    waveSystem->SetHarvestExperience(0.0f);*/
    std::cout << "밤" << std::endl;
}

void DayNightCycle::RemoveNightEffects() {
    // 추가하기
    //waveSystem->IncreaseEnemyAttackPower(-0.25f);
    //waveSystem->SetHarvestExperience(1.0f); // 기본 수확 경험치를 원래대로 되돌리기
}
