#include "Enemy.h"
#include "WaveSystem.h"
#include "../D2DEngine/Scene.h"
#include "../D2DEngine/SpriteRenderer.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/BoxCollider.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include "EnemyFactory.h"

WaveSystem::WaveSystem()
{
    
}

WaveSystem::~WaveSystem()
{
    delete enemyFactory; // EnemyFactory 객체 삭제
    m_Enemies.clear();
}

void WaveSystem::SpawnWave()
{
    int numEnemiesToSpawn = 1; // 일단은 웨이브 1개씩 설정

    m_Enemies.clear();  // 이전 웨이브에서 생성된 적을 삭제 (필요한 경우)

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distY(-240.0f, -100.f);
    std::bernoulli_distribution distSide(0.5); // 50% 확률로 true 또는 false 생성

    for (int i = 0; i < numEnemiesToSpawn; ++i)
    {
        Enemy* newEnemy = enemyFactory->GetEnemyFromPool();

        bool spawnOnLeft = distSide(gen); // 50% 확률로 왼쪽 또는 오른쪽에서 스폰

        float spawnY = distY(gen);

        Vector2 spawnPosition;
        Vector2 moveDirection;

        if (spawnOnLeft)
        {
            spawnPosition = Vector2(-800.0f, spawnY);
            moveDirection = Vector2(1.0f, 0.0f);
        }
        else
        {
            spawnPosition = Vector2(900.0f, spawnY);
            moveDirection = Vector2(-1.0f, 0.0f);
            newEnemy->gameObject->GetComponent<SpriteRenderer>()->SetFilp(true, false);
        }

        newEnemy->gameObject->transform->pos.worldPosition = spawnPosition;
        newEnemy->move->SetDirection(moveDirection);
        newEnemy->move->SetSpeed(50.0f);
        newEnemy->tmpY = spawnPosition.y;

        m_Enemies.push_back(newEnemy);
        std::cout << "적이 생성되었습니다" << std::endl;
    }
}

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

bool WaveSystem::IsMapEmpty()
{
    return m_Enemies.empty();  // 기본적으로 false 반환
}

void WaveSystem::Init()
{
    enemyFactory = new EnemyFactory(scene); // EnemyFactory 생성
}

void WaveSystem::Update(float deltaTime)
{
    // 웨이브 타이머 감소
    waveTimer -= deltaTime;

    // 웨이브 타이머가 0 이하가 되었고, 적이 남아 있으면
    if (waveTimer <= 0.0f && !m_Enemies.empty())
    {
        // 적을 활성화하고 적 목록에서 제거
        auto enemy = m_Enemies.front();
        enemy->gameObject->isActive = true;
        m_Enemies.erase(m_Enemies.begin());

        // 웨이브 타이머를 다음 웨이브에 맞게 설정
        waveTimer = 1.0f / currentWave;
    }

    // 웨이브가 끝난 후 다음 웨이브 시작
    if (m_Enemies.empty() && currentWave > 0)
    {
        StartNextWave();
    }
}
