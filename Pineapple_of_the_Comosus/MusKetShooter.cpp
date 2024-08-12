#include "MusKetShooter.h"
#include "Bullet.h"
#include "BulletFactory.h"
#include "../D2DEngine/Scene.h"
#include"../D2DEngine/GameObject.h"
#include "../D2DEngine/Transform.h"

//MusKetShooter::MusKetShooter(Scene* scene)
//{
//    // BulletFactory를 초기화 (Scene을 전달)
//}

void MusKetShooter::Init()
{
    //// BombCart 특성 초기화 -> 수치 변경 해야함
    //SetStat(16, 5.0f, 10, 3.0f, 240);
    //SetResist(0, 0, 0, 0);
    //SetReward(50, 10);

    //eliteType = EliteType::Normal; // 기본 엘리트 타입 설정 (Normal)
}

void MusKetShooter::Update(float delta)
{
    __super::Update(delta);

    //timeSinceLastShot += delta;

    //// 총알을 발사할 조건이 만족되면 발사
    //if (timeSinceLastShot >= shootCooldown)
    //{
    //    Shoot();
    //    timeSinceLastShot = 0.0f;  // 타이머 초기화
    //}

    // 기타 업데이트 코드 추가
}

void MusKetShooter::Render(D2D1_MATRIX_3X2_F cameraMat)
{
    __super::Render(cameraMat);
    // 렌더링 관련 추가 코드
}

void MusKetShooter::Shoot()
{
    if (bulletFactory)
    {
        // BulletFactory에서 Bullet을 가져온다
        Bullet* bullet = bulletFactory->GetBulletFromPool();

        // 총알 초기화 (속도와 방향 설정)
        Vector2 shootDirection = { 1.0f, 0.0f };  // 예를 들어 오른쪽으로 발사
        float bulletSpeed = 500.0f;
        bullet->Init(bulletSpeed, shootDirection);

        // 총알의 위치를 MusKetShooter의 위치로 설정
        bullet->gameObject->transform->pos.worldPosition = gameObject->transform->pos.worldPosition;
    }
}
