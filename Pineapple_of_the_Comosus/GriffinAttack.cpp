#include "GriffinAttack.h"
#include "Enemy.h"
#include "../D2DEngine/GameObject.h"
void GriffinAttack::Enter()
{	
	enemy = dynamic_cast<Enemy*>(fsm->gameObject->GetComponent<Enemy>());
}

void GriffinAttack::Update(float deltaTime)
{
	if (enemy->enemyData.hp < 0)
	{
		fsm->SetState("Dead");
	}
}

void GriffinAttack::Exit()
{
}
