#include "EnemyFactory.h"
#include "BulletFactory.h"
#include "SwordManAttack.h"
#include "MusKetAttack.h"
#include "BomberAttack.h"
#include "GriffinAttack.h"
#include "HeavyAttack.h"
#include "EnemyMove.h"
#include "EnemyDead.h"
#include "MusKetShooter.h"
#include "DataManager.h"

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
        auto enemy = CreateRandomEnemy(); // ���� �� ����
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
    collider->SetCollisionType(CollisionType::Overlap);
    auto colliderPhysics = mon->CreateComponent<BoxCollider>();
    colliderPhysics->SetExtent({ 1.f, 1.f });
    mon->SetActive(true);
    // auto fsm  =  mon->CreateComponent<FiniteStateMachine>(); // 추가로 FSMstate 넣어야함.
    // fsm->SetOwner(mon);
    Enemy* enemy = nullptr;
    DataManager& d = DataManager::GetInstance();
    switch (type)
    {
    case 0:
        enemy = mon->CreateComponent<SwordMan>();
        enemy->enemyData = *(d.GetEnemyData((int)EnemyID::swordMan));
        loadMon->LoadTexture(L"../Resource/swordsman.png");
        /*fsm->CreateState<SwordManAttack>("Attack");
        fsm->CreateState<EnemyMove>("Move");
        fsm->CreateState<EnemyDead>("Dead");
        fsm->SetState("Move");*/
        break;
    case 1:
        enemy = mon->CreateComponent<BombCart>();
        enemy->enemyData = *(d.GetEnemyData((int)EnemyID::bombCarrier));
        loadMon->LoadTexture(L"../Resource/tile.png");
        /*fsm->CreateState<BomberAttack>("Attack");
        fsm->CreateState<EnemyMove>("Move");
        fsm->CreateState<EnemyDead>("Dead");
        fsm->SetState("Move");*/
        break;
    case 2:
        enemy = mon->CreateComponent<Griffin>();
        enemy->enemyData = *(d.GetEnemyData((int)EnemyID::griffin));
        loadMon->LoadTexture(L"../Resource/griffin.png");
        /*fsm->CreateState<GriffinAttack>("Attack");
        fsm->CreateState<EnemyMove>("Move");
        fsm->CreateState<EnemyDead>("Dead");
        fsm->SetState("Move");*/
        break;
    case 3:
        enemy = mon->CreateComponent<HeavyKnight>();
        enemy->enemyData = *(d.GetEnemyData((int)EnemyID::heavyArmor));
        loadMon->LoadTexture(L"../Resource/HeavyKnight.png");
        /*fsm->CreateState<HeavyAttack>("Attack");
        fsm->CreateState<EnemyMove>("Move");
        fsm->CreateState<EnemyDead>("Dead");
        fsm->SetState("Move");*/
        break;
    case 4:
        enemy = mon->CreateComponent<MusKetShooter>();
        enemy->enemyData = *(d.GetEnemyData((int)EnemyID::musketeer));
        //b->bulletFactory = bulletFactory;
        //enemy = b;
        loadMon->LoadTexture(L"../Resource/MusKetShooter.png");
        /*fsm->CreateState<MusKetAttack>("Attack");
        fsm->CreateState<EnemyMove>("Move");
        fsm->CreateState<EnemyDead>("Dead");
        fsm->SetState("Move");*/
        break;
    default:
        // �⺻ �� �Ǵ� ���� ó��
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
    std::uniform_real_distribution<float> floatDist(0.0f, 1.0f); // 0.0 ~ 1.0 ������ �Ǽ� ����

    float randomValue = floatDist(gen); // 0.0 ~ 1.0 ������ ���� �� ����
    

    if (randomValue < 0.2f)
        enemyType = 0; // 20% Ȯ���� 0
    else if (randomValue < 0.4f)
        enemyType = 1; // 20% Ȯ���� 1
    else if (randomValue < 0.6f)
        enemyType = 2; // 20% Ȯ���� 2
    else if (randomValue < 0.8f)
        enemyType = 3; // 20% Ȯ���� 3
    else
        enemyType = 4; // 20% Ȯ���� 4

    return CreateEnemy(enemyType); // 0-4 ������ �� ����
}

Enemy* EnemyFactory::GetEnemyFromPool()
{
    if (m_EnemyPool.empty())
    {
        auto enemy = CreateRandomEnemy(); // Ǯ�� ���� ������ ���� �� ����
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
