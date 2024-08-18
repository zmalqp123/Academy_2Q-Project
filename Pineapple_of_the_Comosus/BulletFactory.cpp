#include "BulletFactory.h"
#include "../D2DEngine/SpriteRenderer.h"
#include "../D2DEngine/SpriteAnimation.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/SideMovement.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Transform.h"
#include "Bullet.h"


BulletFactory::BulletFactory(Scene* scene)
    : scene(scene)
{
    InitializePool();
}

BulletFactory::~BulletFactory()
{
    m_BulletPool.clear();
}

void BulletFactory::InitializePool()
{
    for (int i = 0; i < initialPoolSize; ++i)
    {
        auto bullet = CreateBullet();  // Bullet 생성
        bullet->gameObject->isActive = false;
        m_BulletPool.push_back(bullet);
    }
}

Bullet* BulletFactory::CreateBullet()
{
    auto bulletObj = scene->CreateGameObject<GameObject>();
    bulletObj->transform->SetSortingLayer(INT_MAX);
    bulletObj->SetActive(false);
    auto spriteRenderer = bulletObj->CreateComponent<SpriteAnimation>();
    auto movement = bulletObj->CreateComponent<SideMovement>();  // SideMovement 사용
    movement->freezeRotate = false;
    auto collider = bulletObj->CreateComponent<BoxCollider>();
    collider->ignoreEventSystem = true;
    collider->SetCollisionType(CollisionType::Overlap);

    spriteRenderer->LoadTexture(L"../Resource/arrow.png");  // 총알 텍스처 로드
 
    Bullet* bullet = bulletObj->CreateComponent<Bullet>();
    bullet->move = movement;
    bullet->pBoxcollider = collider;
    bullet->bulletFactory = this;

    return bullet;
}

Bullet* BulletFactory::GetBulletFromPool()
{
    if (m_BulletPool.empty())
    {
        auto bullet = CreateBullet();  // 풀에 총알이 없으면 새로 생성
        m_BulletPool.push_back(bullet);
    }

    Bullet* bullet = m_BulletPool.back();
    bullet->gameObject->isActive = true;
    bullet->gameObject->transform->SetSortingLayer(INT_MAX);
    m_BulletPool.pop_back();
    return bullet;
}

void BulletFactory::ReturnBulletToPool(Bullet* bullet)
{
    m_BulletPool.push_back(bullet);
    bullet->gameObject->isActive = false;
    bullet->gameObject->transform->pos.worldPosition = Vector2(0.f, 0.f);
    bullet->gameObject->transform->SetSortingLayer(INT_MIN);
    // 총알 상태 초기화
    bullet->Reset();
}
