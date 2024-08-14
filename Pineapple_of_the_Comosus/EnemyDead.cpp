#include "EnemyDead.h"
#include "Enemy.h"
#include "MainPineApple.h"
#include "GamePlayManager.h"
#include "EnemyColliderNotify.h"
#include "../D2DEngine/GameObject.h"

void EnemyDead::Enter()
{
	enemy = dynamic_cast<Enemy*>(fsm->gameObject->GetComponent<Enemy>());
	enemy->mainPineApple->acquireGold(enemy->enemyData.reward);
	enemy->mainPineApple->monAcquireEXP(enemy->enemyData.expReward);
	

	
}

void EnemyDead::Update(float deltaTime)
{	
	bool isDeadAnimationEnd = false;
	//죽는 애니메이션 넣을 것

	if (isDeadAnimationEnd) {
		fsm->gameObject->isActive = false;
		fsm->gameObject->GetComponent<Enemy>()->notify->isActive = false;
	}
}

void EnemyDead::Exit()
{
}
