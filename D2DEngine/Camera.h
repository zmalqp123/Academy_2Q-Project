#pragma once
#include "Component.h"
#include "AABB.h"
#include <vector>
class Camera : public Component
{
public:
	Camera() {};
	virtual ~Camera() {};

	Vector2 ScreenToWorldPosition(Vector2 position);
	Vector2 WorldToScreenPosition(Vector2 position);

	AABB GetCameraRect();
};

