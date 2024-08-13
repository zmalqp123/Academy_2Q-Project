#include "SwordManAttack.h"
#include "Enemy.h"
#include "../D2DEngine/GameObject.h"
void SwordManAttack::Enter()
{
	enemy = dynamic_cast<Enemy*>(fsm->gameObject->GetComponent<Enemy>());

}

void SwordManAttack::Update(float deltaTime)
{
	if (enemy->enemyData.hp < 0)
	{
		fsm->SetState("Dead");
	}
}

void SwordManAttack::Exit()
{

}
