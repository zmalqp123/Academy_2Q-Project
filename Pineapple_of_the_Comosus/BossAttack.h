#pragma once
#include "../D2DEngine/FiniteStateMachine.h"
#include "EnemyAttack.h"

class MainPineApple;
class Enemy;
class BossAttack : public EnemyAttack
{
public:
	BossAttack(FiniteStateMachine* _fsm, std::string _name) : EnemyAttack(_fsm, _name) {}
	virtual ~BossAttack() {}

	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;
	void Attack() override;

};
