#pragma once
#include "../D2DEngine/GameObject.h"

enum class EliteType
{
	Normal,
	Hard,
	Fast,
	Hero
};

class Enemy : public GameObject
{
protected:
	int resistArrow;
	int resistBullet;
	int resistBurst;
	int resistComosus;

	int hp;
	int moveSpeed;
	int attack;
	int attackRate;
	int range;
	
	EliteType eliteType;
	int reward;
	int expReward;

public:
	Enemy(EliteType _Elite) : eliteType(_Elite) {}
	virtual ~Enemy() = default;

	virtual void Init() = 0;

	void SetReward(int Reward, int ExpReward) {
		reward = Reward;
		expReward = ExpReward;
	}

	void SetResist(int ResistArrow, int ResistBullet, int ResistBurst, int ResistComosus) {
		resistArrow = ResistArrow;
		resistBullet = ResistBullet;
		resistBurst = ResistBurst;
		resistComosus = ResistComosus;
	}

	void SetStat(int Hp, int MoveSpeed, int Attack, int AttackRate, int Range) {
		hp = Hp;
		moveSpeed = MoveSpeed;
		attack = Attack;
		attackRate = AttackRate;
		range = Range;
	}

	Enemy& GetEnemy() { return *this; }
};

