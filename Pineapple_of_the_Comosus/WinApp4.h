#pragma once
#include "../D2DEngine/WinGameApp.h"
class Scene;
class WinApp4 : public WinGameApp
{
public:
	Scene* scene;
	//  virtual 만 사용해도 되지만
	// override를 keyword를 사용하므로써 가상함수 "재정의" 라는것을 확실히한다.
	// 부모 클래스의 함수가 virtual 이 아니면 컴파일 에러.
	virtual void Initialize(HINSTANCE hInstance, int nCmdShow, float x, float y);

	//virtual void Run();

	virtual void Update(float deltaTime);

	virtual void Render(D2DRenderer* _render);

	virtual void Uninitialize();
};
