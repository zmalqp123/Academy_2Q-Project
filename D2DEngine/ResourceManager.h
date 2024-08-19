#pragma once
#include "Object.h"
#include <map>
class SpriteAnimationAsset;
class Texture;
class Sprite;

class ResourceManager : public Object
{
private:
	ResourceManager();
	~ResourceManager();
public:

	std::map<std::wstring, ID2D1Bitmap*> m_BitmapMap;
	std::map<std::wstring, Texture*> m_TextureMap;
	std::map<unsigned int, Sprite*> m_SpriteMap;
	std::map<std::wstring, SpriteAnimationAsset*> m_AnimationAssetMap;

	static ResourceManager& GetInstance() {
		static ResourceManager instance;
		return instance;
	}

	bool CreateD2DBitmapFromFile(std::wstring strFilePath, ID2D1Bitmap** bitmap);
	void ReleaseD2DBitmap(std::wstring strFilePath);

	bool CreateTextureFromFile(std::wstring strFilePath, Texture** texture);
	void ReleaseTexture(std::wstring strFilePath);

	bool CreateSpriteFromFile(std::wstring strFilePath, Sprite** sprite);

	bool CreateAnimationAsset(std::wstring strFilePath, SpriteAnimationAsset** asset);
	void ReleaseAnimationAsset(std::wstring strFilePath);
};

