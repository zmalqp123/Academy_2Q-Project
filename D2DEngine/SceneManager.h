// SceneManager.h
#pragma once
#include <unordered_map>
#include <string>
#include "Scene.h"

class SceneManager {
public:
    // 싱글턴 인스턴스를 가져오는 함수
    static SceneManager& GetInstance();

    // 씬을 등록하는 함수
    void RegisterScene(const std::string& name, Scene* scene);

    void SetChangeSceneFlag(const std::string& name);

    // 특정 씬으로 전환하는 함수
    void ChangeScene(const std::string& name);

    void Release();

    // 현재 활성화된 씬을 가져오는 함수
    Scene* GetCurrentScene();

    bool shouldChangeSceneFlag = false;
    std::string nextSceneName;
private:
    // 생성자 및 소멸자
    SceneManager();
    ~SceneManager();

    // 복사 생성자와 대입 연산자 삭제
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;

    std::unordered_map<std::string, Scene*> scenes;
    Scene* currentScene;


};
