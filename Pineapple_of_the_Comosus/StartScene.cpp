#include "StartScene.h"
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/SceneManager.h"
#include "../D2DEngine/InputManager.h"
#include "../D2DEngine/SpriteRenderer.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/ImageUIRenderer.h"
#include "../D2DEngine/SpriteUIAnimation.h"
#include "../D2DEngine/SoundManager.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameTime.h"
#include "Cutton.h";
#include <iostream>
#include "../D2DEngine/Button.h"

StartScene::StartScene() {
    std::cout << "StartScene Constructor" << std::endl;
}

StartScene::~StartScene() {
    std::cout << "StartScene Destructor" << std::endl;
}

void StartScene::Start() {
    std::cout << "Entering StartScene" << std::endl;

    GameTime::GetInstance().SetTimeScale(1.f);

    // 사운드 초기화 및 로드
    SoundManager::GetInstance().LoadSound(L"backgroundMusic", L"../Media/6_Sound/scene1/Bgm/MainMenu_Bgm_01.wav");
    SoundManager::GetInstance().SetVolume(L"backgroundMusic", 0.5f);
    SoundManager::GetInstance().PlaySoundW(L"backgroundMusic", false);

    // click btn 사운드
    SoundManager::GetInstance().LoadSound(L"clickbtn", L"../Media/6_Sound/scene1/Se/ClickButton_Se.wav");
    SoundManager::GetInstance().SetVolume(L"clickbtn", 0.5f);

    auto camera = CreateGameObject<GameObject>();
    auto pCam = camera->CreateComponent<Camera>();
    SetMainCamera(pCam);

    // 초기화 작업 (예: 타이틀 화면, 시작 버튼 등)
    // 배경 이미지
    std::cout << "image StartScene" << std::endl;

    auto bgObj = CreateGameObject<GameObject>();
    auto bgSpr = bgObj->CreateComponent<SpriteRenderer>();
    bgObj->transform->type = Type::Ui;
    bgSpr->LoadTexture(L"../Resource/main/titleBg.png");

    auto startButton = CreateGameObject<GameObject>();
    auto strtSpr = startButton->CreateComponent<Button>();
    startButton->transform->type = Type::Ui;
    startButton->transform->pos.rectposition = { {1100,180} ,{1440,470} };
    strtSpr->LoadTexture(L"../Resource/main/StartButton.png");
    //auto& curS = SceneManager::GetInstance();
    strtSpr->AddListener([&]() {
        SoundManager::GetInstance().PlaySoundW(L"clickbtn", false);
        // 커튼 애니메이션 
        auto cutttonObj = CreateGameObject<GameObject>();
        auto cutton = cutttonObj->CreateComponent<Cutton>();
        cuttons = cutton;
        cutttonObj->transform->type = Type::Ui;
        cutttonObj->transform->pos.rectposition = { {960,0},{1920,1080} };
        auto cuttonSpr = cutttonObj->CreateComponent<SpriteUIAnimation>();
        cuttonSpr->LoadTexture(L"../Resource/10301.png");
        cuttonSpr->LoadAnimationAsset(L"cutton_10301close");
        cuttonSpr->SetAnimation(0, false);
        cutton->UiCutton = cuttonSpr;
        cutton->check = false;

        auto cutttonObj2 = CreateGameObject<GameObject>();
        auto cutton2 = cutttonObj2->CreateComponent<Cutton>();
        cuttons = cutton2;
        cutttonObj2->transform->type = Type::Ui;
        cutttonObj2->transform->pos.rectposition = { {0,0},{960,1080} };
        auto cuttonSpr2 = cutttonObj2->CreateComponent<SpriteUIAnimation>();
        cuttonSpr2->LoadTexture(L"../Resource/10302.png");
        cuttonSpr2->LoadAnimationAsset(L"cutton_10302close");
        cuttonSpr2->SetAnimation(0, false);
        cutton2->UiCutton = cuttonSpr2;
        cutton2->check = false;
        cutton->check = true;
        cutton->ctfn = []() {
            SoundManager::GetInstance().StopSound(L"backgroundMusic");
            SceneManager::GetInstance().SetChangeSceneFlag("GameScene"); 
            };
        });

    auto ruleButton = CreateGameObject<GameObject>();
    ruleButton->transform->SetSortingLayer(1);
    auto ruleSpr = ruleButton->CreateComponent<Button>();
    ruleButton->transform->type = Type::Ui;
    ruleButton->transform->pos.rectposition = { {1320,100} ,{1690,330} };
    ruleSpr->LoadTexture(L"../Resource/main/HowToPlay.png");
   
    //auto& curS = SceneManager::GetInstance();
    
    auto wireButton = CreateGameObject<GameObject>();
    auto wireSpr = wireButton->CreateComponent<Button>();
    wireButton->transform->type = Type::Ui;
    wireButton->transform->pos.rectposition = { {1040,500} ,{1780,1080} };
    wireSpr->LoadTexture(L"../Resource//main/Titilewire.png");
    //auto& curS = SceneManager::GetInstance();
    //strtSpr->AddListener([]() {SceneManager::GetInstance().ChangeScene("GameScene"); });

	auto howtoplay = CreateGameObject<GameObject>();
    howtoplay->transform->SetSortingLayer(2);
	auto howtoplaySpr = howtoplay->CreateComponent<Button>();
    howtoplaySpr->ignoreAlpha = true;
	howtoplay->transform->type = Type::Ui;
	howtoplay->transform->pos.rectposition = { {0,0},{1920,1080} };
	howtoplaySpr->LoadTexture(L"../Resource/main/60001_H2p1.png");
    howtoplay->isActive = false;

    auto howtoplay2 = CreateGameObject<GameObject>();
    howtoplay2->transform->SetSortingLayer(2);
    auto howtoplay2Spr = howtoplay2->CreateComponent<Button>();
    howtoplay2Spr->ignoreAlpha = true;
    howtoplay2->transform->type = Type::Ui;
    howtoplay2->transform->pos.rectposition = { {0,0},{1920,1080} };
    howtoplay2Spr->LoadTexture(L"../Resource/main/70001_H2p2.png");
    howtoplay2->isActive = false;

    auto howtoplay3 = CreateGameObject<GameObject>();
    howtoplay3->transform->SetSortingLayer(2);
    auto howtoplay3Spr = howtoplay3->CreateComponent<Button>();
    howtoplay3Spr->ignoreAlpha = true;
    howtoplay3->transform->type = Type::Ui;
    howtoplay3->transform->pos.rectposition = { {0,0},{1920,1080} };
    howtoplay3Spr->LoadTexture(L"../Resource/main/80001_H2p3.png");
    howtoplay3->isActive = false;

    ruleSpr->AddListener([=]() {
        SoundManager::GetInstance().PlaySoundW(L"clickbtn", false);
        howtoplay->isActive = true;
        });

	howtoplaySpr->AddListener([=]() {
		SoundManager::GetInstance().PlaySoundW(L"clickbtn", false);
		howtoplay->isActive = false;
		howtoplay2->isActive = true;
		});
    howtoplay2Spr->AddListener([=]() {
        SoundManager::GetInstance().PlaySoundW(L"clickbtn", false);
        howtoplay2->isActive = false;
		howtoplay3->isActive = true;
        });
    howtoplay3Spr->AddListener([=]() {
        SoundManager::GetInstance().PlaySoundW(L"clickbtn", false);
        howtoplay3->isActive = false;
		});

}

void StartScene::Clear() {
    __super::Clear();
    std::cout << "Exiting StartScene" << std::endl;

    SoundManager::GetInstance().ReleaseSound(L"backgroundMusic");
    // 정리 작업
}

void StartScene::Update(float deltaTime) {
    __super::Update(deltaTime); 
    // 씬 업데이트 로직
    if (InputManager::GetInstance().IsKeyDown('S')) {
        SceneManager::GetInstance().ChangeScene("GameScene");
    }
}

void StartScene::Render(D2DRenderer* _render) {
    // 씬 렌더링 로직
    __super::Render(_render);
    //std::cout << "Rendering StartScene" << std::endl;
}
