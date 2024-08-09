#include "pch.h"
#include "SideMovement.h"
#include "GameObject.h"
#include "Transform.h"

void SideMovement::Update(float delta)
{
    // 현재 위치 가져오기
    float x = gameObject->transform->pos.worldPosition.x;
    float y = gameObject->transform->pos.worldPosition.y;

    // 수평 이동 계산
    float speedX = m_direction.x * m_speed * delta;

    // 수직 속도 업데이트 (중력 적용)
    m_verticalVelocity += m_gravity * delta;
    y -= m_verticalVelocity * delta;

    // 새 위치 적용
    gameObject->transform->pos.worldPosition = { x + speedX, y };
}
