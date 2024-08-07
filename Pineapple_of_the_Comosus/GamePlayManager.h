#pragma once
#include "../D2DEngine/Component.h"
class GamePlayManager : public Component
{
public:
	GamePlayManager() {};
	virtual ~GamePlayManager() {};

	virtual void Update(float deltaTime);
};

