#pragma once
#include "Renderer.h"
#include "Vector.h"
class Transform;
class Texture;
class AABB;
class LineRenderer : public Renderer
{
public:
	LineRenderer();
	virtual ~LineRenderer();

	float alpha = 1.f;

	Vector2 startPos = { 0.f, 0.f };
	Vector2 endPos = { 0.f, 0.f };

	float width = 1.f;

	ID2D1SolidColorBrush* color_brush = nullptr;
	D2D1::ColorF color = D2D1::ColorF::Green;
	D2D1_MATRIX_3X2_F	m_ImageTransform;

	void Update(float deltaTime);
	void Render(ID2D1HwndRenderTarget* pRenderTarget, D2D1_MATRIX_3X2_F cameraMat);
	void Render(D2D1_MATRIX_3X2_F cameraMat);
	
	void SetColor(D2D1::ColorF color);

	AABB GetBound();
};

