#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/Vector.h"
#include "../D2DEngine/EventSystem.h"
#include "../D2DEngine/Collider.h"
#include "DataManager.h"
#include "Bullet.h"
#include <cmath>

enum class EliteType
{
	Normal,
	Hard,
	Fast,
	Hero
};
class MainPineApple;
class BoxCollider;
class Movement;
class SpriteRenderer;
class SpriteAnimation;

class Enemy : public Component
{
private:
	float hitTime = 0.f;
public:
	Enemy() = default;
	virtual ~Enemy() = default;
	EnemyData enemyData;


	//Vector2 position; // 몬스터의 위치
	//float speed; // 몬스터의 이동 속도
	Vector2 minBounds; // 이동 범위 최소값
	Vector2 maxBounds; // 이동 범위 최대값

	//SpriteRenderer* spriteRenderer;  // 추가: SpriteRenderer 포인터

	bool isSlowed = false;
	float defaultSpeed = 0.0f;
	float slowTimer = 0.0f;
	float slowedRate = 0.0f;
	float elapsedTime = 0.0f;
	float tmpY = 0.0f;
	int defaultAnimationNumber = -1;

	Movement* move;
	MainPineApple* mainPineApple;
	GameObject* notify;
	SpriteRenderer* AttackSprite;
	SpriteAnimation* enemyAnim;

	virtual void Init() override;
	virtual void Update(float delta) override;
	virtual void Render(D2D1_MATRIX_3X2_F cameraMat) override;

	Enemy& GetEnemy() { return *this; }

	void WaveMove(float delta);

	void Ondamage(int damage, BulletType bulletType, bool notReward = false);
	void OnSlow(float slowRate, float slowTime);

};

