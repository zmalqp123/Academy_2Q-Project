#pragma once
#include "../D2DEngine/FiniteStateMachine.h"
class GriffinDie : public FSMState
{
	public:
	GriffinDie(FiniteStateMachine* _fsm,std::string _name) : FSMState(_fsm, _name) {}
	virtual ~GriffinDie() {}

	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;
};

