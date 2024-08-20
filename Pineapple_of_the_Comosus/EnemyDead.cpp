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
	isSpined = false;
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

	switch (enemy->enemyData.id)
	{
		//sword
	case 30601: case 30602: case 30603: case 30604:
			Spin(deltaTime);
		break;
		//musket
		case 30605: case 30606: case 30607: case 30608:
			Spin(deltaTime);
		break;
		//heavyarmy
	case 30609: case 30610: case 30611: case 30612:
			Spin(deltaTime);
		break;
		//griffin
	case 30613: case 30614: case 30615: case 30616:
			Spin(deltaTime);
		break;
		//BombCartExplosion_Se
	case 30617: case 30618: case 30619: case 30620:
			Spin(deltaTime);
		break;
	}
	if (isSpined) {
		fsm->gameObject->transform->pos.worldPosition.y -= deltaTime * 300.f;
	}
	if (fsm->gameObject->transform->m_WorldTransform.dy < -650.f) {
		fsm->gameObject->isActive = false;
	}
}

void EnemyDead::Exit()
{
	isSpined = false;
}

void EnemyDead::Spin(float deltaTime)
{
	//fsm->gameObject->transform->m_RelativeRotation += 5.f;
	if (fsm->gameObject->transform->m_RelativeRotation < 30.f) {
		fsm->gameObject->transform->m_RelativeRotation += 250.f * deltaTime;
	}

	isSpined = true;
}
