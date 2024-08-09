#pragma once

#include "../D2DEngine/FiniteStateMachine.h"
class GriffinMove : public FSMState
{
	public:
	GriffinMove(FiniteStateMachine* _fsm,std::string _name) : FSMState(_fsm, _name) {}
	virtual ~GriffinMove() {}

	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;
};

