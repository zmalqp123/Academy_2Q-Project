#include "EnemyDead.h"
#include "Enemy.h"
#include "MainPineApple.h"
#include "GamePlayManager.h"
#include "../D2DEngine/GameObject.h"

void EnemyDead::Enter()
{
	enemy = dynamic_cast<Enemy*>(fsm->gameObject->GetComponent<Enemy>());
}

void EnemyDead::Update(float deltaTime)
{
	//죽는 애니메이션 넣을 것
}

void EnemyDead::Exit()
{
}
