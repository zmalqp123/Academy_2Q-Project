#pragma once
#include "Component.h"
#include "Vector.h"
class Rigidbody2D : public Component
{
public:
	Vector2 force;
	float mass;

	void virtual Init() {};
	void virtual Update(float delta);
	void virtual Render(D2D1_MATRIX_3X2_F cameraMat) {};

	void ApplyForce(const Vector2& f);

};

