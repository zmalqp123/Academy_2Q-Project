#pragma once
#include "WinApp3.h"
#include "StartScene.h"
#include "GameScene.h"
#include"../D2DEngine/SceneManager.h"

void WinApp3::Initialize(HINSTANCE hInstance, int nCmdShow, float x, float y) {
    __super::Initialize(hInstance, nCmdShow, x, y);

    // 씬 매니저를 사용하여 씬 등록
    SceneManager& sceneManager = SceneManager::GetInstance();

    auto startScene = new StartScene();
    auto gameScene = new GameScene();

    sceneManager.RegisterScene("StartScene", startScene);
    sceneManager.RegisterScene("GameScene", gameScene);

    // 시작 씬으로 전환
    sceneManager.ChangeScene("StartScene");
}

void WinApp3::Update(float deltaTime) {
    __super::Update(deltaTime);

    // 씬 업데이트 호출 (씬 매니저 사용)
    SceneManager::GetInstance().GetCurrentScene()->Update(deltaTime);
}

void WinApp3::Render(D2DRenderer* _render) {
    __super::Render(_render);

    // 씬 렌더링 호출 (씬 매니저 사용)
    SceneManager::GetInstance().GetCurrentScene()->Render(_render);
}

void WinApp3::Uninitialize() {
    __super::Uninitialize();
    SceneManager::GetInstance().Release();
}

