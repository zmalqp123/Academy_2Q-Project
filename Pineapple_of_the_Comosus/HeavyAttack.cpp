#include "HeavyAttack.h"
#include "Enemy.h"
#include "../D2DEngine/GameObject.h"
void HeavyAttack::Enter()
{
	enemy = dynamic_cast<Enemy*>(fsm->gameObject->GetComponent<Enemy>());
}

void HeavyAttack::Update(float deltaTime)
{
	if (enemy->enemyData.hp < 0)
	{
		fsm->SetState("Dead");
	}
}

void HeavyAttack::Exit()
{
}
