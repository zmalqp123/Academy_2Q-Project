#include "StartScene.h"
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/SceneManager.h"
#include "../D2DEngine/InputManager.h"
#include <iostream>

StartScene::StartScene() {
    std::cout << "StartScene Constructor" << std::endl;
}

StartScene::~StartScene() {
    std::cout << "StartScene Destructor" << std::endl;
}

void StartScene::Start() {
    std::cout << "Entering StartScene" << std::endl;
    // 초기화 작업 (예: 타이틀 화면, 시작 버튼 등)
}

void StartScene::Clear() {
    std::cout << "Exiting StartScene" << std::endl;
    // 정리 작업
}

void StartScene::Update(float deltaTime) {
    // 씬 업데이트 로직
    if (InputManager::GetInstance().IsKeyDown('1')) {
        SceneManager::GetInstance().ChangeScene("GameScene");
    }
}

void StartScene::Render(D2DRenderer* _render) {
    // 씬 렌더링 로직
    std::cout << "Rendering StartScene" << std::endl;
}
