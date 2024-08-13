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
}

void DynamicData::UpgradeTurret(TurretType turretType)
{
	turretLevel[turretType] += 1;
}

TurretData* DynamicData::GetTurretData(TurretType turretType)
{
	int number = turretLevel[turretType] + (int)turretType;
	return DataManager::GetInstance().GetTurretData(number);
}
