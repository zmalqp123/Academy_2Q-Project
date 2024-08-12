#pragma once
#include "Renderer.h"
#include "Vector.h"
class Transform;
class Texture;
class AABB;
class SpriteRenderer : public Renderer
{
	bool m_flipX = false;
	bool m_flipY = false;
	Vector2 centerPos = { 0.5f, 0.5f };
public:
	SpriteRenderer();
	virtual ~SpriteRenderer();

	Texture* m_pTexture = nullptr;

	std::wstring m_strTextureFilePath;
	D2D1_RECT_F m_SrcRect = { 0.f, 0.f };	
	D2D1_RECT_F m_DstRect = { 0.f, 0.f };		

	float alpha = 1.f;

	D2D1_MATRIX_3X2_F	m_ImageTransform;	

	void LoadTexture(const std::wstring strFilePath);
	void Update(float deltaTime);
	void Render(ID2D1HwndRenderTarget* pRenderTarget, D2D1_MATRIX_3X2_F cameraMat);
	void Render(D2D1_MATRIX_3X2_F cameraMat);

	AABB GetBound();

	void SetFilp(bool x, bool y);

	//loadTexture를 하기 전에 사용할 것
	void SetCenter(Vector2 normalize);
};

