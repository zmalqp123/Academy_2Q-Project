#include "MusKetAttack.h"
#include "Enemy.h"
#include "../D2DEngine/GameObject.h"
void MusKetAttack::Enter()
{
	enemy = dynamic_cast<Enemy*>(fsm->gameObject->GetComponent<Enemy>());
}

void MusKetAttack::Update(float deltaTime)
{
	if (enemy->enemyData.hp < 0)
	{
		fsm->SetState("Dead");
	}
}

void MusKetAttack::Exit()
{
}
