#include "BulletFactory.h"
#include "../D2DEngine/SpriteRenderer.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/SideMovement.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/GameObject.h"
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
    auto spriteRenderer = bulletObj->CreateComponent<SpriteRenderer>();
    auto movement = bulletObj->CreateComponent<SideMovement>();  // SideMovement 사용
    auto collider = bulletObj->CreateComponent<BoxCollider>();
    collider->SetCollisionType(CollisionType::Overlap);

    spriteRenderer->LoadTexture(L"../Resource/circle.png");  // 총알 텍스처 로드

    Bullet* bullet = bulletObj->CreateComponent<Bullet>();
    bullet->move = movement;
    bullet->pBoxcollider = collider;

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
    m_BulletPool.pop_back();
    return bullet;
}

void BulletFactory::ReturnBulletToPool(Bullet* bullet)
{
    m_BulletPool.push_back(bullet);
    bullet->gameObject->isActive = false;

    // 총알 상태 초기화
    bullet->Reset();
}
