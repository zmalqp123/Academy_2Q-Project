#include "BomberMove.h"
#include "Enemy.h"
#include "../D2DEngine/SoundManager.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/SpriteAnimation.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Transform.h"
void BomberMove::Enter()
{
	enemy = fsm->gameObject->GetComponent<Enemy>();
	SoundManager::GetInstance().PlaySoundW(L"BombCartMovement_Se", false);
}

void BomberMove::Update(float deltaTime)
{
	moveTime += deltaTime;
	if (abs(fsm->gameObject->transform->pos.worldPosition.x) <
		0/*파인애플 좌표*/ + 300/*파인애플 너비의 반*/ + enemy->enemyData.range)
	{
		fsm->SetState("Attack");
	}
	/*if (moveTime > 2.f)
	{
		SoundManager::GetInstance().PlaySoundW(L"BombCartMovement_Se", false);
		moveTime = 0;
	}*/
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
	enemy->move->m_speed = 0.f;
}
