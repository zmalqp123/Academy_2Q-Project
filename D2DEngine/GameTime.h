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

	// 복사 생성자 삭제
	GameTime(const GameTime&) = delete;

	// 복사 할당 연산자 삭제
	GameTime& operator=(const GameTime&) = delete;

	// 이동 생성자 삭제
	GameTime(GameTime&&) = delete;

	// 이동 할당 연산자 삭제
	GameTime& operator=(GameTime&&) = delete;

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

