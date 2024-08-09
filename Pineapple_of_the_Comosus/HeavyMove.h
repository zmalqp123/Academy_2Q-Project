#pragma once

#include "../D2DEngine/FiniteStateMachine.h"
class HeavyMove : public FSMState
{
	public:
	HeavyMove(FiniteStateMachine* _fsm,std::string _name) : FSMState(_fsm, _name) {}
	virtual ~HeavyMove() {}

	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;
};

