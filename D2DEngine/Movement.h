#pragma once
#include "Component.h"
#include "Vector.h"
class Transform;
class Movement : public Component
{
public:
	Transform* m_pTransform = nullptr;
	Vector2 m_direction = {0.f, 0.f};
	float m_speed = 0.f;
	bool m_isInverse = false;

	virtual void SetDirection(Vector2 direction);
	void SetSpeed(float speed);

	void virtual Init();
	void virtual Update(float delta);
};

