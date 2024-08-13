#pragma once
#include "../D2DEngine/FiniteStateMachine.h"
class MainPineApple;
class Enemy;
class SwordManAttack : public FSMState
{
public:
	SwordManAttack(FiniteStateMachine* _fsm,std::string _name) : FSMState(_fsm, _name) {}
	virtual ~SwordManAttack() {}

	Enemy* enemy;
	MainPineApple* mainPineApple;

	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;

};

