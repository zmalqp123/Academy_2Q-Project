#pragma once
#include "../D2DEngine/Component.h"
#include "WaveSystem.h"

class Scene;
class DayNightCycle : public Component {
private:
    bool isNight;          // 밤/낮 상태를 나타내는 변수

public:
    WaveSystem* waveSystem; // 웨이브 시스템에 대한 포인터
    Scene* scene;
    DayNightCycle() {};
    DayNightCycle(WaveSystem* waveSystem);

    void Update(float deltaTime) override; // Update 함수 오버라이드
    bool IsNight() const; // 현재 밤인지 낮인지 여부를 반환
    void ApplyNightEffects(); // 밤이 되었을 때 적용할 효과
    void RemoveNightEffects(); // 낮이 되었을 때 제거할 효과
};
