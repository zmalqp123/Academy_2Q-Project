	#pragma once
#include "../D2DEngine/FiniteStateMachine.h"
class BomberMove : public FSMState
{
	public:
	BomberMove(FiniteStateMachine* _fsm,std::string _name) : FSMState(_fsm, _name) {}
	virtual ~BomberMove() {}

	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;
};

