#pragma once
class DeltaTime
{
private:
	LARGE_INTEGER frequency;
	LARGE_INTEGER prevCounter;
	LARGE_INTEGER currentCounter;
	float deltaTime;
public:
	void InitTime();
	void UpdateTime();
	float GetDeltaTime();
	float GetFPS();
};

