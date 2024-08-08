#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/Vector.h"
#include "../D2DEngine/Movement.h"
#include <vector>

class Scene;
class Enemy;
class SwordMan;
class WaveSystem : public Component
{
private:
    float waveTimer = 1.0f;   // Wave 타이머
    int currentWave = 1;       // 현재 진행 중인 wave
    static const int maxWave = 56; // 최대 wave 수

    std::vector<SwordMan*> m_MonsterPool;
    std::vector<SwordMan*> m_Monster;

    // 몬스터 풀의 초기 크기
    static const int initialPoolSize = 10;

    // 풀에서 몬스터를 가져오는 메서드
    SwordMan* GetMonsterFromPool();
    // 풀에 몬스터를 반환하는 메서드
    void ReturnMonsterToPool(SwordMan* monster);
    void InitializePool();         // 풀 초기화
public:
    Vector2 rightPos; 
    Vector2 leftPos;

    Scene* scene;

    int getCurrentWave() { return currentWave; }
    virtual void Update(float deltaTime); // 매 프레임 호출, wave 타이머 업데이트
    void SpawnWave();              // 새로운 wave 스폰
    bool IsMapEmpty();             // 맵에 몬스터가 하나도 없는지 확인 (추후 필요할 경우 사용)
    virtual ~WaveSystem(); // 소멸자 선언
private:
    void StartNextWave();          // 다음 wave로 넘어가기

};

