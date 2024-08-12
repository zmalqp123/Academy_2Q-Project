#pragma once
#include "../D2DEngine/Component.h"
class BulletFactory;
class MainPineApple : public Component
{
	int PineAppleGold = 30000;
public:
	MainPineApple() { };
	virtual ~MainPineApple() { };

	static MainPineApple& GetInstance() {
		static MainPineApple instance;
		return instance;
	}

	void PrintIndex(int index);
	void acquireGold(int cost);
	void spendGold(int cost);

	float elapsedTime = 0.f;
	virtual void Update(float deltaTime);

	BulletFactory* bulletFactory;
};

