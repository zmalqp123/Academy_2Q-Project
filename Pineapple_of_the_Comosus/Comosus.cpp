#include "Comosus.h"
#include "../D2DEngine/GameTime.h"
Comosus::Comosus()
{
    // 초기화
    //comosusAnimation = GetComponent<Animation>();
    //camera = GetComponent<Camera>();
    //turrets = GetComponents<Turret>();
    //pineapple = GetComponent<Pineapple>();
    //hp = 100;  // 예시 초기값
    //maxHp = 100;  // 예시 초기값
    //currentExp = 50;  // 예시 초기값
    //maxExp = 100;  // 예시 초기값
    //level = 1;  // 예시 초기값
    //gold = 1000;  // 예시 초기값
    //pineappleYPosition = pineapple->GetYPosition();
    // 
    // 
    // 애니메이션 에셋 로드
    //comosusAnimation.LoadAnimationAsset(L"../Resource/tentacle_animation.csv");  // 실제 경로로 변경
    //comosusAnimation.SetAnimation(0, false, false);  // 첫 애니메이션 설정
}

void Comosus::Init()
{
    // 여기서 코모서스 애니메이션 초기화
}

void Comosus::Update(float delta)
{
}


//void Comosus::OnHarvest()
//{
//    PlayComosusAnimation();
//    ShakeCamera(4.0f);
//
//    hp = maxHp;
//
//    if (currentExp == maxExp)
//    {
//        comosusReward = true;
//    }
//
//    // Exp 감소 처리
//    for (float elapsedTime = 0.0f; elapsedTime < 4.0f; elapsedTime += GetDeltaTime())
//    {
//        currentExp -= currentExp / 3 * GetDeltaTime();
//        if (currentExp <= 0)
//        {
//            currentExp = 0;
//            break;
//        }
//    }
//
//    level++;
//
//    // 코모서스 애니메이션 동안 터렛 설치 비활성화
//    for (auto turret : turrets)
//    {
//        turret->SetActive(false);
//    }
//
//    // 파인애플 위로 이동 및 화면 밖으로 사라질 때 스프라이트 삭제
//    while (pineapple->GetYPosition() < ScreenHeight)
//    {
//        pineappleYPosition += 5.0f * GetDeltaTime();  // 예시 속도
//        pineapple->SetYPosition(pineappleYPosition);
//    }
//
//    if (pineappleYPosition >= ScreenHeight)
//    {
//        pineapple->DeleteSprite();
//    }
//
//    // 모든 터렛 환불 및 골드 증가
//    RefundTurrets();
//
//    // 보상 팝업창 등장
//    if (comosusReward)
//    {
//        ShowRewardPopup();
//    }
//}
//
//void Comosus::PlayComosusAnimation()
//{
//    comosusAnimation.Play();
//}
//
//void Comosus::ShakeCamera(float duration)
//{
//    camera->Shake(duration);
//}
//
//void Comosus::RefundTurrets()
//{
//    int refundAmount = 0;
//    for (auto turret : turrets)
//    {
//        refundAmount += turret->GetRefundAmount();
//        turret->Destroy();
//    }
//    gold += refundAmount;
//}
//
//void Comosus::ShowRewardPopup()
//{
//    auto popup = new Popup("RewardPopup");
//    popup->Show();
//    // 인게임 시간 멈춤
//    GetGame()->Pause();
//}
