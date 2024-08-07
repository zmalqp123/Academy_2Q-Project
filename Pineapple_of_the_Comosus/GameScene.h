#pragma once
#include "../D2DEngine/Scene.h"
#include "Hpbar.h"
#include "Mpbar.h"
#include "WaveSystem.h"

class GameScene : public Scene {
private:
    WaveSystem* waveSystem; // WaveSystem 인스턴스 추가
    Mpbar* mpBarUi; // 선언
    Hpbar* hpBarUi;
public:
    GameScene();
    ~GameScene() override;

    // 씬이 활성화될 때 호출
    void Start() override;

    // 씬이 비활성화될 때 호출
    void Clear() override;

    // 씬의 업데이트 로직
    void Update(float deltaTime) override;

    // 씬의 렌더링 로직
    void Render(D2DRenderer* _render) override;
};
