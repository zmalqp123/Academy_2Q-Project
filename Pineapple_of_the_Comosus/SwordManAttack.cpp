#include "SwordManAttack.h"
#include "Enemy.h"
#include "../D2DEngine/GameObject.h"
#include "MainPineApple.h"
#include"../D2DEngine/SoundManager.h"
void SwordManAttack::Enter()
{
	__super::Enter();
	
}

void SwordManAttack::Update(float deltaTime)
{	
	__super::Update(deltaTime);
}

void SwordManAttack::Exit()
{

}

void SwordManAttack::Attack()
{
	__super::Attack();
	SoundManager::GetInstance().PlaySoundW(L"KnightAttack_Se", false);
}
