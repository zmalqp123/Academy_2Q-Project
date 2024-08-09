#pragma once
#include "../D2DEngine/FiniteStateMachine.h"
class MusKetMove : public FSMState
{
	public:
	MusKetMove(FiniteStateMachine* _fsm,std::string _name) : FSMState(_fsm, _name) {}
	virtual ~MusKetMove() {}

	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;
};

