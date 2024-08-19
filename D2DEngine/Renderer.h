#pragma once
#include "Component.h"

class AABB;
class Renderer : virtual public Component
{
public:
	Renderer() {}
	virtual ~Renderer() {}

	virtual AABB GetBound() = 0;

	virtual void Render(D2D1_MATRIX_3X2_F cameraMat) = 0;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget, D2D1_MATRIX_3X2_F cameraMat) = 0;
};

