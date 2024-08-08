#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/Vector.h"
class GameObject;
class Camera;
class BoxCollider;
class GamePlayManager : public Component
{
public:
	GamePlayManager() {};
	virtual ~GamePlayManager() {};

	Camera* camera;

	GameObject* dragObj = nullptr;
	bool isDrag = false;

	GameObject* selectBoxObj = nullptr;
	BoxCollider* multiSelectBox = nullptr;
	Vector2 startPos;
	bool isSelect = false;

	virtual void Update(float deltaTime);

	void StartBatch(int type);
};

