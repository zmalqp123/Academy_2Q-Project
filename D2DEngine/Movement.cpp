#include "pch.h"
#include "Movement.h"
#include "GameObject.h"
#include "Transform.h"
void Movement::SetDirection(D2D1_VECTOR_2F direction)
{
	m_direction = direction;
	
	//FLOAT scaleX = gameObject->transform->m_RelativeScale.x;
	//scaleX = (m_direction.x > 0 ? 1.f : m_direction.x < 0 ? -1.f : scaleX);

	//gameObject->transform->m_RelativeScale.x = scaleX;
}

void Movement::SetSpeed(float speed)
{
	m_speed = speed;
}

void Movement::Init()
{
}

void Movement::Update(float delta)
{
	float x = gameObject->transform->m_RelativeLocation.x;
	float y = gameObject->transform->m_RelativeLocation.y;
	float speedX = m_direction.x * m_speed * delta;
	float speedY = m_direction.y * m_speed * delta;
	gameObject->transform->m_RelativeLocation = { x + speedX, y + speedY };
}
