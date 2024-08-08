#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/Vector.h"
class GameObject;
class Camera;
class GamePlayManager : public Component
{
public:
	GamePlayManager() {};
	virtual ~GamePlayManager() {};

	Camera* camera;

	GameObject* dragObj = nullptr;
	bool isDrag = false;
	bool isAngle = false;

	virtual void Update(float deltaTime);

	void StartBatch(int type);
};

