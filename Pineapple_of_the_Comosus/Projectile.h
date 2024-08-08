#pragma once
#include "../D2DEngine/Component.h"

enum class ProjectileType
{
	Arrow,
	Bullet,
	Burst,
	Normal,
};

class Projectile : public Component
{
protected:
	ProjectileType type;

public:
	void Init() override {};
	void Update(float delta) override {};
	void Render(D2D1_MATRIX_3X2_F cameraMat) override {};

	void SetType(ProjectileType type) { this->type = type; }
	ProjectileType GetType() { return type; }
};

