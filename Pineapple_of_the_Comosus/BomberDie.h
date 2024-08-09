#pragma once
#include "../D2DEngine/FiniteStateMachine.h"
class BomberDie : public FSMState
{
	public:
	BomberDie(FiniteStateMachine* _fsm,std::string _name) : FSMState(_fsm, _name) {}
	virtual ~BomberDie() {}

	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;
};

