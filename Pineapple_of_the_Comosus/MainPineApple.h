#pragma once
#include "../D2DEngine/Component.h"
class BulletFactory;
class MainPineApple : public Component
{
public:
	MainPineApple() { };
	virtual ~MainPineApple() { };

	void PrintIndex(int index);

	float elapsedTime = 0.f;
	virtual void Update(float deltaTime);

	BulletFactory* bulletFactory;
};

