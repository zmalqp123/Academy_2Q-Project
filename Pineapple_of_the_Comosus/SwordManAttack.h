#pragma once
#include "../D2DEngine/FiniteStateMachine.h"
class SwordManAttack : public FSMState
{
public:
	SwordManAttack(FiniteStateMachine* _fsm,std::string _name) : FSMState(_fsm, _name) {}
	virtual ~SwordManAttack() {}

	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;

};

