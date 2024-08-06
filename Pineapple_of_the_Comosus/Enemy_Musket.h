#pragma once
#include "Enemy.h"
class Enemy_Musket : public Enemy
{
	public:
	Enemy_Musket(EliteType _Elite) : Enemy(_Elite) {}
	~Enemy_Musket() = default;

	void Init() override { //함수 3개 필수.
		if (eliteType == EliteType::Normal) {
			SetResist(0, 10, 0, 0);
			SetStat(16, 5, 20, 3, 10);
			SetReward(20, 20);
		}
		else if (eliteType == EliteType::Hard) {
			SetResist(20,20,20,0);
			SetStat(27, 5, 20, 3, 10);
			SetReward(40, 20);

		}
		else if (eliteType == EliteType::Fast) {
			SetResist(0, 0, 0, 0);
			SetStat(12, 20, 40, 3, 10);
			SetReward(30, 20);
		}
		else if (eliteType == EliteType::Hero) {
			SetResist(0, 40, 0, 0);
			SetStat(21, 10, 40, 3, 10);
			SetReward(70, 40);
		}

	}
};

