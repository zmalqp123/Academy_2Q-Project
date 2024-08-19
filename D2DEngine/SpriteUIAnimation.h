#pragma once
#include "Renderer.h"

class SpriteAnimationAsset;
struct ANIMATION_INFO;
class Transform;
class Texture;
class AABB;
class SpriteUIAnimation : public Renderer
{
public:
	SpriteUIAnimation();
	virtual ~SpriteUIAnimation();

	// 공유하는 애니메이션 정보	
	SpriteAnimationAsset* m_pAnimationAsset = nullptr;  // 공유하는 애니메이션 정보

	// 인스턴스마다 다른 애니메이션 정보
	ANIMATION_INFO* m_pAnimationInfo = nullptr;	// 현재 애니메이션 프레임 정보
	std::wstring m_strAnimationAssetFilePath;    // 애니메이션 정보 파일 이름
	std::wstring m_strTextureFilePath;

	float m_FrameTime = 0.0f;	// 프레임 진행시간
	int m_FrameIndexCurr = -1;	// 현재 프레임 인덱스
	int m_FrameIndexPrev = -1;	// 이전 프레임 인덱스
	int m_AnimationIndex = -1;	// 현재 애니메이션 인덱스
	D2D1_RECT_F m_SrcRect = { 0.f, 0.f };		// D2D1Bitmap의 Source 영역
	D2D1_RECT_F m_DstRect = { 0.f, 0.f };		// RenderTarget의 Destination 영역		

	bool m_bMirror;				// 좌우 반전 여부
	D2D1_MATRIX_3X2_F	m_ImageTransform;	// 반대 방향으로 뒤집기 위한 행렬 Scale.x = -1.0f 
	Texture* m_pTexture;

	void LoadAnimationAsset(const std::wstring strFilePath);
	void LoadTexture(const std::wstring strFilePath);
	void Update(float fTimeElapsed);
	void Render(ID2D1HwndRenderTarget* pRenderTarget, D2D1_MATRIX_3X2_F cameraMat);
	void Render(D2D1_MATRIX_3X2_F cameraMat);
	void SetAnimation(int index, bool mirror, bool continueCurrentFrame = false);

	AABB GetBound();

	int GetMaxIndex();

	bool IsLastFrame();
};

