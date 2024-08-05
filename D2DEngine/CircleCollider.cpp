#include "pch.h"
#include "CircleCollider.h"
#include "AABB.h"
bool CircleCollider::isCollide(Collider* collider, Vector2& resolution)
{


    return false;
}

AABB CircleCollider::GetBound()
{
    AABB ab;
    return ab;
}

void CircleCollider::Render(D2D1_MATRIX_3X2_F cameraMat)
{
}

void CircleCollider::Render(ID2D1HwndRenderTarget* pRenderTarget, D2D1_MATRIX_3X2_F cameraMat)
{
}
