#include "pch.h"
#include "TestObject.h"
#include "D2DRenderer.h"

void TestObject::Init()
{
	transform = new Transform();

	bool road = Load(m_strFileName);

	size = m_pBitmap->GetSize();

	DestPos = { 0 , 0 };//{ -size.width / 2,-size.height /2 };
	DestRect = { DestPos.x , DestPos.y, DestPos.x + size.width - 1 ,DestPos.y + size.height - 1 };

	SrcPos = { 0 , 0 };
	SrcRect = { SrcPos.x, SrcPos.y, SrcPos.x + size.width - 1, SrcPos.y + size.height - 1 };
}

void TestObject::Update()
{
}

void TestObject::Render()
{
	//D2DRenderer& render = D2DRenderer::getIncetance();
	//D2DRenderer::getIncetance().DrawBitmap(m_pBitmap, transform->m_WorldTransform);
	D2DRenderer::getRenderTarget().SetTransform(D2D1::Matrix3x2F::Identity());
	//D2DRenderer::getRenderTarget().SetTransform(D2D1::Matrix3x2F::Translation(transform->m_CenterTransform.x, transform->m_CenterTransform.y) * transform->m_WorldTransform);
	//D2DRenderer::getRenderTarget().DrawBitmap(m_pBitmap, DestRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &SrcRect);

}

void TestObject::UnInit()
{
	if(transform != nullptr) delete transform;
}

bool TestObject::Load(const WCHAR* strFileName)
{
	auto hr = D2DRenderer::getIncetance().CreateD2DBitmapFromFile(strFileName, &m_pBitmap);
	if (SUCCEEDED(hr)) {
		return true;
	}
	return false;
}
