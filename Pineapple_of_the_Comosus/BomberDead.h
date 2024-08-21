#pragma once
#include "../D2DEngine/FiniteStateMachine.h"

#include "EnemyDead.h"
class SpriteAnimation;
class BomberDead : public EnemyDead
{
public:
	BomberDead(FiniteStateMachine* _fsm, std::string _name) : EnemyDead(_fsm, _name) {}
	virtual ~BomberDead() {}

	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;

	SpriteAnimation* BomberDeadAnim = nullptr;
};

