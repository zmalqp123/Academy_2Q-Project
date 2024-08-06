#pragma once
#include "Turret.h"
class Turret_SuperCrossBow : public Turret
{
public:
	Turret_SuperCrossBow() = default;
	~Turret_SuperCrossBow() = default;

	void Init() override
	{
		SetCost(1500);
		SetRefund(750);
		SetBulletType(BulletType::Arrow);
		SetBulletSpeed(10.0f);
		SetDamage(8);
		SetFireRate(1.5f);
		SetPenetration(1);
		SetAngle(0.0f);
	}
};

