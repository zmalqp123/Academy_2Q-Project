#pragma once
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/Vector.h"
class MainPineApple;
class Enemy;
class EnemyDead : public FSMState
{	
	public:
	EnemyDead(FiniteStateMachine* _fsm, std::string _name) : FSMState(_fsm, _name) {}
	virtual ~EnemyDead() {}
	Enemy* enemy;
	MainPineApple* mainPineApple;

	void Enter() override;
	void Update(float deltaTime) override;
	void Exit() override;
	void Spin(float deltaTime);

	void GriffinDie(float deltaTime);
	void BossDie(float deltaTime);
	bool isSpined = false;
	Vector2 dieDir = { 0.f, 0.f };
	float bossElapsedTime = 0.f;
	float bossCurPosX = 0.f;
};

