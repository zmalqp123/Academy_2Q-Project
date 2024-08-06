#pragma once
#include "Enemy.h"
class Enemy_Sword : public Enemy
{
public:
	Enemy_Sword(EliteType _Elite) : Enemy(_Elite) {}
	~Enemy_Sword() = default;

	void Init() override { //함수 3개 필수.
		if (eliteType == EliteType::Normal) {
			SetResist(0, 0, 0, 0);
			SetStat(12, 10, 5, 1, 1);
			SetReward(10, 10);
		}
		else if (eliteType == EliteType::Hard) {
			SetResist(20, 20, 20, 0);
			SetStat(21, 10, 3, 1, 1);
			SetReward(20, 10);

		}
		else if (eliteType == EliteType::Fast) {
			SetResist(0, 0, 0, 0);
			SetStat(8, 30, 8, 1, 1);
			SetReward(10, 10);
		}
		else if (eliteType == EliteType::Hero) {
			SetResist(20, 0, 0, 0);
			SetStat(18, 10, 8, 1, 1);
			SetReward(30, 20);
		}
		
	}
};

