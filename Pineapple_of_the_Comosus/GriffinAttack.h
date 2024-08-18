#pragma once
#include "../D2DEngine/FiniteStateMachine.h"
#include "EnemyAttack.h"
class MainPineApple;
class Enemy;
class GriffinAttack : public EnemyAttack
{
public:
	GriffinAttack(FiniteStateMachine* _fsm,std::string _name) : EnemyAttack(_fsm, _name) {}
	virtual ~GriffinAttack() {}

	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;
	void Attack() override;
};


