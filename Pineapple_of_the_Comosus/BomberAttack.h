#pragma once
#include "../D2DEngine/FiniteStateMachine.h"
class BomberAttack : public FSMState
{
	BomberAttack(FiniteStateMachine* _fsm,std::string _name) : FSMState(_fsm, _name) {}
	virtual ~BomberAttack() {}

	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;

};

