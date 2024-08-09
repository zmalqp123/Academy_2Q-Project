#include "pch.h"
#include "SideMovement.h"
#include "GameObject.h"
#include "Transform.h"

void SideMovement::Update(float delta)
{
    // 중력 효과를 무시한 측면 이동 처리
    float x = gameObject->transform->pos.worldPosition.x;
    float y = gameObject->transform->pos.worldPosition.y;

    // Y축 이동을 제거하여 수평(측면) 이동만 처리
    float speedX = m_direction.x * m_speed * delta;

    gameObject->transform->pos.worldPosition = { x + speedX, y };
}
