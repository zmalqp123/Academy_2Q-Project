// SceneManager.cpp
#include "pch.h"
#include "SceneManager.h"
#include <iostream>

// 싱글턴 인스턴스를 가져오는 함수
SceneManager& SceneManager::GetInstance() {
    static SceneManager instance;
    return instance;
}

// 생성자
SceneManager::SceneManager() : currentScene(nullptr) {}

// 소멸자
SceneManager::~SceneManager() {
    Release();
}

// 씬을 등록하는 함수
void SceneManager::RegisterScene(const std::string& name, Scene* scene) {
    scenes[name] = scene;
}

// 특정 씬으로 전환하는 함수
void SceneManager::ChangeScene(const std::string& name) {
    if (currentScene) {
        currentScene->Clear(); // 현재 씬에서 자원 정리
    }

    auto it = scenes.find(name);
    if (it != scenes.end()) {
        currentScene = it->second;
        // 추가적인 초기화가 필요하면 여기서 처리
        currentScene->Start(); // 새로운 씬의 초기화
    }
    else {
        std::cerr << "Scene " << name << " not found!" << std::endl;
    }
}

void SceneManager::Release()
{
    for (auto scene : scenes)
    {
      delete scene.second;
    }
    scenes.clear(); // 컨테이너 비우기
}

// 현재 활성화된 씬을 가져오는 함수
Scene* SceneManager::GetCurrentScene() {
    return currentScene;
}
