#include "pch.h"
#include "SideMovement.h"
#include "GameObject.h"
#include "Transform.h"

void SideMovement::Update(float delta)
{
    prevPosition = gameObject->transform->pos.worldPosition;

    // 현재 위치 가져오기
    float x = gameObject->transform->pos.worldPosition.x;
    float y = gameObject->transform->pos.worldPosition.y;

    // 수평 이동 계산
    float speedX = m_direction.x * m_speed * delta;

    // 수직 속도 업데이트 (중력 적용)
    m_verticalVelocity -= m_gravity * delta;
    y += m_verticalVelocity * delta;

    //std::cout << "m_verticalVelocity : " << m_verticalVelocity << std::endl;
    // 새 위치 적용
    gameObject->transform->pos.worldPosition = { x + speedX, y };

    if (freezeRotate == false) {
        Vector2 currPos = { x + speedX, y };

        Vector2 dir = currPos - prevPosition;
        dir.Normalize();
        float x1 = 1.f;
        float y1 = 0.f;
        float e = atan2f(x1 * dir.y - y1 * dir.x, x1 * dir.x + y1 * dir.y) / 3.14159f * 180.f;
        gameObject->transform->m_RelativeRotation = e;
    }
}

void SideMovement::AddForce(Vector2 velocity)
{
    m_verticalVelocity = velocity.y;

    float movespeed = velocity.Length();
    m_speed = movespeed;
    velocity.Normalize();
    m_direction = velocity;
}
