#include "MusKetAttack.h"
#include "Enemy.h"
#include "../D2DEngine/GameObject.h"
#include "MainPineApple.h"
#include "../D2DEngine/SpriteRenderer.h"
#include"../D2DEngine/SoundManager.h"
void MusKetAttack::Enter()
{
	__super::Enter();
}

void MusKetAttack::Update(float deltaTime)
{
	__super::Update(deltaTime);
}

void MusKetAttack::Exit()
{
}

void MusKetAttack::Attack()
{
	__super::Attack();
	// 사운드 초기화 및 로드
	SoundManager::GetInstance().PlaySoundW(L"MusketAttack_Se", false);
}

void MusKetAttack::AttackMotion(float deltaTime)
{
	if (isAttack)
	{	
		enemy->AttackSprite->alpha = (1.0f - elapsedTimeforMotion);
		elapsedTimeforMotion += deltaTime;
		
		
		if (elapsedTimeforMotion >= 0.25f)
		{
			enemy->AttackSprite->alpha = 0.0f;
			elapsedTimeforMotion = 0.f;
			isAttack = false;
		}

	}
}
