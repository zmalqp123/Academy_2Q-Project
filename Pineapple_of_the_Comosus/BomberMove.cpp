#include "BomberMove.h"
#include "../D2DEngine/SoundManager.h"

void BomberMove::Enter()
{
}

void BomberMove::Update(float deltaTime)
{
	SoundManager::GetInstance().PlaySoundW(L"KnightAttack_Se", false);
}

void BomberMove::Exit()
{
}
