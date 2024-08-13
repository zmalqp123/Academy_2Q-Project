#pragma once
#include "../D2DEngine/FiniteStateMachine.h"

class Enemy;
class HeavyAttack : public FSMState
{
public:
	HeavyAttack(FiniteStateMachine* _fsm,std::string _name) : FSMState(_fsm, _name) {}
	virtual ~HeavyAttack() {}

	Enemy* enemy;

	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;

};

