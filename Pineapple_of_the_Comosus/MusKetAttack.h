#pragma once
#include "../D2DEngine/FiniteStateMachine.h"
#include "EnemyAttack.h"

class Enemy;
class MainPineApple;
class MusKetAttack : public EnemyAttack
{
public:
	MusKetAttack(FiniteStateMachine* _fsm,std::string _name) : EnemyAttack(_fsm, _name) {}
	virtual ~MusKetAttack() {}

	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;
	void Attack() override;
	void AttackMotion(float deltaTime) override;
};


