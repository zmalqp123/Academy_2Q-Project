#include "MouseDownTest.h"
#include"../D2DEngine/InputManager.h"
#include <iostream>
void MouseDownTest::Init()
{
}

void MouseDownTest::Update(float delta)
{
	bool a = InputManager::GetInstance().IsDoubleClick();
	if (a == false) return;
	std::cout << a << std::endl;
}

void MouseDownTest::Render(D2D1_MATRIX_3X2_F cameraMat)
{
}

void MouseDownTest::OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void MouseDownTest::OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void MouseDownTest::OnStayOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void MouseDownTest::OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}
