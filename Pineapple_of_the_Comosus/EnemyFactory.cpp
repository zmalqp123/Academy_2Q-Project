#include "EnemyFactory.h"
#include "../D2DEngine/Scene.h"
#include "../D2DEngine/SpriteRenderer.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/BoxCollider.h"
#include"../D2DEngine/GameObject.h"

Enemy* EnemyFactory::CreateEnemy(int type)
{
    auto mon = scene->CreateGameObject<GameObject>();
    auto loadMon = mon->CreateComponent<SpriteRenderer>();
    auto movement = mon->CreateComponent<Movement>();
    auto collider = mon->CreateComponent<BoxCollider>();

    Enemy* enemy = nullptr;

    switch (type)
    {
    case 0:
        enemy = mon->CreateComponent<SwordMan>();
        loadMon->LoadTexture(L"../Resource/swordsman.png");
        break;
    case 1:
        enemy = mon->CreateComponent<BombCart>();
        loadMon->LoadTexture(L"../Resource/tile.png");
        break;
    case 2:
        enemy = mon->CreateComponent<Griffin>();
        loadMon->LoadTexture(L"../Resource/Sun.png");
        break;
    case 3:
        enemy = mon->CreateComponent<HeavyKnight>();
        loadMon->LoadTexture(L"../Resource/moon.png");
        break;
    case 4:
        enemy = mon->CreateComponent<MusKetShooter>();
        loadMon->LoadTexture(L"../Resource/MusKetShooter.png");
        break;
    default:
        // 기본 적 또는 오류 처리
        return nullptr;
    }

    enemy->move = movement;
    enemy->pBoxcollider = collider;
    return enemy;
}