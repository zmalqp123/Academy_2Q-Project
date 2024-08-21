#include "BomberDead.h"
#include "../D2DEngine/SoundManager.h"
#include "../D2DEngine/SpriteAnimation.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/FiniteStateMachine.h"
void BomberDead::Enter()
{	
	SoundManager::GetInstance().PlaySoundW(L"BombCartExplosion_Se", false);
	BomberDeadAnim->SetAnimation(0); // Animation 0 is BomberDead Animation.
}

void BomberDead::Update(float deltaTime)
{	
	if (BomberDeadAnim->IsLastFrame()) {
		BomberDeadAnim->SetAnimation(1); // Animation 1 is EmptyAnimation
		fsm->gameObject->isActive = false;
	}
	
}

void BomberDead::Exit()
{
}
