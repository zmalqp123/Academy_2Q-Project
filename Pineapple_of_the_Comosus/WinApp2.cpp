#include "WinApp2.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/SpriteAnimationAsset.h"
#include "../D2DEngine/SpriteAnimation.h"
#include "../D2DEngine/ResourceManager.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/Scene.h"
#include "../D2DEngine/SpriteRenderer.h"
#include "../D2DEngine/Camera.h"
#include "../D2DEngine/PublicData.h"
#include "../D2DEngine/InputManager.h"
#include "../D2DEngine/TextRenderer.h"
#include "../D2DEngine/SoundManager.h"  // SoundManager 헤더 파일 포함
#include "../D2DEngine/ImageUIRenderer.h"
#include "WaveSystem.h"
#include "testChar.h"
#include "Hpbar.h"
#include "Mpbar.h"
#include "HarvestButton.h"

Hpbar* hpBarUi;
Mpbar* mpBarUi;
//HarvestButton* harvestUi;
//GoldButton* goldBtnUi;

void WinApp2::Initialize(HINSTANCE hInstance, int nCmdShow, float x, float y)
{
    // 기본 초기화 + 카메라 생성
    __super::Initialize(hInstance, nCmdShow, x, y);

    scene = new Scene();
    auto camera = scene->CreateGameObject<GameObject>();
    auto pCam = camera->CreateComponent<Camera>();
    scene->SetMainCamera(pCam);

    // 사운드 초기화 및 로드
    SoundManager::GetInstance().LoadSound(L"backgroundMusic", L"../Media/hello.mp3");

    soundVolume = 0.5f;
    SoundManager::GetInstance().SetVolume(L"backgroundMusic", soundVolume);

    // 사운드를 재생하도록 호출
    SoundManager::GetInstance().PlaySoundW(L"backgroundMusic", true); // true로 설정하면 루프 재생

    // Bg 이미지 
    auto obj = scene->CreateGameObject<GameObject>();
    auto spr = obj->CreateComponent<SpriteRenderer>();
    spr->LoadTexture(L"../Resource/morningBG.png");

    // 메뉴바 
    auto UI = scene->CreateGameObject<GameObject>();
    auto Image = UI->CreateComponent<ImageUIRenderer>();
    UI->transform->type = Type::Ui;
    UI->transform->pos.rectposition = { {180,0} ,{1560 + 180,200} };
    Image->LoadTexture(L"../Resource/BG/BG.png");


    // 몬스터 테스트 
    /*auto monsterObj = scene->CreateGameObject<GameObject>();
    auto monsterSpr = monsterObj->CreateComponent<SpriteRenderer>();
    monsterSpr->LoadTexture(L"../Resource/ken.png");*/
   
    // 테스트
    auto spwan = scene->CreateGameObject<GameObject>();
    auto wave = spwan->CreateComponent<WaveSystem>();

    wave->scene = scene;
    // 몬스터 테스트 
    // auto monSpawn = scene->CreateGameObject<GameObject>();
    // auto monsterpool = monSpawn->CreateComponent<testChar>();

    // 웨이브 오브젝트 vector push_back
    // wave->m_Monster.push_back(monsterpool);
    
    // 터렛 Ui

    float spacing = 20.0f;  // 터렛 간의 간격
    float startX = 0.f;    // 첫 번째 터렛의 X 위치
    float width = 120.f;

    for (size_t i = 0; i < 6; i++)
    {
        auto turretUI = scene->CreateGameObject<GameObject>();
        auto turretImage = turretUI->CreateComponent<ImageUIRenderer>();
        //UI->transform->SetParent(turretUI->transform);
        // UI 객체의 위치를 계산
        startX = i * (spacing + width);
        std::cout << startX << std::endl;
        turretUI->transform->SetParent(UI->transform);
        turretUI->transform->type = Type::Ui;
        turretUI->transform->pos.rectposition = { {startX + spacing, 60.f} ,{120.f + startX + spacing, 180.f} };
        turretImage->LoadTexture(L"../Resource/turret.png");
    }

    /*auto obj = scene->CreateGameObject<GameObject>();
    auto spr = obj->CreateComponent<SpriteRenderer>();
    spr->LoadTexture(L"../Resource/turret.png");

    auto UI = scene->CreateGameObject<GameObject>();
    auto Image = UI->CreateComponent<ImageUIRenderer>();
    UI->transform->type = Type::Ui;
    UI->transform->pos.rectposition = { {0,0} ,{1560,200} };
    Image->LoadTexture(L"../Resource/BG/BG.png");*/

    //// 경험치 게이지 바 Ui
    auto Mpbarobj = scene->CreateGameObject<GameObject>();
    auto MpbarImage = Mpbarobj->CreateComponent<ImageUIRenderer>();
    Mpbarobj->transform->SetParent(UI->transform);
    MpbarImage->slideBar = 0.f;
    Mpbarobj->transform->type = Type::Ui;
    Mpbarobj->transform->pos.rectposition = { {20.f,10.f} ,{20.f + 820.f,30.f} };
    mpBarUi = Mpbarobj->CreateComponent<Mpbar>();
    mpBarUi->ImageRender = MpbarImage;
    MpbarImage->LoadTexture(L"../Resource/Mpbar.png");

    // Hp 게이지 바 Ui
    auto Hpbarobj = scene->CreateGameObject<GameObject>();
    auto HpbarImage = Hpbarobj->CreateComponent<ImageUIRenderer>();
    Hpbarobj->transform->SetParent(UI->transform);
    Hpbarobj->transform->type = Type::Ui;
    Hpbarobj->transform->pos.rectposition = { {20.f,30.f} ,{20.f + 820.f,50.f} };
    hpBarUi = Hpbarobj->CreateComponent<Hpbar>();
    hpBarUi->ImageRender = HpbarImage;
    HpbarImage->LoadTexture(L"../Resource/Hpbar.png");

    //// 수확 버튼 -> 이거 완성
    //auto Harvestobj = scene->CreateGameObject<GameObject>();
    //auto HarvestbtnImage = Harvestobj->CreateComponent<ImageUIRenderer>();
    //Harvestobj->transform->SetParent(UI->transform);
    //Harvestobj->transform->type = Type::Ui;
    //Harvestobj->transform->pos.rectposition = { {20.f + 820.f + 200.f,10.f} ,{20.f + 820.f + 200.f + 200.f, 200.f -spacing} };
    //harvestUi = Harvestobj->CreateComponent<HarvestButton>();
    //harvestUi->ImageRender = HarvestbtnImage;
    //HarvestbtnImage->LoadTexture(L"../Resource/harvest.png");

    // 골드 보유량 Ui
   /* auto Goldobj = scene->CreateGameObject<GameObject>();
    auto GoldbtnImage = Goldobj->CreateComponent<ImageUIRenderer>();
    Goldobj->transform->SetParent(UI->transform);
    Goldobj->transform->type = Type::Ui;
    Goldobj->transform->pos.rectposition = { {20.f + 820.f + 200.f,10.f} ,{20.f + 820.f + 200.f + 200.f, 200.f} };
    harvestUi = Goldobj->CreateComponent<HarvestButton>();
    harvestUi->ImageRender = HarvestbtnImage;
    HarvestbtnImage->LoadTexture(L"../Resource/harvest.png");*/

    //// 강화 버튼 
    //auto obj = scene->CreateGameObject<GameObject>();
    //auto spr = obj->CreateComponent<SpriteRenderer>();
    //spr->LoadTexture(L"../Resource/BG/BG.png");

    //auto UI = scene->CreateGameObject<GameObject>();
    //auto Image = UI->CreateComponent<ImageUIRenderer>();
    //UI->transform->type = Type::Ui;
    //UI->transform->pos.rectposition = { {0,0} ,{1560,200} };
    //Image->LoadTexture(L"../Resource/BG/BG.png");
}

void WinApp2::Update(float deltaTime)
{
    __super::Update(deltaTime);

    scene->Update(deltaTime);

    if (InputManager::GetInstance().IsKeyDown('1'))
    {
        hpBarUi->takeDamage(10.f);
        hpBarUi->ImageRender->slideBar = hpBarUi->getBarWidth();
        std::cout << hpBarUi->ImageRender->m_DstRect.right << std::endl;
        std::cout << hpBarUi->getBarWidth() << std::endl;
    }

    if (InputManager::GetInstance().IsKeyDown('2'))
    {
        mpBarUi->takeMp(10.f);
        mpBarUi->ImageRender->slideBar = mpBarUi->getBarWidth();
        std::cout << mpBarUi->ImageRender->m_DstRect.right << std::endl;
        std::cout << mpBarUi->getBarWidth() << std::endl;
    }

   // scene->cam->transform->m_RelativeLocation += Vector2(-1.f,0.f) * 100.f * deltaTime;
    // 사운드 업데이트
    SoundManager::GetInstance().Update();
}

void WinApp2::Render(D2DRenderer* _render)
{
    __super::Render(_render);
    scene->Render(_render);
}

void WinApp2::Uninitialize()
{
    // 사운드 종료
    SoundManager::GetInstance().ReleaseSound(L"backgroundMusic");
    __super::Uninitialize();
}
