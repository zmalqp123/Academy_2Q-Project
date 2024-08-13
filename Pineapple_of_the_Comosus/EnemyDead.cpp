#include "EnemyDead.h"
#include "Enemy.h"
#include "MainPineApple.h"
#include "GamePlayManager.h"
#include "../D2DEngine/GameObject.h"

void EnemyDead::Enter()
{
	enemy = dynamic_cast<Enemy*>(fsm->gameObject->GetComponent<Enemy>());
	enemy->mainPineApple->acquireGold(enemy->enemyData.reward);
	enemy->mainPineApple->monAcquireEXP(enemy->enemyData.expReward);
}

void EnemyDead::Update(float deltaTime)
{
}

void EnemyDead::Exit()
{
}
