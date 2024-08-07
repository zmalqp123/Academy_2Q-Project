#include "PineAppleTile.h"
#include "MainPineApple.h"
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
	return turret == nullptr;
}
