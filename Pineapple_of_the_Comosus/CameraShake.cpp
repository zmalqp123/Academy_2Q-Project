#include "CameraShake.h"
#include"../D2DEngine/GameObject.h"
#include"../D2DEngine/Transform.h"
#include"../D2DEngine/GameTime.h"
#include"../D2DEngine/InputManager.h"

void CameraShake::ShakeOnCamera(bool value)
{
	shakeOn = value;
	if (value == true) {
		currentPosX = gameObject->transform->m_WorldTransform.dx;
		elapsedTime = 0.f;
	}
	else {
		gameObject->transform->pos.worldPosition.x = currentPosX;
	}
}

void CameraShake::Update(float deltaTime)
{
	if (shakeOn == true) {

		//float unScaleTime = GameTime::GetInstance().GetUnScaleDeltaTime();
		elapsedTime += deltaTime;

		//float shakeX = amplitude * std::sinf(frequency * elapsedTime * 2.0f * 3.14159f) + currentPosX; //sin파
		float shakeX = amplitude * std::fmodf(frequency * elapsedTime * 2.0f * 3.14159f, 1.f) + currentPosX; // 삼각파

		gameObject->transform->pos.worldPosition.x = shakeX;
	}

	else {
		//마우스 스크롤 기능
		if (InputManager::GetInstance().GetMousePosition().x > 0.f && InputManager::GetInstance().GetMousePosition().x < 100.f && gameObject->transform->pos.worldPosition.x > -600.f) {
			gameObject->transform->pos.worldPosition.x -= 1000.f * deltaTime;
		}

		if (InputManager::GetInstance().GetMousePosition().x < 1920.f && InputManager::GetInstance().GetMousePosition().x > 1820.f && gameObject->transform->pos.worldPosition.x < 600.f) {
			gameObject->transform->pos.worldPosition.x += 1000.f * deltaTime;
		}

		if (InputManager::GetInstance().IsKeyUp(VK_SPACE)) {
			gameObject->transform->pos.worldPosition.x = 0.f;
		}
	}
}
