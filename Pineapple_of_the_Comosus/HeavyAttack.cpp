#include "HeavyAttack.h"
#include "Enemy.h"
#include "../D2DEngine/GameObject.h"
#include "MainPineApple.h"
void HeavyAttack::Enter()
{
	enemy = dynamic_cast<Enemy*>(fsm->gameObject->GetComponent<Enemy>());
}

void HeavyAttack::Update(float deltaTime)
{
	enemy->mainPineApple->pineAppleDamageHP(enemy->enemyData.attack);
}

void HeavyAttack::Exit()
{
}
