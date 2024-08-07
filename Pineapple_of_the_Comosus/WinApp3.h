#pragma once

#include "../D2DEngine/WinGameApp.h"
#include "../D2DEngine/Scene.h"
#include "../D2DEngine/D2DRenderer.h"

class WinApp3 : public WinGameApp {
public:
    // 생성자
    WinApp3() {};

    // 소멸자
    virtual ~WinApp3() {};

    // 애플리케이션 초기화
    void Initialize(HINSTANCE hInstance, int nCmdShow, float x, float y) override;

    // 애플리케이션 업데이트
    void Update(float deltaTime) override;

    // 애플리케이션 렌더링
    void Render(D2DRenderer* _render) override;

    // 애플리케이션 종료 처리
    void Uninitialize() override;

private:
    // 현재 씬을 가리키는 포인터
    Scene* currentScene;
};
