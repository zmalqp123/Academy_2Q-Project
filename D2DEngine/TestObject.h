#pragma once
#include "Transform.h"
class TestObject
{
private:
	//std::wstring m_strFileName;
	WCHAR m_strFileName[255];
public:
	ID2D1Bitmap* m_pBitmap = nullptr;
	Transform* transform = nullptr;
	D2D1_VECTOR_2F DestPos{ 0,0 }, SrcPos{ 0,0 }; // 화면 위치, 비트맵 위치
	D2D1_SIZE_F size{ 0,0 }; //	그릴 크기
	D2D1_RECT_F DestRect{ 0,0,0,0 }, SrcRect{ 0,0,0,0 }; // 화면 영역, 비트맵 영역

	TestObject(const WCHAR* strFileName)
	{
		wcscpy_s(m_strFileName, 255, strFileName);
		Init(); 
	}
	virtual ~TestObject() {};

	void Init();
	void Update();
	void Render();
	void UnInit();

	bool Load(const WCHAR* strFileName);
};

