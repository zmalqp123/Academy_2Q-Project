#include "EndScene.h"
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/SceneManager.h"
#include "../D2DEngine/InputManager.h"
#include "../D2DEngine/SpriteRenderer.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/ImageUIRenderer.h"
#include "../D2DEngine/SpriteUIAnimation.h"
#include "../D2DEngine/SoundManager.h"
#include "../D2DEngine/Transform.h"
#include "Cutton.h";
#include <iostream>
#include "../D2DEngine/Button.h"

EndScene::EndScene()
{
}

EndScene::~EndScene()
{
}

void EndScene::Start()
{
    auto camera = CreateGameObject<GameObject>();
    auto pCam = camera->CreateComponent<Camera>();
    SetMainCamera(pCam);

	// 엔딩 사운드 초기화 

	// 게임오벙 UI 메인화면으로 버튼 만들기
	auto endObj = CreateGameObject<GameObject>();
	auto endSpr = endObj->CreateComponent<SpriteRenderer>();
	endObj->transform->type = Type::Ui;
	endSpr->LoadTexture(L"../Resource/main/titleBg.png");

    auto gameOverButton = CreateGameObject<GameObject>();
    auto ggSpr = gameOverButton->CreateComponent<Button>();
    gameOverButton->transform->type = Type::Ui;
    gameOverButton->transform->pos.rectposition = { {860,440} ,{1060,640} };
    ggSpr->LoadTexture(L"../Resource/gg.png");

	auto restartButton = CreateGameObject<GameObject>();
	auto rstSpr = restartButton->CreateComponent<Button>();
	restartButton->transform->type = Type::Ui;
	restartButton->transform->pos.rectposition = { {1100,180} ,{1440,470} };
	rstSpr->LoadTexture(L"../Resource/main/StartButton.png");
    rstSpr->AddListener([&]() {

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
        cutton->ctfn = []() {SceneManager::GetInstance().SetChangeSceneFlag("StartScene"); };
        });
}

void EndScene::Clear()
{
    __super::Clear();
}

void EndScene::Update(float deltaTime)
{
    __super::Update(deltaTime);
}

void EndScene::Render(D2DRenderer* _render)
{
    __super::Render(_render);
}
