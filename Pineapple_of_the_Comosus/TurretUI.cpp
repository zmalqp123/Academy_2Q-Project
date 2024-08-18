#include "TurretUI.h"
#include "DataManager.h"
#include "MainPineApple.h"
#include "DynamicData.h"
#include "../D2DEngine/ImageUIRenderer.h"
void TurretUI::Update(float deltaTime)
{
	if (DataManager::GetInstance().GetTurretData((int)type)->cost <= pApple->GetPineAppleGold()&&
		pApple->rewardData->isHarvest == false)
		blockImage->alpha = 0.f;
	else
		blockImage->alpha = 0.5f;
}
