#include "Enemy.h"
#include "SwordMan.h"
#include "WaveSystem.h"
#include "../D2DEngine/Scene.h"
#include"../D2DEngine/SpriteRenderer.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/BoxCollider.h"

#include <iostream> 
#include <cstdlib>  // rand() 함수 사용을 위해 포함
#include <ctime>    // 시간 기반 시드 설정
#include <random>   // 랜덤 분포를 사용하기 위해 포함

void WaveSystem::InitializePool()
{
    std::srand(static_cast<unsigned>(std::time(nullptr))); // 랜덤 시드 설정

    for (int i = 0; i < initialPoolSize; ++i)
    {
        auto  mon = scene->CreateGameObject<GameObject>();
        auto loadMon = mon->CreateComponent<SpriteRenderer>();
        loadMon->LoadTexture(L"../Resource/swordsman.png");
        mon->isActive = false;
        auto monster = mon->CreateComponent<SwordMan>();
        m_MonsterPool.push_back(monster);
    }
}

SwordMan* WaveSystem::GetMonsterFromPool()
{
    if (m_MonsterPool.empty())
    {
        // 풀에 몬스터가 없으면 새로 생성
        auto  mon = scene->CreateGameObject<GameObject>();
        auto loadMon = mon->CreateComponent<SpriteRenderer>();
        auto movement = mon->CreateComponent<Movement>();
        auto collider = mon->CreateComponent<BoxCollider>();
        loadMon->LoadTexture(L"../Resource/swordsman.png");
        auto monster = mon->CreateComponent<SwordMan>();
        monster->move = movement;
        monster->pBoxcollider = collider;

        m_MonsterPool.push_back(monster);
    }

    SwordMan* monster = m_MonsterPool.back();
    monster->gameObject->isActive = true;
    m_MonsterPool.pop_back();
    return monster;
}

void WaveSystem::ReturnMonsterToPool(SwordMan* monster)
{
    m_MonsterPool.push_back(monster);
    monster->gameObject->isActive = false;
}

void WaveSystem::Update(float deltaTime)
{
    // 몬스터가 맵에 남아있는지 확인하는 부분은 RemoveMonster가 아닌 다른 시스템에서 처리
    waveTimer -= deltaTime;  // deltaTime 만큼 waveTimer 감소

    if (waveTimer <= 0.0f && !m_Monster.empty())
    {
        auto monster = m_Monster.front();
        monster->gameObject->isActive = true;
        m_Monster.erase(m_Monster.begin());  // 이미 그려진 몬스터는 목록에서 제거

        waveTimer = 1.0f / currentWave;  // 다음 몬스터가 나타나기까지의 시간 설정
    }

    if (m_Monster.empty() && currentWave > 0)
    {
        StartNextWave();  // 모든 몬스터가 등장한 후 다음 웨이브로 넘어감
    }
}

// SpawnWave 함수: 현재 wave에 해당하는 몬스터를 스폰.  
void WaveSystem::SpawnWave()
{
    int numMonstersToSpawn = 1; // 일단은 웨이브 1개씩 설정

    m_Monster.clear();  // 이전 웨이브에서 생성된 몬스터를 삭제 (필요한 경우)

    // 랜덤 엔진 및 분포 설정
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distY(-240.0f, 0.0f); // y좌표의 범위를 설정

    for (int i = 0; i < numMonstersToSpawn; ++i)
    {
        // 풀에서 몬스터를 가져옵니다.
        SwordMan* newMonster = GetMonsterFromPool();

        // 랜덤하게 왼쪽 또는 오른쪽에서 생성
        bool spawnOnLeft = rand() % 2 == 0;

        // 고정된 x 좌표와 랜덤한 y 좌표를 사용하여 위치 설정
        float spawnY = distY(gen);

        Vector2 spawnPosition;
        Vector2 moveDirection;  // 이동 방향을 저장할 변수

        if (spawnOnLeft)
        {
            spawnPosition = Vector2(-800.0f, spawnY);
            moveDirection = Vector2(1.0f, 0.0f);  // 오른쪽으로 이동
        }
        else
        {
            spawnPosition = Vector2(900.0f, spawnY);
            moveDirection = Vector2(-1.0f, 0.0f);  // 왼쪽으로 이동
            newMonster->gameObject->GetComponent<SpriteRenderer>()->SetFilp(true, false);
        }

        newMonster->gameObject->transform->pos.worldPosition = spawnPosition;

        // 이동 방향과 속도를 설정합니다.
        //std::cout << moveDirection.x <<std::endl ;
        newMonster->move->SetDirection(moveDirection);
        newMonster->move->SetSpeed(50.0f);  // 원하는 이동 속도로 설정
        newMonster->tmpY = spawnPosition.y;

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
        waveTimer = 3.0f;  // 타이머 초기화
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
    m_Monster.clear();

    m_MonsterPool.clear();
}