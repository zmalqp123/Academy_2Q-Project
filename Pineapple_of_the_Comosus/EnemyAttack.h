#pragma once
#include "../D2DEngine/FiniteStateMachine.h"

class Enemy;
class MainPineApple;
class EnemyAttack : public FSMState
{
public:
	EnemyAttack(FiniteStateMachine* _fsm, std::string _name) : FSMState(_fsm, _name) {}
	virtual ~EnemyAttack() {}
	float elapsedTime = 0.f;
	float elapsedTimeforMotion = 0.f;

	Enemy* enemy = nullptr;
	MainPineApple* mainPineApple = nullptr;

	bool isAttack = false;

	virtual void Enter() override;
	virtual void Update(float deltaTime) override;
	virtual void Exit() override;

	virtual void Attack();
	virtual void AttackMotion(float deltaTime);
};

