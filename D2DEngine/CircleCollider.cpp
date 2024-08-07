#include "pch.h"
#include "CircleCollider.h"
#include "AABB.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "D2DRenderer.h"
#include "PublicData.h"
#include <algorithm>
bool CircleCollider::isCollide(Collider* collider, Vector2& resolution)
{
    if (collider->gameObject->isActive == false) return false;
    if (collider->GetColliderType() == ColliderType::Box) {
		D2D1_MATRIX_3X2_F circleTr = gameObject->transform->m_WorldTransform;
		D2D1_MATRIX_3X2_F rectTr = collider->gameObject->transform->m_WorldTransform;
		BoxCollider* pOtherCollider = static_cast<BoxCollider*>(collider);
		auto rectX = rectTr.dx + offset.x;
		auto rectY = rectTr.dy + offset.y;
		Vector2 otherOffset = pOtherCollider->GetOffset();
		auto circleX = circleTr.dx + otherOffset.x;
		auto circleY = circleTr.dy + otherOffset.y;

		float rectMaxX = pOtherCollider->m_Collider.GetMaxX();
		float rectMinX = pOtherCollider->m_Collider.GetMinX();
		float rectMaxY = pOtherCollider->m_Collider.GetMaxY();
		float rectMinY = pOtherCollider->m_Collider.GetMinY();
		if (circleX >= rectX + rectMinX &&
			circleX <= rectX + rectMaxX &&
			circleY >= rectY + rectMinY &&
			circleY <= rectY + rectMaxY) return true;

		// 원의 중심이 사각형의 가장자리에 있는지 확인
		float dx = circleX - std::fmaxf(rectX + rectMinX,
			std::fminf(circleX, rectX + rectMaxX));
		float dy = circleY - std::fmaxf(rectY + rectMinY,
			std::fminf(circleY, rectY + rectMaxY));

		resolution = { 0.f, 0.f };
		Vector2 delta = { dx, dy };
		float distance = delta.Length();//length(delta);
		float overlap = radius - distance;

		if (overlap > 0) {
			delta.Normalize();
			Vector2 direction = delta;
			resolution = direction * overlap;
		}

		return (dx * dx + dy * dy) <= (radius * radius);
    }
	else if (collider->GetColliderType() == ColliderType::Circle) {
		D2D1_MATRIX_3X2_F thisTr = gameObject->transform->m_WorldTransform;
		D2D1_MATRIX_3X2_F otherTr = collider->gameObject->transform->m_WorldTransform;
		CircleCollider* pOtherCollider = static_cast<CircleCollider*>(collider);
		auto thisX = thisTr.dx + offset.x;
		auto thisY = thisTr.dy + offset.y;
		Vector2 otherOffset = pOtherCollider->GetOffset();
		auto otherX = otherTr.dx + otherOffset.x;
		auto otherY = otherTr.dy + otherOffset.y;

		float dx = otherX - thisX;
		float dy = otherY - thisY;
		float dr = radius + pOtherCollider->radius;

		resolution = { 0.f, 0.f };
		Vector2 delta = { otherX - thisX, otherY - thisY };
		float distance = delta.Length();
		float overlap = (dr) - distance;

		if (overlap > 0) {
			delta.Normalize();
			Vector2 direction = delta;
			resolution = direction * overlap;
		}

		return (dx * dx + dy * dy) <= (dr * dr);
	}

    return false;
}

AABB CircleCollider::GetBound()
{
    AABB ab;
    return ab;
}

void CircleCollider::Render(D2D1_MATRIX_3X2_F cameraMat)
{
	if (gameObject->isActive == false) return;
	auto pRenderTarget = &D2DRenderer::getRenderTarget();

	D2D1_MATRIX_3X2_F m_ScreenTransform =
		D2D1::Matrix3x2F::Scale(1.0f, -1.0f) *
		D2D1::Matrix3x2F::Translation(PublicData::GetInstance().GetScreenSize().x / 2.f, PublicData::GetInstance().GetScreenSize().y / 2.f);
	D2D1_MATRIX_3X2_F Transform =
		gameObject->transform->m_WorldTransform
		* cameraMat
		* m_ScreenTransform;
	pRenderTarget->SetTransform(Transform);
	//pRenderTarget->DrawBitmap(m_pTexture->m_pD2DBitmap, m_DstRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_SrcRect);
	/*D2DRenderer::getIncetance().getRenderTarget().DrawEllipse({ D2D1::Point2F(0.f, 0.f),
	radius,
	radius }, D2DRenderer::getIncetance().g_brush);*/
	D2DRenderer::getIncetance().DrawCircle(0.f, 0.f, radius, D2D1::ColorF::Green);
}

void CircleCollider::Render(ID2D1HwndRenderTarget* pRenderTarget, D2D1_MATRIX_3X2_F cameraMat)
{
}

bool CircleCollider::isCollide(const Vector2& point)
{
	D2D1_MATRIX_3X2_F thisTr = gameObject->transform->m_WorldTransform;
	auto thisX = thisTr.dx + offset.x;
	auto thisY = thisTr.dy + offset.y;

	float dx = point.x - thisX;
	float dy = point.y - thisY;

	return (dx * dx + dy * dy) <= (radius * radius);
}
