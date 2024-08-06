#pragma once
#include "Component.h"
#include "Vector.h"
enum Type
{
	World,
	Ui
};

struct RectPostion
{
	Vector2 leftBottom;
	Vector2 rightTop;
};

union Position
{
	RectPostion rectposition;
	Vector2 worldPosition;
};

class Transform : public Component
{
public:
	Transform() {};
	virtual ~Transform() {};

public:
	Transform*			m_pParentScene = nullptr;	// 부모 Scene 컴포넌트	
	Vector2		m_RelativeScale = { 1,1 };	// 상대 크기
	float				m_RelativeRotation = 0;		// 상대 회전
	//Vector2 		m_RelativeLocation = { 0,0 }; // 상대 위치
	D2D1_MATRIX_3X2_F	m_RelativeTransform;		// 상대 복합 변환
	D2D1_MATRIX_3X2_F	m_WorldTransform;			// 부모까지 반영된 최종 변환
	Type type = Type::World;
	Position pos;
	//Vector2		m_CenterTransform;

	// RelativeTransform과 m_WorldTransform을 계산한다.
	void UpdateTrasnform();
	void SetParent(Transform* pParentScene) { m_pParentScene = pParentScene; }
};

