#pragma once
#include "Windows.h"
//#include "DeltaTime.h"
#include "D2DRenderer.h"

#include <d2d1.h>
//#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

#pragma comment(lib, "d2d1.lib") // Direct2D 라이브러리 링크

class WinGameApp
{
private:
	HINSTANCE hInst;
	HWND hwnd;
	//D2DRenderer& render;

	//DeltaTime deltaTime;
public:

	// 자식 클래스가 재정의 가능하도록 virtual keyword 를 붙인다.
	virtual void Initialize(HINSTANCE hInstance, int nCmdShow, float x, float y);
	void Run();
	virtual void FixedUpdate();
	virtual void Update(float deltaTime);
	virtual void LateUpdate();
	virtual void Render(D2DRenderer* _render);
	virtual void Uninitialize();
};

