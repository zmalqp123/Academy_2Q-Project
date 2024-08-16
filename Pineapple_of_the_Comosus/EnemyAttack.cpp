#include "EnemyAttack.h"
#include "Enemy.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/SpriteRenderer.h"
#include "MainPineApple.h"


void EnemyAttack::Enter()
{
	enemy = fsm->gameObject->GetComponent<Enemy>();
	mainPineApple = enemy->mainPineApple;
}

void EnemyAttack::Update(float deltaTime)
{	
	elapsedTime += deltaTime;
	
	if (elapsedTime > (1.0f / enemy->enemyData.attackRate)) {
		Attack();
		isAttack = true;
		elapsedTime = 0.f;
	}

	AttackMotion(deltaTime);
}

void EnemyAttack::Exit()
{
}

void EnemyAttack::Attack()
{
	mainPineApple->pineAppleDamageHP(enemy->enemyData.attack);
}

void EnemyAttack::AttackMotion(float deltaTime)
{
	if (isAttack)
	{
		//enemy->AttackSprite->alpha = (1.0f - elapsedTimeforMotion * 4);
		enemy->AttackSprite->alpha = 1.0f;
		elapsedTimeforMotion += deltaTime;


		if (elapsedTimeforMotion >= 0.25f)
		{
			enemy->AttackSprite->alpha = 0.0f;
			elapsedTimeforMotion = 0.f;
			isAttack = false;
		}

	}
}
