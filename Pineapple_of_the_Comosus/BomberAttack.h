#pragma once
#include "../D2DEngine/FiniteStateMachine.h"
class Enemy;
class BomberAttack : public FSMState
{
public:
	BomberAttack(FiniteStateMachine* _fsm,std::string _name) : FSMState(_fsm, _name) {}
	virtual ~BomberAttack() {}

	Enemy* enemy;

	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;

};

