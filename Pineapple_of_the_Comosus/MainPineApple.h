#pragma once
#include "../D2DEngine/Component.h"
class BulletFactory;
class MainPineApple : public Component
{
	int PineAppleGold = 30000;
public:
	MainPineApple() { };
	virtual ~MainPineApple() { };

	void PrintIndex(int index);
	void acquireGold(int cost);
	void spendGold(int cost);
	int GetPineAppleGold() { return PineAppleGold; }

	float elapsedTime = 0.f;
	virtual void Update(float deltaTime);

	BulletFactory* bulletFactory;
};

