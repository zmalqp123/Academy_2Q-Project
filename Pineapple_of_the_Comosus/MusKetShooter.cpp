#include "MusKetShooter.h"

MusKetShooter::MusKetShooter()
{
    // MusKetShooter 특성 초기화 -> 수치 변경 해야함
    SetStat(100, 60, 10, 1, 5);
    SetResist(0, 0, 0, 0);
    SetReward(50, 10);

    eliteType = EliteType::Normal; // 기본 엘리트 타입 설정 (Normal)
}

void MusKetShooter::Init()
{
    Enemy::Init();
}

void MusKetShooter::Update(float delta)
{
    Enemy::Update(delta);
}

void MusKetShooter::Render(D2D1_MATRIX_3X2_F cameraMat)
{
    Enemy::Render(cameraMat);
}
