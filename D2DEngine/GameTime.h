#pragma once
class GameTime
{
private:
	GameTime() {}
	~GameTime() {}
	LARGE_INTEGER frequency;
	LARGE_INTEGER prevCounter;
	LARGE_INTEGER currentCounter;
	float deltaTime;
	float timeScale = 1.f;
public:
	static GameTime& GetInstance() {
		static GameTime instance;
		return instance;
	}
	void InitTime();
	void UpdateTime();
	float GetDeltaTime();
	float GetUnScaleDeltaTime();
	float GetFPS();

	void SetTimeScale(float value) { timeScale = value; }
};

