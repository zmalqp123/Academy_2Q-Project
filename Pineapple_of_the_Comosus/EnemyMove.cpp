#include "EnemyMove.h"
#include "Enemy.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Transform.h"

void EnemyMove::Enter()
{

}

void EnemyMove::Update(float deltaTime)
{
	if (abs(fsm->gameObject->transform->pos.worldPosition.x) <
		0/*파인애플 좌표*/ + 300/*파인애플 너비의 반*/ + dynamic_cast<Enemy*>(fsm->gameObject->GetComponent<Enemy>())->range)
	{
		fsm->SetState("Attack");
	}
	else if(dynamic_cast<Enemy*>(fsm->gameObject->GetComponent<Enemy>())->hp<0)
	{
		fsm->SetState("Dead");
	}


}

void EnemyMove::Exit()
{

}
