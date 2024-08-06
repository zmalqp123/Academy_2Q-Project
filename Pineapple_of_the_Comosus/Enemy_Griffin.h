#pragma once
#include "Enemy.h"
class Enemy_Griffin : public Enemy
{	
public:
	Enemy_Griffin(EliteType _Elite) : Enemy(_Elite) {}
	~Enemy_Griffin() = default;

	void Init() override { //함수 3개 필수.
		if (eliteType == EliteType::Normal) {
			SetResist(0, 0, 30, 0);
			SetStat(22, 20, 20, 2, 1);
			SetReward(30, 30);
		}
		else if (eliteType == EliteType::Hard) {
			SetResist(20, 20, 50, 0);
			SetStat(31, 10, 20, 2, 1);
			SetReward(35, 30);

		}
		else if (eliteType == EliteType::Fast) {
			SetResist(0, 0, 10, 0);
			SetStat(12, 40, 40, 2, 1);
			SetReward(25, 30);
		}
		else if (eliteType == EliteType::Hero) {
			SetResist(0,0,40,0);
			SetStat(28,20,40,2,1);
			SetReward(50,90);
		}

	}


};

