#include "BomberAttack.h"
#include "Enemy.h"
#include "../D2DEngine/GameObject.h"
void BomberAttack::Enter()
{
	enemy = dynamic_cast<Enemy*>(fsm->gameObject->GetComponent<Enemy>());
}

void BomberAttack::Update(float deltaTime)
{
	if (enemy->enemyData.hp < 0)
	{
		fsm->SetState("Dead");
	}
}

void BomberAttack::Exit()
{
}
