#pragma once
#include "Renderer.h"
#include "EventSystem.h"
#include <functional>
#include "Collider.h"
class Texture;

class Button : virtual public Renderer, virtual public Collider, public IPointer
{
public:
	Button() {};
	virtual ~Button();

	// Renderer을(를) 통해 상속됨
	AABB GetBound() override;
	void Render(D2D1_MATRIX_3X2_F cameraMat) override;
	void Render(ID2D1HwndRenderTarget* pRenderTarget, D2D1_MATRIX_3X2_F cameraMat) override;

	// IPointer을(를) 통해 상속됨
	void IPointerEnter() override;
	void IPointerStay() override;
	void IPointerExit() override;

	Texture* m_pTexture = nullptr;

	float alpha = 1.f;

	std::wstring m_strTextureFilePath;
	D2D1_RECT_F m_SrcRect = { 0.f, 0.f };		// D2D1Bitmap의 Source 영역
	D2D1_RECT_F m_DstRect = { 0.f, 0.f };		// RenderTarget의 Destination 영역

	D2D1_MATRIX_3X2_F	m_ImageTransform;	// 반대 방향으로 뒤집기 위한 행렬 Scale.x = -1.0f 

	void LoadTexture(const std::wstring strFilePath);
	void Update(float deltaTime);

private:
	bool isMouseOn = false;
	bool isClicked = false;
	std::function<void()> events;
public:

	void OnClick();
	void OffClick();
	void AddListener(std::function<void()> func);

	// Collider을(를) 통해 상속됨
	bool isCollide(Collider* collider, Vector2& resolution) override;
	bool isCollide(const Vector2& point) override;
};

