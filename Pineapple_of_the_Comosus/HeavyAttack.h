#pragma once
#include "../D2DEngine/FiniteStateMachine.h"
#include "EnemyAttack.h"
class MainPineApple;
class Enemy;
class HeavyAttack : public EnemyAttack
{
public:
	HeavyAttack(FiniteStateMachine* _fsm,std::string _name) : EnemyAttack(_fsm, _name) {}
	virtual ~HeavyAttack() {}

	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;

};

