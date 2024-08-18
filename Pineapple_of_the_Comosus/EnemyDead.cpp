#include "EnemyDead.h"
#include "Enemy.h"
#include "MainPineApple.h"
#include "GamePlayManager.h"
#include "EnemyColliderNotify.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/SoundManager.h"

void EnemyDead::Enter()
{
	enemy = dynamic_cast<Enemy*>(fsm->gameObject->GetComponent<Enemy>());
	enemy->mainPineApple->acquireGold(enemy->enemyData.reward);
	enemy->mainPineApple->monAcquireEXP(enemy->enemyData.expReward);
	
	switch (enemy->enemyData.id)
	{
	//sword
	case 30601: case 30602: case 30603: case 30604:
		SoundManager::GetInstance().PlaySoundW(L"KnightDeath_Se", false);
		break;
	//musket
	/*case 30605: case 30606: case 30607: case 30608:
		SoundManager::GetInstance().PlaySoundW(L"CrossbowFire_Se", false);*/
		break;
	//heavyarmy
	case 30609: case 30610: case 30611: case 30612:
		SoundManager::GetInstance().PlaySoundW(L"HeavySoldierDeath_Se", false);
		break;
	//griffin
	case 30613: case 30614: case 30615: case 30616:
		SoundManager::GetInstance().PlaySoundW(L"GriffinDeath_Se", false);
		break;
	//BombCartExplosion_Se
	case 30617: case 30618: case 30619: case 30620:
		SoundManager::GetInstance().PlaySoundW(L"BombCartExplosion_Se", false);
		break;
	}
	
}

void EnemyDead::Update(float deltaTime)
{	
	fsm->gameObject->transform->pos.worldPosition.y -= deltaTime * 300.f;
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
