#pragma once
#include "../D2DEngine/FiniteStateMachine.h"
class HeavyAttack : public FSMState
{
	HeavyAttack(FiniteStateMachine* _fsm,std::string _name) : FSMState(_fsm, _name) {}
	virtual ~HeavyAttack() {}

	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;

};

