#pragma once
#include "Movement.h"

class SideMovement : public Movement
{
private:
    float m_gravity = 500.f;  // 중력의 세기
    float m_verticalVelocity = 0.0f; // 수직 속도
public:
    void Update(float delta) override;
    void AddForce(Vector2 velocity);
};
