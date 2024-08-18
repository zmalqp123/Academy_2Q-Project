#include "DynamicData.h"
#include "DataManager.h"
void DynamicData::Init()
{
	turretLevel[TurretType::Crossbow] = 0;
	turretLevel[TurretType::Musket] = 0;
	turretLevel[TurretType::Cannon] = 0;
	turretLevel[TurretType::SuperCrossbow] = 0;
	turretLevel[TurretType::SlowWand] = 0;
	turretLevel[TurretType::GrowthPromoter] = 0;

	rewardTurretStat[TurretType::Crossbow];
	rewardTurretStat[TurretType::Musket];
	rewardTurretStat[TurretType::Cannon];
	rewardTurretStat[TurretType::SuperCrossbow];
	rewardTurretStat[TurretType::SlowWand];
	rewardTurretStat[TurretType::GrowthPromoter];
}

void DynamicData::UpgradeTurret(TurretType turretType)
{
	if(turretLevel[turretType] < 4)
		turretLevel[turretType] += 1;
}

const TurretData* DynamicData::GetStaticTurretData(TurretType turretType)
{
	int number = turretLevel[turretType] + (int)turretType;
	return DataManager::GetInstance().GetTurretData(number);
}

const TurretData* DynamicData::GetNextStaticTurretData(TurretType turretType)
{
	int number = turretLevel[turretType] + (int)turretType + 1;
	if (turretLevel[turretType] == 4) {
		return nullptr;
	}
	return DataManager::GetInstance().GetTurretData(number);
}

const RewardTurretStat DynamicData::GetRewardTurretData(TurretType turretType)
{
	return rewardTurretStat[turretType];
}

const RewardPineAppleStat DynamicData::GetRewardPineAppleStat()
{
	return rewardPineAppleStat;
}
