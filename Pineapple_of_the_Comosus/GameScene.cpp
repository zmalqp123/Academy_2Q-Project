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
#include "DataManager.h"
//Hpbar* hpBarUi;
//Mpbar* mpBarUi;

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

    // 게임 매니저 드래그엔 드롭, 파인애플 설치, 터렛 파인애플 몹 데이터 등을 관리함.
    auto gmObj = CreateGameObject<GameObject>();
    auto GameManager = gmObj->CreateComponent<GamePlayManager>();
    GameManager->camera = pCam;
    auto boxObj = CreateGameObject<GameObject>();
    boxObj->SetActive(false);
    auto boxColl = boxObj->CreateComponent<BoxCollider>();
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
    paObj->transform->pos.worldPosition = { 0.f, 0.f };
    auto pineApple = paObj->CreateComponent<MainPineApple>();
    testPineApple = pineApple;
    pineApple->bulletFactory = bulletFactory;
    auto pineappleSpr = paObj->CreateComponent<SpriteRenderer>();
    pineappleSpr->SetCenter({ 0.5f, 0.6f });
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

    GameManager->pineApple = pineApple;
    // 파인애플 타일들
    {
        

        {
            // 파인애플 타일들
            auto paTileObj = CreateGameObject<GameObject>();
            paTileObj->transform->SetParent(paObj->transform);
            paTileObj->transform->pos.worldPosition = { -200.f, 200.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 0;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(60.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
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
            paTileObj->transform->pos.worldPosition = { 0.f, 200.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 1;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(60.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
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
            paTileObj->transform->pos.worldPosition = { 200.f, 200.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 2;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(60.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
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
            paTileObj->transform->pos.worldPosition = { -100.f, 100.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 3;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(60.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
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
            paTileObj->transform->pos.worldPosition = { 100.f, 100.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 4;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(60.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
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
            paTileObj->transform->pos.worldPosition = { -200.f, 0.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 5;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(60.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
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
            paTileObj->transform->pos.worldPosition = { 0.f, 0.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 6;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(60.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
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
            paTileObj->transform->pos.worldPosition = { 200.f, 0.f };

            auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
            pineTile->pApple = pineApple;
            pineTile->index = 7;

            auto coll = paTileObj->CreateComponent<CircleCollider>();
            coll->SetCollisionType(CollisionType::Overlap);
            coll->isKinemetic = true;
            coll->SetRadius(60.f);

            auto childObj = CreateGameObject<GameObject>();
            childObj->isActive = false;
            auto tur = childObj->CreateComponent<Turret>();
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
    uiImage->LoadTexture(L"../Resource/30401_상태창배경.png");

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

    // 내부 컴포넌트 포인터 주소 연결
    nightSystem->waveSystem = waveSystem;


    // 터렛 UI
    float spacing = 20.0f;
    float startX = 0.f;
    float width = 120.f;

    //std::vector<Button*> btn;
    // 이미지 파일 경로 배열
    std::wstring turretImages[] = {
        L"../Resource/30201_터렛버튼_석궁타워.png",
        L"../Resource/30202_터렛버튼_머스킷타워.png",
        L"../Resource/30203_터렛버튼_박격포타워.png",
        L"../Resource/30205_터렛버튼_슬로우완드타워.png",
        L"../Resource/30204_터렛버튼_슈퍼석궁.png",
        L"../Resource/30206_터렛버튼_성장촉진제.png"
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
        turretUIComp->SetIndex(i);

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

    auto hpBarObj = CreateGameObject<GameObject>();
    auto hpBarImage = hpBarObj->CreateComponent<ImageUIRenderer>();
    hpBarObj->transform->SetParent(uiObj->transform);
    hpBarObj->transform->type = Type::Ui;
    hpBarObj->transform->pos.rectposition = { {20.f,0.f} ,{20.f + 820.f,20.f} };
    hpBarUi = hpBarObj->CreateComponent<Hpbar>();
    hpBarUi->ImageRender = hpBarImage;
    hpBarImage->LoadTexture(L"../Resource/30403_HP_02_꽉참.png");


    auto mpBarObj = CreateGameObject<GameObject>();
    auto mpBarImage = mpBarObj->CreateComponent<ImageUIRenderer>();
    mpBarObj->transform->SetParent(uiObj->transform);
    mpBarObj->transform->type = Type::Ui;
    mpBarObj->transform->pos.rectposition = { {20.f,20.f} ,{20.f + 820.f,40.f} };
    auto mpBar = mpBarObj->CreateComponent<Mpbar>();
    pineApple->expbar = mpBar;
    mpBar->ImageRender = mpBarImage;
    mpBarImage->LoadTexture(L"../Resource/30402_수확바_02_꽉참.png");
   

    /*auto turretUI = CreateGameObject<GameObject>();
    auto turretImage = turretUI->CreateComponent<Button>();
    startX = i * (spacing + width);
    turretUI->transform->SetParent(uiObj->transform);
    turretUI->transform->type = Type::Ui;
    turretUI->transform->pos.rectposition = { {startX + spacing, 60.f} ,{120.f + startX + spacing, 180.f} };
    turretImage->LoadTexture(L"../Resource/turret.png");*/

    std::cout << "Ewwwwwww" << std::endl;

    // 골드 보유량 Ui
    auto GoldObj = CreateGameObject<GameObject>();
    auto GoldImage = GoldObj->CreateComponent<Button>();
    GoldObj->transform->SetParent(uiObj->transform);
    GoldObj->transform->type = Type::Ui;
    GoldObj->transform->pos.rectposition = { {20.f + 820.f + spacing ,113.f} ,{20.f + 820.f + spacing + 270.f, 196.f} };
    /*harvestUi = Harvestobj->CreateComponent<HarvestButton>();
    harvestUi->ImageRender = HarvestbtnImage;*/
    GoldImage->LoadTexture(L"../Resource/30404_골드보유량창.png");
    // wstring str;
    

    // 레벨 버튼 
    auto UpgradeObj = CreateGameObject<GameObject>();
    auto UpgradeImage = UpgradeObj->CreateComponent<Button>();
    UpgradeObj->transform->SetParent(uiObj->transform);
    UpgradeObj->transform->type = Type::Ui;
    UpgradeObj->transform->pos.rectposition = { {20.f + 820.f + spacing ,0.f} ,{20.f + 820.f + spacing + 270.f, 98.f} };
    /*harvestUi = Harvestobj->CreateComponent<HarvestButton>();
    harvestUi->ImageRender = HarvestbtnImage;*/
    UpgradeImage->LoadTexture(L"../Resource/30406_파인애플레벨창.png");

    // 수확 버튼 -> 이거 완성 500 * 500
    auto Harvestobj = CreateGameObject<GameObject>();
    auto HarvestbtnImage = Harvestobj->CreateComponent<Button>();
    Harvestobj->transform->SetParent(uiObj->transform);
    Harvestobj->transform->type = Type::Ui;
    Harvestobj->transform->pos.rectposition = { {20.f + 820.f + spacing + 270.f + spacing,10.f} ,{20.f + 820.f + spacing + 270.f + spacing + 180.f, 200.f - spacing} };
    /*harvestUi = Harvestobj->CreateComponent<HarvestButton>();
    harvestUi->ImageRender = HarvestbtnImage;*/
    HarvestbtnImage->LoadTexture(L"../Resource/harvest.png");
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

    SoundManager::GetInstance().Update();
}

void GameScene::Render(D2DRenderer* _render) {
    __super::Render(_render);

    auto pd = testPineApple;
    int gold = pd->GetPineAppleGold();
    std::wstring pineAppleGold = std::to_wstring(gold);
    //std::wcout << "pineAppleGold" << pineAppleGold << std::endl;
   
    D2DRenderer::getIncetance().DrawStringTextw(pineAppleGold.c_str(), m_GameObjects[0]->transform->m_WorldTransform, D2D1::ColorF::Red);
    //std::cout << cam->transform->m_WorldTransform.dx << std::endl;
    //std::cout << cam->transform->m_WorldTransform.dy << std::endl;
}
