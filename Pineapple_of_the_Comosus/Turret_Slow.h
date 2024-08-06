#pragma once
#include "Turret.h"
class Turret_Slow : public Turret
{
	public:
	Turret_Slow() = default;
	~Turret_Slow() = default;

	void Init() override //8개가 모두 있어야 합니다 8개 있는지 항상 확인해주세요.
	{
		SetCost(600);
		SetRefund(300);
		SetBulletType(BulletType::Burst);
		SetBulletSpeed(0.0f); //이 부분은 논의가 필요할 듯 합니다. 기획분과 상의 해주세요.
		SetDamage(0);
		SetFireRate(4.5f);
		SetPenetration(1);
		SetAngle(0.0f);
	}
};

