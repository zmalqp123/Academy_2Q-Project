#pragma once
#include "Renderer.h"

class Transform;
class Texture;
class AABB;
class SpriteRenderer : public Renderer
{
	bool m_flipX = false;
	bool m_flipY = false;
public:
	SpriteRenderer();
	virtual ~SpriteRenderer();

	Texture* m_pTexture = nullptr;

	std::wstring m_strTextureFilePath;
	D2D1_RECT_F m_SrcRect = { 0.f, 0.f };		// D2D1Bitmap의 Source 영역
	D2D1_RECT_F m_DstRect = { 0.f, 0.f };		// RenderTarget의 Destination 영역

	float alpha = 1.f;

	D2D1_MATRIX_3X2_F	m_ImageTransform;	// 반대 방향으로 뒤집기 위한 행렬 Scale.x = -1.0f 

	void LoadTexture(const std::wstring strFilePath);
	void Update(float deltaTime);
	void Render(ID2D1HwndRenderTarget* pRenderTarget, D2D1_MATRIX_3X2_F cameraMat);
	void Render(D2D1_MATRIX_3X2_F cameraMat);

	AABB GetBound();

	void SetFilp(bool x, bool y);
};

