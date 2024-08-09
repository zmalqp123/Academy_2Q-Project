#pragma once
#include "../D2DEngine/FiniteStateMachine.h"
class MusKetDie : public FSMState
{
	public:
	MusKetDie(FiniteStateMachine* _fsm,std::string _name) : FSMState(_fsm, _name) {}
	virtual ~MusKetDie() {}

	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;
};

