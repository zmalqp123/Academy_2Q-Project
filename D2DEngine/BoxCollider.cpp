#include "pch.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "D2DRenderer.h"
#include "PublicData.h"
#include "CircleCollider.h"
#include <algorithm>
bool BoxCollider::isCollide(Collider* collider, Vector2& resolution)
{
	if (collider->gameObject->isActive == false) return false;
    if (collider->GetColliderType() == ColliderType::Box) {
		D2D1_MATRIX_3X2_F c = gameObject->transform->m_WorldTransform;

		AABB owner;
		owner.m_Center = {
			c.m[2][0] + m_Collider.m_Center.x + offset.x,
			c.m[2][1] + m_Collider.m_Center.y + offset.y
		};
		owner.m_Extent = {
			abs(c.m[0][0] * m_Collider.m_Extent.x + c.m[1][0] * m_Collider.m_Extent.y),
			abs(c.m[0][1] * m_Collider.m_Extent.x + c.m[1][1] * m_Collider.m_Extent.y)
		};

        BoxCollider* pOtherCollider = static_cast<BoxCollider*>(collider);
		D2D1_MATRIX_3X2_F c1 = pOtherCollider->gameObject->transform->m_WorldTransform;
		AABB other;
		other.m_Center = {
			c1.m[2][0] + pOtherCollider->offset.x + pOtherCollider->m_Collider.m_Center.x,
			c1.m[2][1] + pOtherCollider->offset.y + pOtherCollider->m_Collider.m_Center.y
		};
		other.m_Extent = {
			abs(c1.m[0][0] * pOtherCollider->m_Collider.m_Extent.x + c1.m[1][0] * pOtherCollider->m_Collider.m_Extent.y),
			abs(c1.m[0][1] * pOtherCollider->m_Collider.m_Extent.x + c1.m[1][1] * pOtherCollider->m_Collider.m_Extent.y)
		};

        if (!owner.CheckIntersect(other, resolution))
            return false;
        return true;
		/*if (!m_Collider.CheckIntersect(pOtherCollider->m_Collider))
            return false;
        return true;*/
    }
	else if (collider->GetColliderType() == ColliderType::Circle) {
		D2D1_MATRIX_3X2_F rectTr = gameObject->transform->m_WorldTransform;
		D2D1_MATRIX_3X2_F circleTr = collider->gameObject->transform->m_WorldTransform;
		CircleCollider* pOtherCollider = static_cast<CircleCollider*>(collider);
		auto rectX = rectTr.dx + offset.x;
		auto rectY = rectTr.dy + offset.y;
		Vector2 otherOffset = pOtherCollider->GetOffset();
		auto circleX = circleTr.dx + otherOffset.x;
		auto circleY = circleTr.dy + otherOffset.y;
		float rectMaxX = m_Collider.GetMaxX();
		float rectMinX = m_Collider.GetMinX();
		float rectMaxY = m_Collider.GetMaxY();
		float rectMinY = m_Collider.GetMinY();
		if (circleX >= rectX + rectMinX &&
			circleX <= rectX + rectMaxX &&
			circleY >= rectY + rectMinY &&
			circleY <= rectY + rectMaxY) return true;

		// 원의 중심이 사각형의 가장자리에 있는지 확인
		float dx = circleX - std::fmaxf(rectX + rectMinX,
			std::fminf(circleX, rectX + rectMaxX));
		float dy = circleY - std::fmaxf(rectY + rectMinY,
			std::fminf(circleY, rectY + rectMaxY));
		float radius = pOtherCollider->GetRadius();

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
    return false;
}

void BoxCollider::Render(D2D1_MATRIX_3X2_F cameraMat)
{
//#ifdef DEBUG
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
	D2DRenderer::getIncetance().DrawHollowRectangle(
		m_Collider.GetMinX() + offset.x,
		m_Collider.GetMinY() + offset.y,
		m_Collider.GetMaxX() + offset.x,
		m_Collider.GetMaxY() + offset.y,
		2.f,
		D2D1::ColorF::LimeGreen		
	);
//#endif
}



void BoxCollider::SetOffset(const Vector2& _offset)
{
	offset = _offset;
}

void BoxCollider::SetCenter(const Vector2& _center)
{
	m_Collider.m_Center = _center;
}

void BoxCollider::SetExtent(const Vector2& _extent)
{
	m_Collider.m_Extent = _extent;
}


//collider에 render붙이는거 테스트 중.
AABB BoxCollider::GetBound()
{
	AABB ab;
	ab.SetCenter(
		gameObject->transform->m_WorldTransform.dx + m_Collider.m_Center.x, 
		gameObject->transform->m_WorldTransform.dy + m_Collider.m_Center.y);
	ab.SetExtent(m_Collider.m_Extent.x, m_Collider.m_Extent.y);
	return ab;
}

void BoxCollider::Render(ID2D1HwndRenderTarget* pRenderTarget, D2D1_MATRIX_3X2_F cameraMat)
{
	//if (gameObject->isActive == false) return;

	//D2D1_MATRIX_3X2_F m_ScreenTransform =
	//	D2D1::Matrix3x2F::Scale(1.0f, -1.0f) *
	//	D2D1::Matrix3x2F::Translation(PublicData::GetInstance().GetScreenSize().x * 0.5f, PublicData::GetInstance().GetScreenSize().y * 0.5f);
	//D2D1_MATRIX_3X2_F Transform =
	//	gameObject->transform->m_WorldTransform
	//	* cameraMat
	//	* m_ScreenTransform;
	//pRenderTarget->SetTransform(Transform);
	////pRenderTarget->DrawBitmap(m_pTexture->m_pD2DBitmap, m_DstRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_SrcRect);
	//D2DRenderer::getIncetance().DrawHollowRectangle(
	//	m_Collider.GetMinX() + m_Collider.m_Center.x + offset.x,
	//	m_Collider.GetMinY() + m_Collider.m_Center.y + offset.y,
	//	m_Collider.GetMaxX() + m_Collider.m_Center.x + offset.x,
	//	m_Collider.GetMaxY() + m_Collider.m_Center.y + offset.y,
	//	2.f,
	//	D2D1::ColorF::LimeGreen
	//);
}

bool BoxCollider::isCollide(const Vector2& point)
{
	D2D1_MATRIX_3X2_F rectTr = gameObject->transform->m_WorldTransform;
	auto rectX = rectTr.dx + offset.x;
	auto rectY = rectTr.dy + offset.y;
	float rectMaxX = m_Collider.GetMaxX();
	float rectMinX = m_Collider.GetMinX();
	float rectMaxY = m_Collider.GetMaxY();
	float rectMinY = m_Collider.GetMinY();

	bool isCollide = rectMaxX >= point.x && rectMinX <= point.x && rectMaxY >= point.y && rectMinY <= point.y;

	return isCollide;
}
