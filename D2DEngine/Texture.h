#pragma once
#include "Object.h"


// 텍스쳐는 이미지의 원본을 가지고 있다가
// sprite가 텍스처를 참조한 뒤
// center, scale, rotate 등의 변경사항을 sprite가 가지고 있다가
// 그 값을 오브젝트가 참조해서 사용하는 방식으로 예정

// texture, sprite는 referenceCounter를 참조받는다.
// ex) texture를 기반으로 sprite를 여러개로 쪼개어 저장했다가
// 애니메이션에서 sprite를 배열에 담아 사용하는 방식으로.

// 타입을 single, multiple로 구분하고
class Texture;
class Sprite : public Object
{
	// 이름
	std::wstring m_Name;

	// 비트맵
	Texture* m_pTexture = nullptr;

	// 이미지의 pivot좌표
	D2D1_VECTOR_2F		m_PivotTransform;

	// 이미지의 border좌표
	D2D1_VECTOR_4F		m_BorderTransform;

	// 이미지의 크기		ex) 시작좌표 (0, 0), 끝좌표 (width - 1, height - 1)
	D2D1_SIZE_F			m_SpriteSize;

	// 이미지에서 그릴 영역
	D2D1_RECT_F			m_Source;

	Sprite(Texture* _pTexture);
	Sprite(Texture* _pTexture, D2D1_VECTOR_2F _pivot);
	Sprite(Texture* _pTexture, D2D1_VECTOR_2F _pivot, D2D1_RECT_F _Source);
	virtual ~Sprite();
};

class Texture : public Object
{
public:
	// 0 = Default, 1 = Sprite 
	Texture(std::wstring _Filepath, ID2D1Bitmap* _pD2DBitmap);
	virtual ~Texture();

	std::wstring m_Filepath;
	ID2D1Bitmap* m_pD2DBitmap = nullptr;

	Sprite* sprite = nullptr;
	std::vector<Sprite*> multipleSprite;
};

