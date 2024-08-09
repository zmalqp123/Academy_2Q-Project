#include "EnemyFactory.h"
#include "SwordManAttack.h"
#include "MusKetAttack.h"
#include "BomberAttack.h"
#include "GriffinAttack.h"
#include "HeavyAttack.h"
#include "../D2DEngine/Scene.h"
#include "../D2DEngine/SpriteRenderer.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/FiniteStateMachine.h"

EnemyFactory::EnemyFactory(Scene* scene)
    : scene(scene)
{
    //InitializePool();
}

EnemyFactory::~EnemyFactory()
{
    m_EnemyPool.clear();
}

void EnemyFactory::InitializePool()
{
    for (int i = 0; i < initialPoolSize; ++i)
    {
        auto enemy = CreateRandomEnemy(); // 랜덤 적 생성
        enemy->gameObject->isActive = false;
        m_EnemyPool.push_back(enemy);
    }
}

Enemy* EnemyFactory::CreateEnemy(int type)
{
    auto mon = scene->CreateGameObject<GameObject>();
    auto loadMon = mon->CreateComponent<SpriteRenderer>();
    auto movement = mon->CreateComponent<Movement>();
    auto collider = mon->CreateComponent<BoxCollider>();
    auto fsm  =  mon->CreateComponent<FiniteStateMachine>(); // 추가로 FSM state 넣을 것
    Enemy* enemy = nullptr;

    switch (type)
    {
    case 0:
        enemy = mon->CreateComponent<SwordMan>();
        enemy->Init();
        loadMon->LoadTexture(L"../Resource/swordsman.png");
        fsm->CreateState<SwordManAttack>("Attack");
        break;
    case 1:
        enemy = mon->CreateComponent<BombCart>();
        loadMon->LoadTexture(L"../Resource/tile.png");
        fsm->CreateState<BomberAttack>("Attack");
        break;
    case 2:
        enemy = mon->CreateComponent<Griffin>();
        loadMon->LoadTexture(L"../Resource/Sun.png");
        fsm->CreateState<GriffinAttack>("Attack");
        break;
    case 3:
        enemy = mon->CreateComponent<HeavyKnight>();
        loadMon->LoadTexture(L"../Resource/moon.png");
        fsm->CreateState<HeavyAttack>("Attack");
        break;
    case 4:
        enemy = mon->CreateComponent<MusKetShooter>();
        loadMon->LoadTexture(L"../Resource/MusKetShooter.png");
        fsm->CreateState<MusKetAttack>("Attack");
        break;
    default:
        // 기본 적 또는 오류 처리
        return nullptr;
    }

    enemy->move = movement;
    enemy->pBoxcollider = collider;
    return enemy;
}

Enemy* EnemyFactory::CreateRandomEnemy()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> floatDist(0.0f, 1.0f); // 0.0 ~ 1.0 범위의 실수 생성

    float randomValue = floatDist(gen); // 0.0 ~ 1.0 사이의 랜덤 값 생성
    int enemyType;

    if (randomValue < 0.2f)
        enemyType = 0; // 20% 확률로 0
    else if (randomValue < 0.4f)
        enemyType = 1; // 20% 확률로 1
    else if (randomValue < 0.6f)
        enemyType = 2; // 20% 확률로 2
    else if (randomValue < 0.8f)
        enemyType = 3; // 20% 확률로 3
    else
        enemyType = 4; // 20% 확률로 4

    return CreateEnemy(enemyType); // 0-4 범위의 적 생성
}

Enemy* EnemyFactory::GetEnemyFromPool()
{
    if (m_EnemyPool.empty())
    {
        auto enemy = CreateRandomEnemy(); // 풀에 적이 없으면 랜덤 적 생성
        m_EnemyPool.push_back(enemy);
    }

    Enemy* enemy = m_EnemyPool.back();
    enemy->gameObject->isActive = true;
    m_EnemyPool.pop_back();
    return enemy;
}

void EnemyFactory::ReturnEnemyToPool(Enemy* enemy)
{
    m_EnemyPool.push_back(enemy);
    enemy->gameObject->isActive = false;
}
