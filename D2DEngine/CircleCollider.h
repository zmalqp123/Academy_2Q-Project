#pragma once
#include "Collider.h"
#include "Renderer.h"
class CircleCollider : public Collider, public Renderer
{
	friend class BoxCollider;
protected:
	float radius;

public:
	CircleCollider(CollisionType cType = BLOCK) {
		m_ColliderType = ColliderType::Circle;
		m_CollisionType = cType;
	}

	// Collider을(를) 통해 상속됨
	bool isCollide(Collider* collider, Vector2& resolution) override;

	float GetRadius() { return radius; }
	void SetRadius(float _radius) { radius = _radius; }

	// Renderer을(를) 통해 상속됨
	AABB GetBound() override;
	void Render(D2D1_MATRIX_3X2_F cameraMat) override;
	void Render(ID2D1HwndRenderTarget* pRenderTarget, D2D1_MATRIX_3X2_F cameraMat) override;

	// Collider을(를) 통해 상속됨
	bool isCollide(const Vector2& point) override;
};

