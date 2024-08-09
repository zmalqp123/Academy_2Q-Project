#pragma once
#include "../D2DEngine/FiniteStateMachine.h"
class GriffinAttack : public FSMState
{
public:
	GriffinAttack(FiniteStateMachine* _fsm,std::string _name) : FSMState(_fsm, _name) {}
	virtual ~GriffinAttack() {}

	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;

};


