#include "TurretUI.h"
#include "DataManager.h"
#include "MainPineApple.h"
#include "DynamicData.h"
#include "../D2DEngine/ImageUIRenderer.h"
#include "../D2DEngine/TextUIRenderer.h"
void TurretUI::Update(float deltaTime)
{
	if (DataManager::GetInstance().GetTurretData((int)type)->cost <= pApple->GetPineAppleGold()&&
		pApple->rewardData->isHarvest == false)
		blockImage->alpha = 0.f;
	else
		blockImage->alpha = 0.5f;

	if (pApple->rewardData->isUpgrade == false) {
		textUI->text = std::to_wstring(DataManager::GetInstance().GetTurretData((int)type)->cost).c_str();
	}
	else {
		auto cost = pApple->rewardData->GetNextStaticTurretData(type);
		if (cost == nullptr) {
			textUI->text = L"X";
		}
		else {
			textUI->text = std::to_wstring(cost->cost).c_str();
		}
	}
}
