#pragma once
#include "Enemy.h"

class BulletFactory;
class Scene;
class MusKetShooter : public Enemy
{
public:
    MusKetShooter() {};
	MusKetShooter(Scene* scene);

    virtual void Init() override;
    virtual void Update(float delta) override;
    virtual void Render(D2D1_MATRIX_3X2_F cameraMat) override;
    void Shoot();  // 총알 발사 함수

    BulletFactory* bulletFactory;  // BulletFactory 포인터
private:
    float shootCooldown =1.f;           // 총알 발사 간격을 위한 쿨다운 타이머
    float timeSinceLastShot;       // 마지막으로 총알을 발사한 이후의 시간
};

