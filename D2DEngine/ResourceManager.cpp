#include "pch.h"
#include "ResourceManager.h"
#include "SpriteAnimationAsset.h"
#include "Texture.h"
#include "Sprite.h"
#include "D2DRenderer.h"

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
	for (auto& m : m_TextureMap) {
		m.second->Release();
	}
	for (auto& m : m_AnimationAssetMap) {
		m.second->Release();
	}

	m_TextureMap.clear();
	m_AnimationAssetMap.clear();

	assert(m_BitmapMap.empty());
	assert(m_TextureMap.empty());	// map안에 값들 release안해서 그러니 나중에 해결해야함.
	assert(m_SpriteMap.empty());
	assert(m_AnimationAssetMap.empty());
}

bool ResourceManager::CreateD2DBitmapFromFile(std::wstring strFilePath, ID2D1Bitmap** bitmap)
{
	if (m_BitmapMap.find(strFilePath) != m_BitmapMap.end())
	{
		*bitmap = m_BitmapMap[strFilePath];
		(*bitmap)->AddRef();
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	// 기존과 같은 생성로직. D2D1Bitmap 생성하여 인터페이스 포인터 받는다.
	// 여기서는 생략한다.

	D2DRenderer::getIncetance().CreateD2DBitmapFromFile(strFilePath.c_str(), bitmap);

	// 생성한 비트맵을 맵에 저장한다.
	m_BitmapMap[strFilePath] = *bitmap;
	return true;
}

void ResourceManager::ReleaseD2DBitmap(std::wstring strFilePath)
{
	// 맵에 해당 키가 존재하면 비트맵을 해제한다.
	std::map<std::wstring, ID2D1Bitmap*>::iterator iter = m_BitmapMap.find(strFilePath);
	assert(iter != m_BitmapMap.end()); // 컨테이너에 없으면 Create/Release 짝이 잘못됐다.

	if (iter != m_BitmapMap.end())
	{
		ID2D1Bitmap* bitmap = m_BitmapMap[strFilePath];
		if (bitmap->Release() == 0)
		{
			m_BitmapMap.erase(iter);
		}
	}
}

bool ResourceManager::CreateTextureFromFile(std::wstring strFilePath, Texture** texture)
{
	if (m_TextureMap.find(strFilePath) != m_TextureMap.end())
	{
		*texture = m_TextureMap[strFilePath];
		(*texture)->AddRef();
		return true;
	}

	ID2D1Bitmap* temp = nullptr;
	auto hr = D2DRenderer::getIncetance().CreateD2DBitmapFromFile(strFilePath.c_str(), &temp);
	if (FAILED(hr)) 
		return false;
	else
		*texture = new Texture(strFilePath, temp);

	m_TextureMap[strFilePath] = *texture;
	return true;
}

void ResourceManager::ReleaseTexture(std::wstring strFilePath)
{
	std::map<std::wstring, Texture*>::iterator iter = m_TextureMap.find(strFilePath);
	assert(iter != m_TextureMap.end()); // 컨테이너에 없으면 Create/Release 짝이 잘못됐다.

	if (iter != m_TextureMap.end())
	{
		Texture* texture = m_TextureMap[strFilePath];
		if (texture->Release() == 0)
		{
			m_TextureMap.erase(iter);
		}
	}
}

bool ResourceManager::CreateSpriteFromFile(std::wstring strFilePath, Sprite** sprite)
{
	return false;
}

bool ResourceManager::CreateAnimationAsset(std::wstring strFilePath, SpriteAnimationAsset** asset)
{
	if (m_AnimationAssetMap.find(strFilePath) != m_AnimationAssetMap.end())
	{
		*asset = m_AnimationAssetMap[strFilePath];
		(*asset)->AddRef();
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	// 기존과 같은 생성로직. AnimationAsset 생성하여 인터페이스 포인터 받는다.
	// 여기서는 생략한다.

	SpriteAnimationAsset* pTemp = new SpriteAnimationAsset;
	// 생성한 애니메이션 에셋에 애니메이션 데이터를 로드한다.
	if (pTemp->LoadAnimation(strFilePath) == false)
	{
		delete pTemp;
		return false;
	}
	else
	{
		*asset = pTemp;
	}
	// 생성한 애니메이션 에셋을 맵에 저장한다.
	m_AnimationAssetMap[strFilePath] = *asset;
	return true;
}

void ResourceManager::ReleaseAnimationAsset(std::wstring strFilePath)
{
	// 맵에 해당 키가 존재하면 애니메이션 에셋을 해제한다.
	std::map<std::wstring, SpriteAnimationAsset*>::iterator iter = m_AnimationAssetMap.find(strFilePath);
	assert(iter != m_AnimationAssetMap.end()); // 컨테이너에 없으면 Create/Release 짝이 잘못됐다.

	if (iter != m_AnimationAssetMap.end())
	{
		SpriteAnimationAsset* asset = m_AnimationAssetMap[strFilePath];
		if (asset->Release() == 0)
		{
			m_AnimationAssetMap.erase(iter);
		}
	}
}
