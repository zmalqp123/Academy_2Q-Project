#include "pch.h"
#include "SpriteRenderer.h"
#include "AABB.h"
#include "Transform.h"
#include "GameObject.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "PublicData.h"

SpriteRenderer::SpriteRenderer()
{
}

SpriteRenderer::~SpriteRenderer() {
	if (m_pTexture) {
		ResourceManager::GetInstance().ReleaseAnimationAsset(m_strTextureFilePath);
		m_pTexture = nullptr;
	}
}

void SpriteRenderer::LoadTexture(const std::wstring strFilePath)
{
	m_strTextureFilePath = strFilePath;

	if (ResourceManager::GetInstance().CreateTextureFromFile(m_strTextureFilePath, &m_pTexture))
	{
		auto size = m_pTexture->m_pD2DBitmap->GetSize();
		m_DstRect.left = 0.f;
		m_DstRect.top = 0.f;
		m_DstRect.right = size.width;
		m_DstRect.bottom = size.height;
		m_SrcRect = m_DstRect;

	/*	if (m_flipX == false) {
			m_ImageTransform = D2D1::Matrix3x2F::Scale(1.0f, 1.0f, D2D1::Point2F(0, 0)) *
				D2D1::Matrix3x2F::Translation(-size.width / 2.f, size.height / 2.f);
		}
		else {
			m_ImageTransform = D2D1::Matrix3x2F::Scale(-1.0f, 1.0f, D2D1::Point2F(0, 0)) *
				D2D1::Matrix3x2F::Translation(size.width / 2.f, size.height / 2.f);
		}*/

		m_ImageTransform = D2D1::Matrix3x2F::Scale(m_flipX ? -1.f : 1.f, m_flipY ? -1.f : 1.f, D2D1::Point2F(0, 0)) *
			D2D1::Matrix3x2F::Translation(m_flipX ? size.width / 2.f : -size.width / 2.f, m_flipY ? -size.width / 2.f : size.height / 2.f);
	}
}

void SpriteRenderer::Update(float deltaTime)
{
}

void SpriteRenderer::Render(ID2D1HwndRenderTarget* pRenderTarget, D2D1_MATRIX_3X2_F cameraMat)
{
	if (gameObject->isActive == false || (gameObject->transform->m_pParentScene != nullptr && gameObject->transform->m_pParentScene->gameObject->isActive == false))
		return;
	D2D1_MATRIX_3X2_F m_ScreenTransform =
		D2D1::Matrix3x2F::Scale(1.0f, -1.0f) *
		D2D1::Matrix3x2F::Translation(PublicData::GetInstance().GetScreenSize().x * 0.5f, PublicData::GetInstance().GetScreenSize().y * 0.5f);
	D2D1_MATRIX_3X2_F Transform =
		D2D1::Matrix3x2F::Scale(1.0f, -1.0f) * m_ImageTransform
		* gameObject->transform->m_WorldTransform
		* cameraMat
		* m_ScreenTransform;
	;// * D2DRenderer::m_CameraTransform;
	pRenderTarget->SetTransform(Transform);
	if (m_pTexture == nullptr) return;
	pRenderTarget->DrawBitmap(m_pTexture->m_pD2DBitmap, m_DstRect, alpha, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, m_SrcRect);
}

void SpriteRenderer::Render(D2D1_MATRIX_3X2_F cameraMat)
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
	;// * D2DRenderer::m_CameraTransform;
	pRenderTarget->SetTransform(Transform);
	if (m_pTexture == nullptr) return;
	pRenderTarget->DrawBitmap(m_pTexture->m_pD2DBitmap, m_DstRect, alpha, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, m_SrcRect);
}

AABB SpriteRenderer::GetBound()
{
	AABB ab;
	ab.SetCenter(gameObject->transform->m_WorldTransform.dx, gameObject->transform->m_WorldTransform.dy);
	ab.SetExtent(float((m_DstRect.right - m_DstRect.left) / 2), float((m_DstRect.bottom - m_DstRect.top) / 2));
	return ab;
}

void SpriteRenderer::SetFilp(bool x, bool y)
{
	m_flipX = x;
	m_flipY = y;
	auto size = m_pTexture->m_pD2DBitmap->GetSize();
	m_DstRect.left = 0.f;
	m_DstRect.top = 0.f;
	m_DstRect.right = size.width;
	m_DstRect.bottom = size.height;
	m_SrcRect = m_DstRect;

	m_ImageTransform = D2D1::Matrix3x2F::Scale(m_flipX ? -1.f : 1.f, m_flipY ? -1.f : 1.f, D2D1::Point2F(0, 0)) *
		D2D1::Matrix3x2F::Translation(m_flipX ? size.width / 2.f : -size.width / 2.f, m_flipY ? -size.width / 2.f : size.height / 2.f);
}
