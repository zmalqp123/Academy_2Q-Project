#include "PineAppleTile.h"
#include "MainPineApple.h"
#include "../D2DEngine/GameObject.h"
void PineAppleTile::Update(float deltaTime)
{
}

void PineAppleTile::IPointerEnter()
{
	pApple->PrintIndex(index);
}

void PineAppleTile::IPointerStay()
{
}

void PineAppleTile::IPointerExit()
{
}

bool PineAppleTile::IsPlaceable()
{
	// 터렛이 활성화되어있지 않다면 설치가능한 타일.
	return turret->isActive == false;
}
