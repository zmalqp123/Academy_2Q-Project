#include "pch.h"
#include "InputManager.h"

InputManager::~InputManager()
{
}

InputManager& InputManager::GetInstance()
{
	static InputManager instance;
	return instance;
}

void InputManager::InitInput(HWND _hWnd)
{
	hWnd = _hWnd;
	for (int i = 0; i < 256; i++)
	{
		isKeyDown[i] = false;
		isKeyUp[i] = false;
		isKey[i] = false;
	}
	InitMouse();
}

void InputManager::InitMouse()
{
	curMouse.wheel = 0;

	curMouse.left = false;
	curMouse.right = false;
	curMouse.middle = false;

	prevMouse = curMouse;
}

void InputManager::ResetInput()
{
	for (int i = 0; i < 256; i++)
	{
		isKeyDown[i] = false;
		isKeyUp[i] = false;
	}
}

void InputManager::KeyDown(unsigned int key)
{
	isKeyDown[key] = true;
	isKey[key] = true;
}

void InputManager::KeyUp(unsigned int key)
{
	isKeyUp[key] = true;
	isKey[key] = false;
}

void InputManager::MouseWheel(int value)
{
	curMouse.wheel = value;
}

bool InputManager::IsKeyDown(unsigned int key)
{
	return isKeyDown[key];
}

bool InputManager::IsKeyUp(unsigned int key)
{
	return isKeyUp[key];
}

bool InputManager::IsKey(unsigned int key)
{
	return isKey[key];
}

int InputManager::IsMouseWheel()
{
	return curMouse.wheel;
}

bool InputManager::IsDoubleClick()
{
	return curMouse.doubleClick;
}

void InputManager::UpdateMouse(bool isWheel, bool doubleClick)
{
	prevMouse = curMouse;

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);

	curMouse.x = pt.x;
	curMouse.y = pt.y;
	if(isWheel == false)
		curMouse.wheel = 0;
	if (doubleClick == false) {
		curMouse.doubleClick = false;
	}

	curMouse.left = (GetKeyState(VK_LBUTTON) & 0x8000) != 0;
	curMouse.right = (GetKeyState(VK_RBUTTON) & 0x8000) != 0;
	curMouse.middle = (GetKeyState(VK_MBUTTON) & 0x8000) != 0;

	//std::cout << pt.x << ", " << pt.y << std::endl;
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);

	D2D1_MATRIX_3X2_F clientToScreenMatrix =
		D2D1::Matrix3x2F::Scale(1.0f, -1.0f) *
		D2D1::Matrix3x2F::Translation(
			0,
			(clientRect.bottom - clientRect.top));

	mousePosition = {
		curMouse.x * clientToScreenMatrix._11 + curMouse.y * clientToScreenMatrix._21 + clientToScreenMatrix._31,
		curMouse.x * clientToScreenMatrix._12 + curMouse.y * clientToScreenMatrix._22 + clientToScreenMatrix._32
	};
}

bool InputManager::IsSame(const MouseState& a, const MouseState& b)
{
	return a.x == b.x && a.y == b.y && a.wheel == b.wheel && a.left == b.left && a.right == b.right && a.middle == b.middle;
}

const InputManager::MouseState& InputManager::GetMouseState()
{
	return curMouse;
}

const InputManager::MouseState& InputManager::GetPrevMouseState()
{
	return prevMouse;
}

const Vector2& InputManager::GetMousePosition()
{
	return mousePosition;
}
