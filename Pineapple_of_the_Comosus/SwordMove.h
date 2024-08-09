#pragma once
#include "../D2DEngine/FiniteStateMachine.h"

class SwordMove : public FSMState
{
	SwordMove(FiniteStateMachine* _fsm, std::string _name) : FSMState(_fsm,name) {}

	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;

};

