#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/Vector.h"
#include "../D2DEngine/Movement.h"
#include "DayNightCycle.h"
#include "DataManager.h"
#include <vector>

class Scene;
class Enemy;
class EnemyFactory;
class BulletFactory;
class MainPineApple;

class WaveSystem : public Component
{
private:
    const float maxWaveTimer = 15.f;
    float waveTimer = 3.f;   // Wave 타이머
    int currentWave = 0;       // 현재 진행 중인 wave
    static const int maxWave = 56; // 최대 wave 수

    std::vector<WaveEnemyData> leftEnemyDatas;
    std::vector<WaveEnemyData> rightEnemyDatas;
    
public:
    EnemyFactory* enemyFactory;  
    BulletFactory* bulletFactory;
    MainPineApple* mainPineApple;
    DayNightCycle* dayNightCycle;
    Vector2 rightPos; 
    Vector2 leftPos;

    GameObject* tutorial;
	


    Scene* scene = nullptr;
    // 풀에서 몬스터를 가져오는 메서드
    //Enemy* GetEnemyFromPool(); // SwordMan -> Enemy로 변경
    //void ReturnEnemyToPool(Enemy* enemy); // SwordMan -> Enemy로 변경
    //void InitializePool();         // 풀 초기화
    int getCurrentWave() { return currentWave; }
    virtual void Init();
    virtual void Update(float deltaTime); // 매 프레임 호출, wave 타이머 업데이트
    //void SpawnWave();              // 새로운 wave 스폰

    void LoadWaveData();
    void Generator();
	void pullingTutorial(float deltaTime);

    bool IsFly(int id);

    //bool IsMapEmpty();             // 맵에 몬스터가 하나도 없는지 확인 (추후 필요할 경우 사용)

    WaveSystem();
    virtual ~WaveSystem(); // 소멸자 선언
private:
    void StartNextWave();          // 다음 wave로 넘어가기

};

