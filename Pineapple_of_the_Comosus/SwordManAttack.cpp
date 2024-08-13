#include "SwordManAttack.h"
#include "Enemy.h"
#include "../D2DEngine/GameObject.h"
#include "MainPineApple.h"
void SwordManAttack::Enter()
{
	enemy = dynamic_cast<Enemy*>(fsm->gameObject->GetComponent<Enemy>());
}

void SwordManAttack::Update(float deltaTime)
{
	enemy->mainPineApple->pineAppleDamageHP(enemy->enemyData.attack);
}

void SwordManAttack::Exit()
{

}
