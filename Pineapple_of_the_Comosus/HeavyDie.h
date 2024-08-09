#pragma once
#include "../D2DEngine/FiniteStateMachine.h"
class HeavyDie : public FSMState
{
	public:
	HeavyDie(FiniteStateMachine* _fsm,std::string _name) : FSMState(_fsm, _name) {}
	virtual ~HeavyDie() {}

	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;
};

