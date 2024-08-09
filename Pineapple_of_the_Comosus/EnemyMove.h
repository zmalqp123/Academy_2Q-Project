#pragma once
#include "../D2DEngine/FiniteStateMachine.h"
class EnemyMove : public FSMState
{
	public:
	EnemyMove(FiniteStateMachine* _fsm, std::string _name) : FSMState(_fsm, _name) {}
	virtual ~EnemyMove() {}

	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;
};

