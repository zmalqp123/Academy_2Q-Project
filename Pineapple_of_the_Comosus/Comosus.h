#pragma once
#include "../D2DEngine/Component.h"
//#include "Popup.h"
#include <vector>

class Comosus : public Component
{
public:
    Comosus();

    void OnHarvest();  // 수확 버튼을 눌렀을 때 실행되는 함수

private:
    void virtual Init() override;
    void virtual Update(float delta) override;
    //void PlayComosusAnimation();  // 코모서스 애니메이션 재생
    //void ShakeCamera(float duration);  // 카메라 흔들림
    //void RefundTurrets();  // 모든 터렛 환불
    //void ShowRewardPopup();  // 보상 팝업창 표시

    //SpriteAnimation comosusAnimation;  // 추가된 멤버 변수
    //Animation comosusAnimation;
    //Camera* camera;
    //std::vector<Turret*> turrets;
    //MainPineApple* pineapple;
    bool comosusReward = false;
    int hp, maxHp;
    int currentExp, maxExp;
    int level;
    int gold;
    float pineappleYPosition;
};
