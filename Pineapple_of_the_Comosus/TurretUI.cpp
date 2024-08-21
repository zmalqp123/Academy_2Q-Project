#include "TurretUI.h"
#include "DataManager.h"
#include "MainPineApple.h"
#include "DynamicData.h"
#include "../D2DEngine/ImageUIRenderer.h"
#include "../D2DEngine/TextUIRenderer.h"
#include "../D2DEngine/Button.h"
void TurretUI::Update(float deltaTime)
{
	auto data = DataManager::GetInstance().GetTurretData((int)type);
	auto upgradeData = pApple->rewardData->GetNextStaticTurretData(type);

	if (pApple->rewardData->isHarvest == false) {
		if (pApple->rewardData->isUpgrade == false) {
			if (data->cost <= pApple->GetPineAppleGold()) {
				blockImage->alpha = 0.f;
				textUI->SetTextColor(possible);
			}
			else {
				blockImage->alpha = 0.5f;
				textUI->SetTextColor(impossible);
			}
		}
		else {
			if (upgradeData != nullptr) {
				if (upgradeData->cost <= pApple->GetPineAppleGold()) {
					blockImage->alpha = 0.f;
					textUI->SetTextColor(possible);
				}
				else {
					blockImage->alpha = 0.5f;
					textUI->SetTextColor(impossible);
				}
			}
			else {
				blockImage->alpha = 0.5f;
				textUI->SetTextColor(impossible);
			}
		}
	}
	else {
		blockImage->alpha = 0.5f;
		//textUI->SetTextColor(impossible);
	}

	if (pApple->rewardData->isUpgrade == false) {
		textUI->text = std::to_wstring(data->cost).c_str();

		button->LoadTexture(defaultPath.c_str());
	}
	else {
		auto cost = upgradeData;
		if (cost == nullptr) {
			textUI->text = L"X";
		}
		else {
			textUI->text = std::to_wstring(cost->cost).c_str();
		}
		button->LoadTexture(upgradePath.c_str());
	}
}
