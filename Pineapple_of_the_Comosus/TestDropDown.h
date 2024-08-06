#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/Vector.h"
class GameObject;
class Camera;
class TestDropDown : public Component
{
public:
	Camera* camera;

	GameObject* dragObj;
	Vector2 offset;
	bool isDrag = false;
	virtual void Update(float delta);
};

