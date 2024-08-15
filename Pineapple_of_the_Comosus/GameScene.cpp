#include "GameScene.h"
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/Camera.h"
#include "../D2DEngine/SoundManager.h"
#include "../D2DEngine/InputManager.h"
#include <iostream>
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/SpriteRenderer.h"
#include"../D2DEngine/ImageUIRenderer.h"
#include"../D2DEngine/SceneManager.h"
#include "../D2DEngine/Button.h"
#include "../D2DEngine/BoxCollider.h"
#include "EnemyFactory.h"
#include "TurretUI.h"
#include "GamePlayManager.h"
#include "MainPineApple.h"
#include "SelectTurretContainer.h"
#include "BulletFactory.h"
#include "Turret.h"
#include "PineAppleTile.h"
#include "../D2DEngine/CircleCollider.h"
#include "../D2DEngine/TextUIRenderer.h"
#include "DataManager.h"
#include "DynamicData.h"
#include "Comosus.h"
#include "../D2DEngine/ResourceManager.h"
#include "../D2DEngine/SpriteAnimation.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "FSMHarvest.h"
//Hpbar* hpBarUi;
//Mpbar* mpBarUi;
#include <functional>
#include <algorithm>

MainPineApple* testPineApple = nullptr;

GameScene::GameScene() {
    std::cout << "GameScene Constructor" << std::endl;
}

GameScene::~GameScene() {
    std::cout << "GameScene Destructor" << std::endl;
}

void GameScene::Start() {
    std::cout << "Entering GameScene" << std::endl;

    auto camera = CreateGameObject<GameObject>();
    auto pCam = camera->CreateComponent<Camera>();
    SetMainCamera(pCam);

    auto bulletFactory = new BulletFactory(this);

    //데이터 매니저 초기화
    auto& DataManager = DataManager::GetInstance();
    DataManager.LoadEnemySheetFromCSV(L"../Resource/EnemyData.csv");
    DataManager.LoadTurretSheetFromCSV(L"../Resource/TurretData.csv");
    DataManager.LoadWaveSheetFromCSV(L"../Resource/WaveData");

    // 게임 매니저 드래그엔 드롭, 파인애플 설치, 터렛 파인애플 몹 데이터 등을 관리함.
    auto gmObj = CreateGameObject<GameObject>();
    auto GameManager = gmObj->CreateComponent<GamePlayManager>();
    auto dynamicData = gmObj->CreateComponent<DynamicData>();
    dynamicData->Init();

    GameManager->camera = pCam;
    auto boxObj = CreateGameObject<GameObject>();
    boxObj->SetActive(false);
    auto boxColl = boxObj->CreateComponent<BoxCollider>();
    boxColl->ignoreEventSystem = true;
    boxColl->SetCollisionType(CollisionType::Overlap);
    auto selector = boxObj->CreateComponent<SelectTurretContainer>();
    GameManager->selectBoxObj = boxObj;
    GameManager->multiSelectBox = boxColl;
    GameManager->selectTurrets = selector;


    // 드래그 시 이미지 보여줄 오브젝트
    auto testDragObj = CreateGameObject<GameObject>();
    testDragObj->SetActive(false);
    auto sproper = testDragObj->CreateComponent<SpriteRenderer>();
    sproper->alpha = 0.7f;
    GameManager->dragObj = testDragObj;
    testDragObj->transform->SetSortingLayer(1);

    // 코모서스 파인애플 (겁나 큼)
    auto paObj = CreateGameObject<GameObject>();
    paObj->transform->SetSortingLayer(-1);
    paObj->transform->pos.worldPosition = { 0.f, 0.f };
    auto pineApple = paObj->CreateComponent<MainPineApple>();

    // 상태 생성
    /*auto pineFSM = paObj->CreateComponent<FiniteStateMachine>();
    pineApple->fsm = pineFSM;
    pineFSM->CreateState<TentacleDefault>("harveststart");
    pineFSM->CreateState<TentacleDownState>("TentacleDownState");
    pineFSM->CreateState<TentacleUpState>("TentacleUpState");
    pineFSM->CreateState<ShowPopupState>("ShowPopupState");*/

    pineApple->rewardData = dynamicData;
    testPineApple = pineApple;
    pineApple->bulletFactory = bulletFactory;
    auto pineappleSpr = paObj->CreateComponent<SpriteRenderer>();
    pineappleSpr->SetCenter({ 0.5f, 0.67f });
    pineappleSpr->LoadTexture(L"../Resource/pineApple_Actual.png");
    auto pineColl = paObj->CreateComponent<BoxCollider>();
    pineColl->ignoreEventSystem = true;
    pineColl->isKinemetic = true;
    pineColl->SetCenter({ 300.f, 100.f });
    pineColl->SetExtent({ 0.f, 400.f });
    pineColl = paObj->CreateComponent<BoxCollider>();
    pineColl->ignoreEventSystem = true;
    pineColl->isKinemetic = true;
    pineColl->SetCenter({ -300.f, 100.f });
    pineColl->SetExtent({ 0.f, 400.f });

    // 코모서스 강림
    auto comoObj = CreateGameObject<GameObject>();
    comoObj->transform->pos.worldPosition = { 0.f,250.f };
    auto comosus = comoObj->CreateComponent<Comosus>();
    comoObj->transform->SetSortingLayer(100);
    auto comsusSpr = comoObj->CreateComponent<SpriteAnimation>();
    Texture* t = nullptr;
    ResourceManager::GetInstance().CreateTextureFromFile(L"../Resource/30722_tentacle_animation.png", &t);
    comsusSpr->m_pTexture = t;
    comsusSpr->LoadAnimationAsset(L"Comosus");
    comsusSpr->SetAnimation(0, false);
    pineApple->comosus = comsusSpr;

    GameManager->pineApple = pineApple;
    // 파인애플 타일들
    {
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { -3.f, 190.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { -85.f, 120.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { 80.f, 120.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { -3.f, 53.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { -85.f, -16.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { 80.f, -16.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { -3.f, -84.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { -85.f, -154.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { 80.f, -154.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { -3.f, -220.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { -165.f, 53.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { 158.f, 53.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { -165.f, -84.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { 158.f, -84.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { -155.f, 190.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { 150.f, 190.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { -155.f, -220.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { 150.f, -220.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(50.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->transform->SetSortingLayer(1);
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
            tur->dynamicData = dynamicData;
            tur->parentPineApple = pineApple;
            auto circleColl = childObj->CreateComponent<CircleCollider>();
            circleColl->SetCollisionType(CollisionType::Overlap);
            childObj->transform->SetParent(paTileObj->transform);
            auto spr = childObj->CreateComponent<SpriteRenderer>();
            pineTile->turret = childObj;
        }
    }


    // 사운드 초기화 및 로드
    SoundManager::GetInstance().LoadSound(L"backgroundMusic", L"../Media/hello.mp3");
    SoundManager::GetInstance().SetVolume(L"backgroundMusic", 0.5f);
    SoundManager::GetInstance().PlaySoundW(L"backgroundMusic", true);

    // 배경 이미지
    auto bgObj = CreateGameObject<GameObject>();
    bgObj->transform->SetSortingLayer(-10);
    auto bgSpr = bgObj->CreateComponent<SpriteRenderer>();
    bgSpr->LoadTexture(L"../Resource/morningBG.png");

    // 메뉴바
    auto uiObj = CreateGameObject<GameObject>();
    auto uiImage = uiObj->CreateComponent<ImageUIRenderer>();
    uiObj->transform->type = Type::Ui;
    uiObj->transform->pos.rectposition = { {180,0} ,{1560 + 180,200} };
    uiImage->LoadTexture(L"../Resource/30401.png");

    // 웨이브 시스템
    auto waveObj = CreateGameObject<GameObject>();
    waveSystem = waveObj->CreateComponent<WaveSystem>();
    waveSystem->scene = this;
    waveSystem->bulletFactory = bulletFactory;
    waveSystem->mainPineApple = GameManager->pineApple;
    waveSystem->Init();


    // DayNightCycleComponent 생성 및 게임 오브젝트에 추가
    auto nightObj = CreateGameObject<GameObject>();
    nightSystem = nightObj->CreateComponent<DayNightCycle>();
    waveSystem->dayNightCycle = nightSystem;

    // 해 이미지
    auto sunObj = CreateGameObject<GameObject>();
    sunObj->transform->SetSortingLayer(-9);
    auto sunSpr = sunObj->CreateComponent<SpriteRenderer>();
    sunSpr->LoadTexture(L"../Resource/BGSun.png");
    sunObj->transform->pos.worldPosition = { 800.f, 400.f };
    nightSystem->m_Sun = sunObj;

    // 달 이미지
    auto moonObj = CreateGameObject<GameObject>();
    moonObj->transform->SetSortingLayer(-9);
    auto moonSpr = moonObj->CreateComponent<SpriteRenderer>();
    moonSpr->LoadTexture(L"../Resource/BGMoon.png");
    moonObj->transform->pos.worldPosition = { 800.f, -300.f };
    nightSystem->m_Moon = moonObj;


    // 내부 컴포넌트 포인터 주소 연결
    //nightSystem->waveSystem = waveSystem;


    // 터렛 UI
    float spacing = 20.0f;
    float startX = 0.f;
    float width = 120.f;

    //std::vector<Button*> btn;
    // 이미지 파일 경로 배열
    std::wstring turretImages[] = {
        L"../Resource/30201.png",
        L"../Resource/30202.png",
        L"../Resource/30203.png",
        L"../Resource/30204.png",
        L"../Resource/30205.png",
        L"../Resource/30206.png"
    };

    // UI 생성 및 이미지 설정 코드
    std::vector<Button*> btn;

    for (size_t i = 0; i < 6; i++) {
        auto turretUI = CreateGameObject<GameObject>();
        float startX = i * (spacing + width);
        turretUI->transform->SetParent(uiObj->transform);
        turretUI->transform->type = Type::Ui;
        turretUI->transform->pos.rectposition = { {startX + spacing, 60.f} ,{120.f + startX + spacing, 180.f} };

        auto backImage = turretUI->CreateComponent<ImageUIRenderer>();
        backImage->ignoreEventSystem = true;

        // 각 터렛 UI에 대해 다른 이미지 로드
        backImage->LoadTexture(turretImages[i]);

        // 변경사항 터렛UI
        auto turretUIChild = CreateGameObject<GameObject>();
        turretUIChild->transform->SetParent(turretUI->transform);
        turretUIChild->transform->type = Type::Ui;
        turretUIChild->transform->pos.rectposition = { {0.f, 0.f} ,{120.f, 120.f} };

        auto turretButton = turretUIChild->CreateComponent<Button>();
        turretButton->LoadTexture(turretImages[i]);
        //turretButton->LoadTexture(L"../Resource/turret.png");  // 버튼의 이미지는 고정
        auto turretUIComp = turretUIChild->CreateComponent<TurretUI>();
        turretUIComp->SetIndex(30501 + (10*i));

        btn.push_back(turretButton);
        // 터렛 버튼 클릭 시 동작 정의
        //turretButton->AddListener([GameManager, turretUIComp]() {GameManager->StartBatch(turretUIComp->GetIndex()); });
    }
    auto t1 = btn[0]->gameObject->GetComponent<TurretUI>();
    btn[0]->AddListener([GameManager, t1]() {GameManager->StartBatch(t1->GetIndex()); });
    auto t2 = btn[1]->gameObject->GetComponent<TurretUI>();
    btn[1]->AddListener([GameManager, t2]() {GameManager->StartBatch(t2->GetIndex()); });
    auto t3 = btn[2]->gameObject->GetComponent<TurretUI>();
    btn[2]->AddListener([GameManager, t3]() {GameManager->StartBatch(t3->GetIndex()); });
    auto t4 = btn[3]->gameObject->GetComponent<TurretUI>();
    btn[3]->AddListener([GameManager, t4]() {GameManager->StartBatch(t4->GetIndex()); });
    auto t5 = btn[4]->gameObject->GetComponent<TurretUI>();
    btn[4]->AddListener([GameManager, t5]() {GameManager->StartBatch(t5->GetIndex()); });
    auto t6 = btn[5]->gameObject->GetComponent<TurretUI>();
    btn[5]->AddListener([GameManager, t6]() {GameManager->StartBatch(t6->GetIndex()); });
    // HP 및 MP 바 UI
    
    // hpbar
    auto hpBarObj = CreateGameObject<GameObject>();
    auto hpBarImage = hpBarObj->CreateComponent<ImageUIRenderer>();
    hpBarObj->transform->SetParent(uiObj->transform);
    hpBarObj->transform->type = Type::Ui;
    hpBarObj->transform->pos.rectposition = { {20.f,0.f} ,{20.f + 820.f,20.f} };
    hpBarUi = hpBarObj->CreateComponent<Hpbar>();
    pineApple->hpbar = hpBarUi;
    hpBarUi->ImageRender = hpBarImage;
    hpBarImage->LoadTexture(L"../Resource/30403_02.png");


    // expbar
    auto mpBarObj = CreateGameObject<GameObject>();
    auto mpBarImage = mpBarObj->CreateComponent<ImageUIRenderer>();
    mpBarObj->transform->SetParent(uiObj->transform);
    mpBarObj->transform->type = Type::Ui;
    mpBarObj->transform->pos.rectposition = { {20.f,20.f} ,{20.f + 820.f,40.f} };
    auto mpBar = mpBarObj->CreateComponent<Mpbar>();
    pineApple->expbar = mpBar;
    mpBar->ImageRender = mpBarImage;
    mpBarImage->LoadTexture(L"../Resource/30402_02.png");


    /*auto turretUI = CreateGameObject<GameObject>();
    auto turretImage = turretUI->CreateComponent<Button>();
    startX = i * (spacing + width);
    turretUI->transform->SetParent(uiObj->transform);
    turretUI->transform->type = Type::Ui;
    turretUI->transform->pos.rectposition = { {startX + spacing, 60.f} ,{120.f + startX + spacing, 180.f} };
    turretImage->LoadTexture(L"../Resource/turret.png");*/

    // 골드 Ui
    auto GoldObj = CreateGameObject<GameObject>();
    auto GoldImage = GoldObj->CreateComponent<Button>();
    GoldObj->transform->SetParent(uiObj->transform);
    GoldObj->transform->type = Type::Ui;
    GoldObj->transform->pos.rectposition = { {20.f + 820.f + spacing ,113.f} ,{20.f + 820.f + spacing + 270.f, 196.f} };
    GoldImage->LoadTexture(L"../Resource/30404.png");
    // wstring str;


    // 레벨 버튼 
    auto UpgradeObj = CreateGameObject<GameObject>();
    auto UpgradeImage = UpgradeObj->CreateComponent<Button>();
    UpgradeObj->transform->SetParent(uiObj->transform);
    UpgradeObj->transform->type = Type::Ui;
    UpgradeObj->transform->pos.rectposition = { {20.f + 820.f + spacing ,0.f} ,{20.f + 820.f + spacing + 270.f, 98.f} };
    UpgradeImage->LoadTexture(L"../Resource/30406.png");

    // 수확 버튼 -> 이거 완성 500 * 500
    auto Harvestobj = CreateGameObject<GameObject>();
    auto HarvestbtnImage = Harvestobj->CreateComponent<Button>();
    Harvestobj->transform->SetParent(uiObj->transform);
    Harvestobj->transform->type = Type::Ui;
    Harvestobj->transform->pos.rectposition = { {20.f + 820.f + spacing + 270.f + spacing,10.f} ,{20.f + 820.f + spacing + 270.f + spacing + 180.f, 200.f - spacing} };
    /*harvestUi = Harvestobj->CreateComponent<HarvestButton>();
    harvestUi->ImageRender = HarvestbtnImage;*/

    HarvestbtnImage->LoadTexture(L"../Resource/harvest.png");
    
    pineApple->harvestbtn = HarvestbtnImage;

    // 검은색 배경과 버튼 그룹 생성
    auto uiGroup = CreateGameObject<GameObject>();
    uiGroup->transform->type = Type::Ui;
    uiGroup->SetActive(false); // 초기에는 비활성화

    // 반투명 검은색 배경 추가
    auto blackObj = CreateGameObject<GameObject>();
    blackObj->transform->SetParent(uiGroup->transform);
    blackObj->transform->SetSortingLayer(-10); // 다른 UI나 오브젝트보다 뒤에 있도록 설정
    SpriteRenderer* blackSpr = blackObj->CreateComponent<SpriteRenderer>();
    //bgSpr->SetColor(D2D1::ColorF(0, 0, 0, 0.5f)); // 검은색 배경 (반투명)
    //bgSpr->transform->pos.rectposition = { {0.f, 0.f} ,{1920.f, 1080.f} };

    // 버튼 5개 생성 및 초기 비활성화
    std::vector<Button*> buttons;

    // 버튼의 위치와 크기를 수동으로 지정
    D2D1_RECT_F buttonPositions[] = {
        {500.f, 600.f, 800.f, 700.f},  // 첫 번째 버튼의 위치 (x1, y1, x2, y2)
        {900.f, 600.f, 1200.f, 700.f}, // 두 번째 버튼의 위치
        {500.f, 800.f, 800.f, 900.f},  // 세 번째 버튼의 위치
        {900.f, 800.f, 1200.f, 900.f}, // 네 번째 버튼의 위치
        {700.f, 400.f, 1000.f, 500.f}  // 다섯 번째 버튼의 위치 (중앙 하단)
    };

    for (size_t i = 0; i < 5; i++) {
        auto buttonObj = CreateGameObject<GameObject>();
        float startX = i * (spacing + width);
        buttonObj->transform->SetParent(uiGroup->transform);
        buttonObj->transform->type = Type::Ui;

        // rectposition 값을 개별적으로 설정
        buttonObj->transform->pos.rectposition.leftBottom = { buttonPositions[i].left, buttonPositions[i].bottom };
        buttonObj->transform->pos.rectposition.rightTop = { buttonPositions[i].right, buttonPositions[i].top };

        auto buttonImage = buttonObj->CreateComponent<Button>();
        buttonImage->ignoreEventSystem = false;  // 버튼 클릭 가능하도록 설정
        buttonImage->LoadTexture(L"../Resource/button.png"); // 버튼 이미지 설정

        pineApple->Popup =  buttonImage;
      /*  auto button = buttonObj->CreateComponent<Button>();
        button->LoadTexture(L"../Resource/button.png");*/

        // 각 버튼에 클릭 리스너 추가
        buttonImage->AddListener([i,uiGroup]() {
            std::wcout << L"Button " << i + 1 << L" clicked!" << std::endl;
            uiGroup->SetActive(false); // 초기에는 비활성화
            });

        buttons.push_back(buttonImage);
    }

    // 수확 버튼 클릭 시 -> harvest 안에서 sectactive 
    pineApple->Harvest();
    // 그룹 전체 활성화
    HarvestbtnImage->AddListener([uiGroup]() {
        uiGroup->SetActive(true); // 수확 버튼을 눌렀을 때 그룹 전체를 활성화

    });


    // 수확 버튼 클릭시

    //HarvestbtnImage->AddListener([pineApple]() {pineApple->Harvest(); });//[지역변수](매개변수){기능}

    // 수확이 버튼 눌렀을 때 코모서스 애니메이션 A재생
    //
    // 현재 hp -> maxHP
}

void GameScene::Clear() {
    __super::Clear();
    std::cout << "Exiting GameScene" << std::endl;
    // 정리 작업
    SoundManager::GetInstance().ReleaseSound(L"backgroundMusic");
}

void GameScene::Update(float deltaTime) {
    __super::Update(deltaTime);

    if (InputManager::GetInstance().IsKeyDown('1')) {
        hpBarUi->takeDamage(10.f);
        hpBarUi->ImageRender->slideBar = hpBarUi->getBarWidth();
        std::cout << hpBarUi->ImageRender->m_DstRect.right << std::endl;
        std::cout << hpBarUi->getBarWidth() << std::endl;
    }

    /*if (InputManager::GetInstance().IsKeyDown('2')) {
        mpBarUi->takeMp(10.f);
        mpBarUi->ImageRender->slideBar = mpBarUi->getBarWidth();
        std::cout << mpBarUi->ImageRender->m_DstRect.right << std::endl;
        std::cout << mpBarUi->getBarWidth() << std::endl;
    }*/

    // 메인 씬 전환 테스트
    if (InputManager::GetInstance().IsKeyDown('3')) {
        SceneManager::GetInstance().ChangeScene("StartScene");
    }

    // 동시 사운드 테스트 
    if (InputManager::GetInstance().IsKeyDown('5')) {
        // 5번을 클릭할 때 마다 SoundManager::GetInstance().LoadSound(L"backgroundMusic", L"../Media/hello.mp3"); 사운드가 
        // 기존의 사운드는 그대로 출력되고 새 사운드가 중복으로 출력되게 하려고 하는데, 어떻게 하면 좋을까?
         // 새로운 고유 이름으로 사운드 로드
        std::wstring soundName = L"gimicSuccess";
        SoundManager::GetInstance().LoadSound(soundName, L"../Media/gimicSuccess.mp3");

        // 로드된 사운드를 재생
        SoundManager::GetInstance().PlaySoundW(soundName, true);
    }
    //마우스 스크롤 기능
    if (InputManager::GetInstance().GetMousePosition().x>0.f && InputManager::GetInstance().GetMousePosition().x < 100.f && camera->gameObject->transform->pos.worldPosition.x>-1560.f) {
		camera->gameObject->transform->pos.worldPosition.x -= 1000.f * deltaTime;
    }

    if (InputManager::GetInstance().GetMousePosition().x < 1920.f && InputManager::GetInstance().GetMousePosition().x > 1820.f && camera->gameObject->transform->pos.worldPosition.x < 1560.f) {
        camera->gameObject->transform->pos.worldPosition.x += 1000.f * deltaTime;
    }

    if (InputManager::GetInstance().IsKeyUp(VK_SPACE)) {
        camera->gameObject->transform->pos.worldPosition.x = 0.f;
    }

    SoundManager::GetInstance().Update();
}

void GameScene::Render(D2DRenderer* _render) {
    __super::Render(_render);

    auto pd = testPineApple;
    int gold = pd->GetPineAppleGold();
    //std::cout << gold << std::endl;
    std::wstring pineAppleGold = std::to_wstring(gold);
    D2DRenderer::getIncetance().DrawStringTextw(pineAppleGold.c_str(), m_GameObjects[0]->transform->m_WorldTransform, D2D1::ColorF::Red);
    //std::cout << cam->transform->m_WorldTransform.dx << std::endl;
    //std::cout << cam->transform->m_WorldTransform.dy << std::endl;

    /*int pineappleLV = pd->GetPineAppleLV();
    std::wstring pineAppleLV = std::to_wstring(pineappleLV);
    D2DRenderer::getIncetance().DrawStringTextw(pineAppleLV.c_str(), m_GameObjects[0]->transform->m_WorldTransform, D2D1::ColorF::Blue);*/


}
