#include "MusKetAttack.h"
#include "Enemy.h"
#include "../D2DEngine/GameObject.h"
#include "MainPineApple.h"
void MusKetAttack::Enter()
{
	enemy = dynamic_cast<Enemy*>(fsm->gameObject->GetComponent<Enemy>());
}

void MusKetAttack::Update(float deltaTime)
{
	enemy->mainPineApple->pineAppleDamageHP(enemy->enemyData.attack);
}

void MusKetAttack::Exit()
{
}
