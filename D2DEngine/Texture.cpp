#include "pch.h"
#include "Texture.h"

Sprite::Sprite(Texture* _pTexture)
{
	m_pTexture = _pTexture;

	m_SpriteSize = m_pTexture->m_pD2DBitmap->GetSize();

	float width = m_SpriteSize.width;
	float height = m_SpriteSize.height;
	m_PivotTransform = { width / 2, height / 2 };
	m_SpriteSize = { width, height };

	m_BorderTransform = { 0, 0, width, height };

	m_Source = { 0.f, 0.f, width - 1, height - 1 };
}

Sprite::Sprite(Texture* _pTexture, D2D1_VECTOR_2F _pivot)
{
	m_pTexture = _pTexture;

	m_SpriteSize = m_pTexture->m_pD2DBitmap->GetSize();

	float width = m_SpriteSize.width;
	float height = m_SpriteSize.height;
	m_PivotTransform = _pivot;
	m_SpriteSize = { width, height };

	m_BorderTransform = { 0, 0, width, height };

	m_Source = { 0.f, 0.f, width - 1, height - 1 };
}

Sprite::Sprite(Texture* _pTexture, D2D1_VECTOR_2F _pivot, D2D1_RECT_F _Source)
{
	m_pTexture = _pTexture;

	m_SpriteSize = m_pTexture->m_pD2DBitmap->GetSize();

	float width = m_SpriteSize.width;
	float height = m_SpriteSize.height;
	m_PivotTransform = _pivot;
	m_SpriteSize = { width, height };

	m_BorderTransform = { 0, 0, width, height };

	m_Source = _Source;
}

Sprite::~Sprite()
{
}

Texture::Texture(std::wstring _Filepath, ID2D1Bitmap* _pD2DBitmap)
{
	m_Filepath = _Filepath;
	m_pD2DBitmap = _pD2DBitmap;
	//sprite = new Sprite(this);
}

Texture::~Texture()
{
	if(m_pD2DBitmap) m_pD2DBitmap->Release();
}
