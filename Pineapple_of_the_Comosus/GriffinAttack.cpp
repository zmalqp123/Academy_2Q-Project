#include "GriffinAttack.h"
#include "Enemy.h"
#include "../D2DEngine/GameObject.h"
void GriffinAttack::Enter()
{	
	enemy = dynamic_cast<Enemy*>(fsm->gameObject->GetComponent<Enemy>());
}

void GriffinAttack::Update(float deltaTime)
{

}

void GriffinAttack::Exit()
{
}
