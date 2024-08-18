#include "BomberMove.h"
#include "../D2DEngine/SoundManager.h"

void BomberMove::Enter()
{
}

void BomberMove::Update(float deltaTime)
{
	moveTime += deltaTime;
	if (moveTime > 2.f)
	{
		SoundManager::GetInstance().PlaySoundW(L"BombCartMovement_Se", false);
		moveTime = 0;
	}
}

void BomberMove::Exit()
{
}
