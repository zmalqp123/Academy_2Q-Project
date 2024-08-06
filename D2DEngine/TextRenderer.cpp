#include "pch.h"
#include "TextRenderer.h"
#include "AABB.h"
#include "Transform.h"
#include "GameObject.h"
#include "ResourceManager.h"

#include "PublicData.h"

TextRenderer::TextRenderer()
{
}

TextRenderer::~TextRenderer()
{
}

void TextRenderer::Update(float deltaTime)
{
}

void TextRenderer::Render(ID2D1HwndRenderTarget* pRenderTarget, D2D1_MATRIX_3X2_F cameraMat)
{
	if (gameObject->isActive == false || (gameObject->transform->m_pParentScene != nullptr && gameObject->transform->m_pParentScene->gameObject->isActive == false))
		return;
	D2D1_MATRIX_3X2_F m_ScreenTransform =
		D2D1::Matrix3x2F::Scale(1.0f, -1.0f) *
		D2D1::Matrix3x2F::Translation(PublicData::GetInstance().GetScreenSize().x * 0.5f, PublicData::GetInstance().GetScreenSize().y * 0.5f);
	D2D1_MATRIX_3X2_F Transform =
		D2D1::Matrix3x2F::Scale(1.0f, -1.0f)
		* gameObject->transform->m_WorldTransform
		* cameraMat
		* m_ScreenTransform;
	;// * D2DRenderer::m_CameraTransform;
	pRenderTarget->SetTransform(Transform);
	D2DRenderer::getIncetance().DrawStringTextw(text.c_str(), cameraMat, D2D1::ColorF::LimeGreen);
}

void TextRenderer::Render(D2D1_MATRIX_3X2_F cameraMat)
{
	if (gameObject->isActive == false || (gameObject->transform->m_pParentScene != nullptr && gameObject->transform->m_pParentScene->gameObject->isActive == false))
		return;
	auto pRenderTarget = &D2DRenderer::getRenderTarget();

	D2D1_MATRIX_3X2_F m_ScreenTransform =
		D2D1::Matrix3x2F::Scale(1.0f, -1.0f) *
		D2D1::Matrix3x2F::Translation(PublicData::GetInstance().GetScreenSize().x / 2.f, PublicData::GetInstance().GetScreenSize().y / 2.f);
	D2D1_MATRIX_3X2_F Transform =
		D2D1::Matrix3x2F::Scale(1.0f, -1.0f)
		* gameObject->transform->m_WorldTransform
		* cameraMat
		* m_ScreenTransform;
	;// * D2DRenderer::m_CameraTransform;
	//pRenderTarget->SetTransform(Transform);
	//pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	D2DRenderer::getIncetance().DrawStringTextw(text.c_str(), D2D1::Matrix3x2F::Identity(), D2D1::ColorF::LimeGreen);
}

AABB TextRenderer::GetBound()
{
	AABB ab;
	ab.SetCenter(gameObject->transform->m_WorldTransform.dx, gameObject->transform->m_WorldTransform.dy);
	ab.SetExtent(float((m_DstRect.right - m_DstRect.left) / 2), float((m_DstRect.bottom - m_DstRect.top) / 2));

	std::cout << ab.m_Center.x << ", " << ab.m_Center.y << ", "<< ab.m_Extent.x << ", " << ab.m_Extent.y << std::endl;
	return ab;
}
