#pragma once
#include "Enemy.h"
class Enemy_Bomber : public Enemy
{
	public:
	Enemy_Bomber(EliteType _Elite) : Enemy(_Elite) {}
	~Enemy_Bomber() = default;

	void Init() override { //함수 3개 필수.
		if (eliteType == EliteType::Normal) {
			SetResist(30, 0, 0, 0);
			SetStat(150, 3, 500, 1, 1);
			SetReward(240, 0);
		}
		else if (eliteType == EliteType::Hard) {
			SetResist(50, 20, 20, 0);
			SetStat(360, 1, 500, 1, 1);
			SetReward(360, 0);

		}
		else if (eliteType == EliteType::Fast) {
			SetResist(0, 0, 0, 0);
			SetStat(120, 5, 1000, 1, 1);
			SetReward(360, 0);
		}
		else if (eliteType == EliteType::Hero) {
			SetResist(40, 0, 0, 0);
			SetStat(270, 3, 1000, 1, 1);
			SetReward(540, 0);
		}

	}
};

