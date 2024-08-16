#pragma once
#include "../D2DEngine/FiniteStateMachine.h"
#include "EnemyAttack.h"

class MainPineApple;
class Enemy;
class SwordManAttack : public EnemyAttack
{
public:
	SwordManAttack(FiniteStateMachine* _fsm,std::string _name) : EnemyAttack(_fsm, _name) {}
	virtual ~SwordManAttack() {}

	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;
	void Attack() override;

};

