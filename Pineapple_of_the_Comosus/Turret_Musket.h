#pragma once
#include "Turret.h"
class Turret_Musket : public Turret
{
public:
	Turret_Musket() = default;
	~Turret_Musket() = default;

	void Init() override //8개가 모두 있어야 합니다 8개 있는지 항상 확인해주세요.
	{
		SetCost(500);
		SetRefund(250);
		SetBulletType(BulletType::Bullet);
		SetBulletSpeed(30.0f);
		SetDamage(12);
		SetFireRate(3.0f);
		SetPenetration(3);
		SetAngle(0.0f);
	}
};

