#include "PineAppleTile.h"
#include "MainPineApple.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/SpriteRenderer.h"
#include <string>
void PineAppleTile::Update(float deltaTime)
{

}

void PineAppleTile::IPointerEnter()
{
	pApple->PrintIndex(index);
	isSelected = true;
}

void PineAppleTile::IPointerStay()
{
}

void PineAppleTile::IPointerExit()
{
	isSelected = false;
}

bool PineAppleTile::IsPlaceable()
{
	// 터렛이 활성화되어있지 않다면 설치가능한 타일.
	return turret->isActive == false;
}

void PineAppleTile::SetActivateTurret(std::wstring& path)
{
	auto spr = turret->GetComponent<SpriteRenderer>();
	spr->LoadTexture(path.c_str());
}

