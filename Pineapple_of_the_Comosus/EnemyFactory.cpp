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
#include "MainPineApple.h"
#include "EnemyColliderNotify.h"

#include "../D2DEngine/Scene.h"
#include "../D2DEngine/SpriteRenderer.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/Transform.h"
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
    collider->SetExtent({ 1.f, 1.f });

    auto child = scene->CreateGameObject<GameObject>();
    auto monBar = child->CreateComponent<SpriteRenderer>();
    child->transform->SetSortingLayer(-1);
    child->transform->SetParent(mon->transform);
    auto notify = child->CreateComponent<EnemyColliderNotify>();
    auto notifyColl = child->CreateComponent<BoxCollider>();
    notifyColl->SetCollisionType(CollisionType::Overlap);

    //auto colliderPhysics = mon->CreateComponent<BoxCollider>();
    //colliderPhysics->SetExtent({ 1.f, 1.f });
    mon->SetActive(false);
    auto fsm  =  mon->CreateComponent<FiniteStateMachine>(); // 추가로 FSMstate 넣어야함.
    fsm->SetOwner(mon);
    Enemy* enemy = nullptr;
    DataManager& d = DataManager::GetInstance();
    switch (type)
    {
    case (int)EnemyID::swordMan:
    case (int)EnemyID::swordMan + 1:
    case (int)EnemyID::swordMan + 2:
    case (int)EnemyID::swordMan + 3:
        enemy = mon->CreateComponent<SwordMan>();
        enemy->enemyData = *(d.GetEnemyData((int)EnemyID::swordMan)); //복사가 되야하는 부분!
		enemy->AttackSprite = mon->CreateComponent<SpriteRenderer>();
        monBar->LoadTexture(L"../Resource/30631.png");
        monBar->SetCenter(Vector2(0.5f, 0.f));
        loadMon->LoadTexture(L"../Resource/swordsman.png");
		enemy->AttackSprite->LoadTexture(L"../Resource/30701.png");
        fsm->CreateState<SwordManAttack>("Attack");
        fsm->CreateState<EnemyMove>("Move");
        fsm->CreateState<EnemyDead>("Dead");
        fsm->SetState("Move");
        
        break;
    case (int)EnemyID::bombCarrier:
    case (int)EnemyID::bombCarrier + 1:
    case (int)EnemyID::bombCarrier + 2:
    case (int)EnemyID::bombCarrier + 3:
        enemy = mon->CreateComponent<BombCart>();
        enemy->enemyData = *(d.GetEnemyData((int)EnemyID::bombCarrier)); //복사가 되야하는 부분!
        monBar->LoadTexture(L"../Resource/30631.png");
        loadMon->LoadTexture(L"../Resource/tile.png");
        monBar->SetCenter(Vector2(0.5f, 0.f));
        fsm->CreateState<BomberAttack>("Attack");
        fsm->CreateState<EnemyMove>("Move");
        fsm->CreateState<EnemyDead>("Dead");
        fsm->SetState("Move");
        break;
    case (int)EnemyID::griffin:
    case (int)EnemyID::griffin + 1:
    case (int)EnemyID::griffin + 2:
    case (int)EnemyID::griffin + 3:
        enemy = mon->CreateComponent<Griffin>();
        enemy->enemyData = *(d.GetEnemyData((int)EnemyID::griffin)); //복사가 되야하는 부분!
        monBar->LoadTexture(L"../Resource/30632.png");
        loadMon->LoadTexture(L"../Resource/griffin.png");
        monBar->SetCenter(Vector2(0.5f, 1.f));
        fsm->CreateState<GriffinAttack>("Attack");
        fsm->CreateState<EnemyMove>("Move");
        fsm->CreateState<EnemyDead>("Dead");
        fsm->SetState("Move");
        break;
    case (int)EnemyID::heavyArmor:
    case (int)EnemyID::heavyArmor + 1:
    case (int)EnemyID::heavyArmor + 2:
    case (int)EnemyID::heavyArmor + 3:
        enemy = mon->CreateComponent<HeavyKnight>();
        enemy->enemyData = *(d.GetEnemyData((int)EnemyID::heavyArmor)); //복사가 되야하는 부분!
        monBar->LoadTexture(L"../Resource/30631.png");
        loadMon->LoadTexture(L"../Resource/HeavyKnight.png");
        monBar->SetCenter(Vector2(0.5f, 0.f));
        fsm->CreateState<HeavyAttack>("Attack");
        fsm->CreateState<EnemyMove>("Move");
        fsm->CreateState<EnemyDead>("Dead");
        fsm->SetState("Move");
        break;
    case (int)EnemyID::musketeer:
    case (int)EnemyID::musketeer + 1:
    case (int)EnemyID::musketeer + 2:
    case (int)EnemyID::musketeer + 3:
        enemy = mon->CreateComponent<MusKetShooter>();
        enemy->enemyData = *(d.GetEnemyData((int)EnemyID::musketeer)); //복사가 되야하는 부분!
        monBar->LoadTexture(L"../Resource/30631.png");
        monBar->SetCenter(Vector2(0.5f, 0.f));
        //b->bulletFactory = bulletFactory;
        //enemy = b;
        loadMon->LoadTexture(L"../Resource/MusKetShooter.png");
        fsm->CreateState<MusKetAttack>("Attack");
        fsm->CreateState<EnemyMove>("Move");
        fsm->CreateState<EnemyDead>("Dead");
        fsm->SetState("Move");
        break;
    default:
        // �⺻ �� �Ǵ� ���� ó��
        return nullptr;
    }
    enemy->mainPineApple = mainPineApple;
    enemy->move = movement;
    notify->enemy = enemy;
    enemy->notify = child;
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

Enemy* EnemyFactory::GetEnemyFromPool(int type)
{
    if (m_EnemyPool.empty())
    {
        auto enemy = CreateEnemy(type);//CreateRandomEnemy(); // Ǯ�� ���� ������ ���� �� ����
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
