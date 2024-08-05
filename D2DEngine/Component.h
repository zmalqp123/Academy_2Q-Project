#pragma once
#include "Object.h"
#include "D2DRenderer.h"
class GameObject;
class Component : public Object
{
public:
	GameObject* gameObject = nullptr;
	Component() {}
	virtual ~Component() {};

	void SetOwner(GameObject* _gameObject);
	void virtual Init() {};
	void virtual Update(float delta) {};
	void virtual Render(D2D1_MATRIX_3X2_F cameraMat) {};
};

