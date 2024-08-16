#pragma once
#include "../D2DEngine/FiniteStateMachine.h"
#include "EnemyAttack.h"
class MainPineApple;
class Enemy;
class BomberAttack : public EnemyAttack
{
public:
	BomberAttack(FiniteStateMachine* _fsm,std::string _name) : EnemyAttack(_fsm, _name) {}
	virtual ~BomberAttack() {}

	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;

};

