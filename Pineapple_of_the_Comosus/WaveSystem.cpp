#include"testChar.h"
#include "WaveSystem.h"
#include "../D2DEngine/Scene.h"
#include"../D2DEngine/SpriteRenderer.h"
#include "../D2DEngine/Transform.h"

#include <iostream> 
#include <cstdlib>  // rand() 함수 사용을 위해 포함
#include <ctime>    // 시간 기반 시드 설정

void WaveSystem::InitializePool()
{
    std::srand(static_cast<unsigned>(std::time(nullptr))); // 랜덤 시드 설정

    for (int i = 0; i < initialPoolSize; ++i)
    {
        auto  mon = scene->CreateGameObject<GameObject>();
        auto loadMon = mon->CreateComponent<SpriteRenderer>();
        loadMon->LoadTexture(L"../Resource/Sun.png");
        mon->isActive = false;
        auto monster = mon->CreateComponent<testChar>();
        m_MonsterPool.push_back(monster);
    }
}

testChar* WaveSystem::GetMonsterFromPool()
{
    if (m_MonsterPool.empty())
    {
        // 풀에 몬스터가 없으면 새로 생성
        auto  mon = scene->CreateGameObject<GameObject>();
        auto loadMon = mon->CreateComponent<SpriteRenderer>();
        loadMon->LoadTexture(L"../Resource/Sun.png");
        auto monster = mon->CreateComponent<testChar>();
        m_MonsterPool.push_back(monster);
    }

    testChar* monster = m_MonsterPool.back();
    monster->gameObject->isActive = true;
    m_MonsterPool.pop_back();
    return monster;
}

void WaveSystem::ReturnMonsterToPool(testChar* monster)
{
    m_MonsterPool.push_back(monster);
    monster->gameObject->isActive = false;
}

void WaveSystem::Update(float deltaTime)
{
    // 몬스터가 맵에 남아있는지 확인하는 부분은 RemoveMonster가 아닌 다른 시스템에서 처리
    waveTimer -= deltaTime;  // deltaTime 만큼 waveTimer 감소
    if (waveTimer <= 0.0f)
    {
        StartNextWave();
    }
}

// SpawnWave 함수: 현재 wave에 해당하는 몬스터를 스폰.  
void WaveSystem::SpawnWave()
{
    int numMonstersToSpawn = currentWave; // 현재 웨이브 번호에 따라 몬스터 수 결정

    m_Monster.clear();  // 이전 웨이브에서 생성된 몬스터를 삭제 (필요한 경우)

    for (int i = 0; i < numMonstersToSpawn; ++i)
    {
        // 풀에서 몬스터를 가져옵니다.
        testChar* newMonster = GetMonsterFromPool();

        // 랜덤하게 왼쪽 또는 오른쪽에서 생성
        bool spawnOnLeft = rand() % 2 == 0;
        Vector2 spawnPosition;
        if (spawnOnLeft)
        {
            spawnPosition = Vector2(-600.0f, -240.0f);
        }
        else
        {
            spawnPosition = Vector2(600.0f, -240.0f);
        }
        newMonster->gameObject->transform->pos.worldPosition = spawnPosition;


        m_Monster.push_back(newMonster);
        std::cout << "몬스터가 생성되었습니다" << std::endl;
    }
}
// StartNextWave 함수: wave를 진행시키고 타이머를 초기화
void WaveSystem::StartNextWave()
{
    if (currentWave < maxWave)
    {
        currentWave++;
        waveTimer = 1.0f;  // 타이머 초기화
        SpawnWave();        // 새로운 wave 스폰
    }
    // maxWave에 도달했을 경우 추가적인 처리 필요 (게임 종료 또는 루프 등)
}

// IsMapEmpty 함수: 맵에 몬스터가 하나도 없는지 확인
bool WaveSystem::IsMapEmpty()
{
    // 맵에서 몬스터가 남아있는지 확인하는 로직 (필요 시 사용)
    return m_Monster.empty();  // 기본적으로 false 반환
}

WaveSystem::~WaveSystem()
{
    /// 몬스터를 풀에 반환
    for (testChar* monster : m_Monster)
    {
        ReturnMonsterToPool(monster);
    }
    m_Monster.clear();

    // 풀에 있는 몬스터들을 삭제
    for (testChar* monster : m_MonsterPool)
    {
        delete monster;
    }
    m_MonsterPool.clear();
}