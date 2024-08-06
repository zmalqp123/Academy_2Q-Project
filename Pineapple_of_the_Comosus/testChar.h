#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/Vector.h"

class SpriteRenderer;
class testChar : public Component
{
private:
	//Vector2 position; // 몬스터의 위치
	float speed; // 몬스터의 이동 속도
	Vector2 minBounds; // 이동 범위 최소값
	Vector2 maxBounds; // 이동 범위 최대값

	//SpriteRenderer* spriteRenderer;  // 추가: SpriteRenderer 포인터
public:

	testChar();  // 기본 생성자
	//void SetPosition(const Vector2& pos); // 위치 설정 메서드
	void virtual Init();
	void virtual Update(float delta);
	void virtual Render(D2D1_MATRIX_3X2_F cameraMat);

};

