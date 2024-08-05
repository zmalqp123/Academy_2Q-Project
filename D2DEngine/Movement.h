#pragma once
#include "Component.h"
class Transform;
class Movement : public Component
{
public:
	Transform* m_pTransform = nullptr;
	D2D1_VECTOR_2F m_direction = {0.f, 0.f};
	float m_speed = 0.f;
	bool m_isInverse = false;

	void SetDirection(D2D1_VECTOR_2F direction);
	void SetSpeed(float speed);

	void virtual Init();
	void virtual Update(float delta);
};

