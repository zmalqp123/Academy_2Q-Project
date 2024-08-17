#pragma once
#include "../D2DEngine/Component.h"
class CameraShake : public Component
{
	bool shakeOn = false;
	float currentPosX = 0.f;
	float elapsedTime = 0.f;

	float amplitude = 10.f;
	float frequency = 2.f;
public:
	CameraShake() {};
	virtual ~CameraShake() {};
	
	void ShakeOnCamera(bool value);
	void SetAmplitude(float value) { amplitude = value; }
	void SetFrequency(float value) { frequency = value; }
	virtual void Update(float deltaTime);
};

