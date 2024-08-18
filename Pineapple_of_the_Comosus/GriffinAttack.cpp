#include "GriffinAttack.h"
#include "Enemy.h"
#include "../D2DEngine/GameObject.h"
#include "MainPineApple.h"
#include"../D2DEngine/SoundManager.h"
void GriffinAttack::Enter()
{	
	__super::Enter();
}

void GriffinAttack::Update(float deltaTime)
{

	__super::Update(deltaTime);
}

void GriffinAttack::Exit()
{
}

void GriffinAttack::Attack()
{
	__super::Attack();
	// 사운드 초기화 및 로드
	SoundManager::GetInstance().PlaySoundW(L"GriffinAttack_Se", false);
}
