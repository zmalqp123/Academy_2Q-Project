#include "pch.h"
#include "Camera.h"
#include "Transform.h"
#include "GameObject.h"
#include "InputManager.h"
#include "PublicData.h"

Vector2 Camera::ScreenToWorldPosition(Vector2 position)
{
	// 스크린좌표를 화면 중심을 기준으로 변경
	Vector2 screenSize = PublicData::GetInstance().GetScreenSize();
	position.x -= screenSize.x / 2.f;
	position.y -= screenSize.y / 2.f;
	

	Vector2 mousePosition = {
		position.x * gameObject->transform->m_WorldTransform._11 + position.y * gameObject->transform->m_WorldTransform._21 + gameObject->transform->m_WorldTransform._31,
		position.x * gameObject->transform->m_WorldTransform._12 + position.y * gameObject->transform->m_WorldTransform._22 + gameObject->transform->m_WorldTransform._32
	};
	return mousePosition;
}

Vector2 Camera::WorldToScreenPosition(Vector2 position)
{
	return Vector2();
}

AABB Camera::GetCameraRect()
{
	D2D1_MATRIX_3X2_F c = gameObject->transform->m_WorldTransform;
	Vector2 extent = PublicData::GetInstance().GetScreenSize() / 2.f;//{ 640.f, 360.f };
	Vector2 centerPos = {
		c.m[2][0],
		c.m[2][1]
	};
	Vector2 extentPos = {
		c.m[0][0] * extent.x + c.m[1][0] * extent.y,
		c.m[0][1] * extent.x + c.m[1][1] * extent.y
	};

	AABB camAABB;
	camAABB.m_Center = centerPos;
	camAABB.m_Extent = extentPos;

	return camAABB;
}
