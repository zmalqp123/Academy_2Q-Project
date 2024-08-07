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

//Hpbar* hpBarUi;
//Mpbar* mpBarUi;

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

    // 사운드 초기화 및 로드
    SoundManager::GetInstance().LoadSound(L"backgroundMusic", L"../Media/hello.mp3");
    SoundManager::GetInstance().SetVolume(L"backgroundMusic", 0.5f);
    SoundManager::GetInstance().PlaySoundW(L"backgroundMusic", true);

    // 배경 이미지
    auto bgObj = CreateGameObject<GameObject>();
    auto bgSpr = bgObj->CreateComponent<SpriteRenderer>();
    bgSpr->LoadTexture(L"../Resource/morningBG.png");

    // 메뉴바
    auto uiObj = CreateGameObject<GameObject>();
    auto uiImage = uiObj->CreateComponent<ImageUIRenderer>();
    uiObj->transform->type = Type::Ui;
    uiObj->transform->pos.rectposition = { {180,0} ,{1560 + 180,200} };
    uiImage->LoadTexture(L"../Resource/BG/BG.png");

    // 웨이브 시스템
    auto waveObj = CreateGameObject<GameObject>();
    waveSystem = waveObj->CreateComponent<WaveSystem>();
    waveSystem->scene = this;

    // 터렛 UI
    float spacing = 20.0f;
    float startX = 0.f;
    float width = 120.f;

    for (size_t i = 0; i < 6; i++) {
        auto turretUI = CreateGameObject<GameObject>();
        auto turretImage = turretUI->CreateComponent<ImageUIRenderer>();
        startX = i * (spacing + width);
        turretUI->transform->SetParent(uiObj->transform);
        turretUI->transform->type = Type::Ui;
        turretUI->transform->pos.rectposition = { {startX + spacing, 60.f} ,{120.f + startX + spacing, 180.f} };
        turretImage->LoadTexture(L"../Resource/turret.png");
    }

    // HP 및 MP 바 UI
    auto mpBarObj = CreateGameObject<GameObject>();
    auto mpBarImage = mpBarObj->CreateComponent<ImageUIRenderer>();
    mpBarObj->transform->SetParent(uiObj->transform);
    mpBarObj->transform->type = Type::Ui;
    mpBarObj->transform->pos.rectposition = { {20.f,10.f} ,{20.f + 820.f,30.f} };
    mpBarUi = mpBarObj->CreateComponent<Mpbar>();
    mpBarUi->ImageRender = mpBarImage;
    mpBarImage->LoadTexture(L"../Resource/Mpbar.png");

    auto hpBarObj = CreateGameObject<GameObject>();
    auto hpBarImage = hpBarObj->CreateComponent<ImageUIRenderer>();
    hpBarObj->transform->SetParent(uiObj->transform);
    hpBarObj->transform->type = Type::Ui;
    hpBarObj->transform->pos.rectposition = { {20.f,30.f} ,{20.f + 820.f,50.f} };
    hpBarUi = hpBarObj->CreateComponent<Hpbar>();
    hpBarUi->ImageRender = hpBarImage;
    hpBarImage->LoadTexture(L"../Resource/Hpbar.png");
}

void GameScene::Clear() {
    __super::Clear();
    std::cout << "Exiting GameScene" << std::endl;
    // 정리 작업
    SoundManager::GetInstance().ReleaseSound(L"backgroundMusic");
}

void GameScene::Update(float deltaTime) {
    Scene::Update(deltaTime);

    if (InputManager::GetInstance().IsKeyDown('1')) {
        hpBarUi->takeDamage(10.f);
        hpBarUi->ImageRender->slideBar = hpBarUi->getBarWidth();
        std::cout << hpBarUi->ImageRender->m_DstRect.right << std::endl;
        std::cout << hpBarUi->getBarWidth() << std::endl;
    }

    if (InputManager::GetInstance().IsKeyDown('2')) {
        mpBarUi->takeMp(10.f);
        mpBarUi->ImageRender->slideBar = mpBarUi->getBarWidth();
        std::cout << mpBarUi->ImageRender->m_DstRect.right << std::endl;
        std::cout << mpBarUi->getBarWidth() << std::endl;
    }

    // 메인 씬 전환 테스트
    if (InputManager::GetInstance().IsKeyDown('3')) {
        SceneManager::GetInstance().ChangeScene("StartScene");
    }

    SoundManager::GetInstance().Update();
}

void GameScene::Render(D2DRenderer* _render) {
    Scene::Render(_render);
}
