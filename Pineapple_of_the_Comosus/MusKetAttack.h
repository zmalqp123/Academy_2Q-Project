#pragma once
#include "../D2DEngine/FiniteStateMachine.h"
class MusKetAttack : public FSMState
{
	MusKetAttack(FiniteStateMachine* _fsm,std::string _name) : FSMState(_fsm, _name) {}
	virtual ~MusKetAttack() {}

	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;

};


