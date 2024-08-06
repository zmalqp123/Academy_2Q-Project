#pragma once
#include "Turret.h"
class Turret_Mortar : public Turret
{
	public:
	Turret_Mortar() = default;
	~Turret_Mortar() = default;

	void Init() override //8개가 모두 있어야 합니다 8개 있는지 항상 확인해주세요.
	{
		SetCost(800);
		SetRefund(400);
		SetBulletType(BulletType::Burst);
		SetBulletSpeed(3.0f);
		SetDamage(20);
		SetFireRate(8.0f);
		SetPenetration(5);
		SetAngle(0.0f);
	}
};

