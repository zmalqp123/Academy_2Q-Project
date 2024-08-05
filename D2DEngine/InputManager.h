#pragma once
#include "Vector.h"
class InputManager
{
private:
	InputManager() {};
	~InputManager();
public:
	static InputManager& GetInstance();

	void InitInput(HWND _hWnd);
	void InitMouse();
	void ResetInput();
	void KeyDown(unsigned int key);
	void KeyUp(unsigned int key);
	void MouseWheel(int value);
	bool IsKeyDown(unsigned int key);
	bool IsKeyUp(unsigned int key);
	bool IsKey(unsigned int key);
	int IsMouseWheel();
	struct MouseState
	{
		MouseState()
		{
			x = 0;
			y = 0;
			wheel = 0;
			left = false;
			right = false;
			middle = false;
		}

		int x;
		int y;
		int wheel;
		bool left;
		bool right;
		bool middle;
	};

	void UpdateMouse(bool isWheel = false);

	bool IsSame(const MouseState& a, const MouseState& b);

	const MouseState& GetMouseState();
	const MouseState& GetPrevMouseState();
	const Vector2& GetMousePosition(); // 스크린 좌표를 리턴 Left - Bottom = (0,0)
private:
	HWND hWnd;

	bool isKeyDown[256];
	bool isKeyUp[256];
	bool isKey[256];

	MouseState curMouse;
	MouseState prevMouse;

	Vector2 mousePosition;

	int length = 0;
	bool isInputKey = false;
};

