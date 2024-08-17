#pragma once
#include "../D2DEngine/FiniteStateMachine.h"

class MainPineApple;
class SpriteAnimation;
class ComosusLightSelector;
class CameraShake;
class DynamicData;
class ComosusPhaseDefault : public FSMState
{
public:
	ComosusPhaseDefault(FiniteStateMachine* _fsm, std::string _name) : FSMState(_fsm, _name) {}
	virtual ~ComosusPhaseDefault() {}


	// FSMState을(를) 통해 상속됨
	void Enter() override;

	void Update(float deltaTime) override;

	void Exit() override;
};

class ComosusPhase1 : public FSMState
{
public:
	ComosusPhase1(FiniteStateMachine* _fsm, std::string _name) : FSMState(_fsm, _name) {}
	virtual ~ComosusPhase1() {}

	MainPineApple* pineApple = nullptr;
	SpriteAnimation* comosusSpriteAnim = nullptr;
	ComosusLightSelector* lightSeletor = nullptr;
	CameraShake* cameraShaker = nullptr;
	DynamicData* dynamicData = nullptr;

	float phase1Duration = 4.f;
	float fadeOutDutation = 0.f;

	// FSMState을(를) 통해 상속됨
	void Enter() override;

	void Update(float deltaTime) override;

	void Exit() override;
};

class ComosusPhase2 : public FSMState
{
public:
	ComosusPhase2(FiniteStateMachine* _fsm, std::string _name) : FSMState(_fsm, _name) {}
	virtual ~ComosusPhase2() {}

	MainPineApple* pineApple = nullptr;
	DynamicData* dynamicData = nullptr;

	float fallDuration = 0.f;
	float startY = 0.f;

	// FSMState을(를) 통해 상속됨
	void Enter() override;

	void Update(float deltaTime) override;

	void Exit() override;
};