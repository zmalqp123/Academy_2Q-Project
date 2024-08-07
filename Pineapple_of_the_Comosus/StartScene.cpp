#include "StartScene.h"
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/SceneManager.h"
#include "../D2DEngine/InputManager.h"
#include "../D2DEngine/SpriteRenderer.h"
#include <iostream>

StartScene::StartScene() {
    std::cout << "StartScene Constructor" << std::endl;
}

StartScene::~StartScene() {
    std::cout << "StartScene Destructor" << std::endl;
}

void StartScene::Start() {
    std::cout << "Entering StartScene" << std::endl;

    auto camera = CreateGameObject<GameObject>();
    auto pCam = camera->CreateComponent<Camera>();
    SetMainCamera(pCam);

    // 초기화 작업 (예: 타이틀 화면, 시작 버튼 등)
    // 배경 이미지
    auto bgObj = CreateGameObject<GameObject>();
    auto bgSpr = bgObj->CreateComponent<SpriteRenderer>();
    bgSpr->LoadTexture(L"../Resource/mainPage.png");
    std::cout << "image StartScene" << std::endl;
}

void StartScene::Clear() {
    __super::Clear();
    std::cout << "Exiting StartScene" << std::endl;
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
