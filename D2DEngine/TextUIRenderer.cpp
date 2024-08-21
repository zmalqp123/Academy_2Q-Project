#include "pch.h"
#include "TextUIRenderer.h"
#include "D2DRenderer.h"
#include "Transform.h"
#include "GameObject.h"
#include "AABB.h"
#include "PublicData.h"

TextUIRenderer::TextUIRenderer()
{
	D2DRenderer::getRenderTarget().CreateSolidColorBrush(color, &color_brush);

	auto hr = D2DRenderer::getIncetance().g_pDWriteFactory->CreateTextFormat(
        L"Gabriola",                // 폰트 이름
        NULL,                       // 폰트 컬렉션(NULL: 기본 시스템 폰트)
        DWRITE_FONT_WEIGHT_REGULAR, // 폰트 두께
        DWRITE_FONT_STYLE_NORMAL,   // 폰트 스타일
        DWRITE_FONT_STRETCH_NORMAL, // 폰트 너비
        fontSize,                      // 폰트 크기
        L"en-us",                   // 로캘
        &pTextFormat
    );
	pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
}

TextUIRenderer::~TextUIRenderer()
{
}

void TextUIRenderer::Update(float deltaTime)
{
	/*m_DstRect.left = 0.f;
	m_DstRect.top = 0.f;
	m_DstRect.right = size.width;
	m_DstRect.bottom = size.height;
	m_SrcRect = m_DstRect;*/
	m_DstRect.left = 0.f;
	m_DstRect.top = 0.f;
	m_DstRect.right = gameObject->transform->pos.rectposition.rightTop.x - gameObject->transform->pos.rectposition.leftBottom.x;
	m_DstRect.bottom = gameObject->transform->pos.rectposition.rightTop.y - gameObject->transform->pos.rectposition.leftBottom.y;
	m_SrcRect = m_DstRect;

	m_ImageTransform = D2D1::Matrix3x2F::Scale(1.0f, 1.0f, D2D1::Point2F(0, 0)) *
		D2D1::Matrix3x2F::Translation(0.f, m_DstRect.bottom);
}

void TextUIRenderer::Render(ID2D1HwndRenderTarget* pRenderTarget, D2D1_MATRIX_3X2_F cameraMat)
{
}

void TextUIRenderer::Render(D2D1_MATRIX_3X2_F cameraMat)
{
	if (gameObject->isActive == false || (gameObject->transform->m_pParentScene != nullptr && gameObject->transform->m_pParentScene->gameObject->isActive == false))
		return;
	auto pRenderTarget = &D2DRenderer::getRenderTarget();

	D2D1_MATRIX_3X2_F m_ScreenTransform =
		D2D1::Matrix3x2F::Scale(1.0f, -1.0f) *
		D2D1::Matrix3x2F::Translation(0, PublicData::GetInstance().GetScreenSize().y);
	D2D1_MATRIX_3X2_F Transform =
		D2D1::Matrix3x2F::Scale(1.0f, -1.0f) * m_ImageTransform
		* gameObject->transform->m_WorldTransform
		* m_ScreenTransform;

	pRenderTarget->SetTransform(Transform);

	UINT32 cTextLength = (UINT32)wcslen(text.c_str());

	pRenderTarget->DrawTextW(text.c_str(), cTextLength, pTextFormat, m_DstRect, color_brush);
	//D2DRenderer::getIncetance().DrawStringTextw(text.c_str(), D2D1::Matrix3x2F::Identity(), D2D1::ColorF::LimeGreen);
	//pRenderTarget->DrawBitmap(m_pTexture->m_pD2DBitmap, dstTmp, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, srcTmp);
}

AABB TextUIRenderer::GetBound()
{
	AABB ab;
	ab.SetCenter(gameObject->transform->m_WorldTransform.dx, gameObject->transform->m_WorldTransform.dy);
	ab.SetExtent(float((m_DstRect.right - m_DstRect.left) / 2), float((m_DstRect.bottom - m_DstRect.top) / 2));
	return ab;
}

bool TextUIRenderer::isCollide(Collider* collider, Vector2& resolution)
{
	return false;
}

bool TextUIRenderer::isCollide(const Vector2& point)
{
	float x = gameObject->transform->m_WorldTransform.dx;
	float y = gameObject->transform->m_WorldTransform.dy;
	float dx = gameObject->transform->pos.rectposition.rightTop.x - gameObject->transform->pos.rectposition.leftBottom.x;
	float dy = gameObject->transform->pos.rectposition.rightTop.y - gameObject->transform->pos.rectposition.leftBottom.y;
	bool result = (x <= point.x &&
		x + dx >= point.x &&
		y <= point.y &&
		y + dy >= point.y);
	return result;
}

void TextUIRenderer::SetTextColor(D2D1::ColorF _color)
{
	color_brush->SetColor(_color);
}

void TextUIRenderer::SetFontSize(float size)
{
	fontSize = size;
	auto hr = D2DRenderer::getIncetance().g_pDWriteFactory->CreateTextFormat(
		L"Gabriola",                // 폰트 이름
		NULL,                       // 폰트 컬렉션(NULL: 기본 시스템 폰트)
		DWRITE_FONT_WEIGHT_REGULAR, // 폰트 두께
		DWRITE_FONT_STYLE_NORMAL,   // 폰트 스타일
		DWRITE_FONT_STRETCH_NORMAL, // 폰트 너비
		size,                      // 폰트 크기
		L"en-us",                   // 로캘
		&pTextFormat
	);
}

void TextUIRenderer::SetAlignCenter(int type)
{

	if (type == -1)
	{
		pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	}
	if (type == 0)
	{
		pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	}
	else if (type == 1)
	{
		pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
	}

}

bool TextUIRenderer::SetFont(LPCWSTR fontname)
{
	auto hr = D2DRenderer::getIncetance().g_pDWriteFactory->CreateTextFormat(
		fontname,                // 폰트 이름
		NULL,                       // 폰트 컬렉션(NULL: 기본 시스템 폰트)
		DWRITE_FONT_WEIGHT_REGULAR, // 폰트 두께
		DWRITE_FONT_STYLE_NORMAL,   // 폰트 스타일
		DWRITE_FONT_STRETCH_NORMAL, // 폰트 너비
		fontSize,                      // 폰트 크기
		L"ko-KR",                   // 로캘
		&pTextFormat
	);
	if (FAILED(hr))
		return false;
	else {
		return true;
	}
}
