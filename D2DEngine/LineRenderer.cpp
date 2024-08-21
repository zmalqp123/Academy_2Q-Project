#include "pch.h"
#include "LineRenderer.h"
#include "AABB.h"
#include "Transform.h"
#include "GameObject.h"
#include "PublicData.h"

LineRenderer::LineRenderer()
{
	D2DRenderer::getRenderTarget().CreateSolidColorBrush(color, &color_brush);
}

LineRenderer::~LineRenderer()
{
}

void LineRenderer::Update(float deltaTime)
{
}

void LineRenderer::Render(ID2D1HwndRenderTarget* pRenderTarget, D2D1_MATRIX_3X2_F cameraMat)
{
}

void LineRenderer::Render(D2D1_MATRIX_3X2_F cameraMat)
{
	if (gameObject->isActive == false || (gameObject->transform->m_pParentScene != nullptr && gameObject->transform->m_pParentScene->gameObject->isActive == false))
		return;
	auto pRenderTarget = &D2DRenderer::getRenderTarget();

	D2D1_MATRIX_3X2_F m_ScreenTransform =
		D2D1::Matrix3x2F::Scale(1.0f, -1.0f) *
		D2D1::Matrix3x2F::Translation(PublicData::GetInstance().GetScreenSize().x * 0.5f, PublicData::GetInstance().GetScreenSize().y * 0.5f);

	D2D1_MATRIX_3X2_F Transform =
		D2D1::Matrix3x2F::Scale(1.0f, -1.0f) * m_ImageTransform
		* gameObject->transform->m_WorldTransform
		* cameraMat
		* m_ScreenTransform;

	pRenderTarget->SetTransform(Transform);

	pRenderTarget->DrawLine({ startPos.x, startPos.y }, { endPos.x, endPos.y }, color_brush, width);
}

void LineRenderer::SetColor(D2D1::ColorF color)
{
	this->color = color;
	color_brush->SetColor(color);
}

AABB LineRenderer::GetBound()
{
	AABB ab;
	ab.SetCenter(gameObject->transform->m_WorldTransform.dx, gameObject->transform->m_WorldTransform.dy);
	ab.SetExtent(float(1.f), float(1.f));

	//std::cout << ab.m_Center.x << ", " << ab.m_Center.y << ", " << ab.m_Extent.x << ", " << ab.m_Extent.y << std::endl;
	return ab;
}
