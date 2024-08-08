#include "SwordMan.h"
#include"../D2DEngine/SoundManager.h"

SwordMan::SwordMan()
{
    // SwordMan 특성 초기화
    SetStat(100, 60, 10, 1, 5);
    SetResist(0, 0, 0, 0);
    SetReward(50, 10);

    eliteType = EliteType::Normal; // 기본 엘리트 타입 설정 (Normal)
}

void SwordMan::Init()
{
    __super::Init();
    SoundManager::GetInstance().LoadSound(L"SwordAttack", L"../Media/Dead.wav");
}

void SwordMan::Update(float delta)
{
    __super::Update(delta);

    elapsedTime += delta;

    if (elapsedTime > 2.0f)
    {
        Attack();
        elapsedTime = 0.f;
    }
}

void SwordMan::Render(D2D1_MATRIX_3X2_F cameraMat)
{
    __super::Render(cameraMat);
}

void SwordMan::Attack()
{
    SoundManager::GetInstance().PlaySoundW(L"SwordAttack", false);
    std::cout <<"sound" << std::endl;
}
