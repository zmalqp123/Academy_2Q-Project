#include "BomberAttack.h"
#include "Enemy.h"
#include "../D2DEngine/GameObject.h"
#include "MainPineApple.h"
void BomberAttack::Enter()
{
	enemy = dynamic_cast<Enemy*>(fsm->gameObject->GetComponent<Enemy>());
}

void BomberAttack::Update(float deltaTime)
{
	enemy->mainPineApple->pineAppleDamageHP(enemy->enemyData.attack);
}

void BomberAttack::Exit()
{
}
