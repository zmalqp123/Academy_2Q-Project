#pragma once
#include "../D2DEngine/FiniteStateMachine.h"
class SwordDie : public FSMState
{
	public:
	SwordDie(FiniteStateMachine* _fsm,std::string _name) : FSMState(_fsm, _name) {}
	virtual ~SwordDie() {}

	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;
};

