#include "BomberMove.h"
#include "Enemy.h"
#include "../D2DEngine/SoundManager.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/SpriteAnimation.h"

void BomberMove::Enter()
{
}

void BomberMove::Update(float deltaTime)
{
	moveTime += deltaTime;
	if (moveTime > 2.f)
	{
		SoundManager::GetInstance().PlaySoundW(L"BombCartMovement_Se", false);
		moveTime = 0;
	}
	if (enemy->isSlowed) {
		enemy->slowTimer -= deltaTime;
		if (enemy->slowTimer <= 0.0f)
		{
			enemy->move->m_speed = enemy->defaultSpeed;
			enemy->isSlowed = false;
			enemy->slowedRate = 0.0f;
			enemy->slowTimer = 0.0f;
			enemy->enemyAnim->alpha = 1.f;
		}
	}
}

void BomberMove::Exit()
{
}
