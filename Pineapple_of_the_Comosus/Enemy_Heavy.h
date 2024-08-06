#pragma once
#include "Enemy.h"

class Enemy_Heavy : public Enemy
{
public:
	Enemy_Heavy(EliteType _Elite) : Enemy(_Elite) {}
	~Enemy_Heavy() = default;

	void Init() override { //함수 3개 필수.
		if (eliteType == EliteType::Normal) {
			SetResist(30, 0, 0, 0);
			SetStat(21, 10, 10, 5, 1);
			SetReward(50, 40);
		}
		else if (eliteType == EliteType::Hard) {
			SetResist(50, 20, 20, 0);
			SetStat(80, 5, 10, 5, 1);
			SetReward(80, 40);

		}
		else if (eliteType == EliteType::Fast) {
			SetResist(0, 0, 0, 0);
			SetStat(18, 25, 20, 5, 1);
			SetReward(70, 40);
		}
		else if (eliteType == EliteType::Hero) {
			SetResist(40, 0, 0, 0);
			SetStat(72, 10, 20, 5, 1);
			SetReward(120, 80);
		}

	}
};

