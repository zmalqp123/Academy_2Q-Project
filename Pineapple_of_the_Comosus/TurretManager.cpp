#include "TurretManager.h"
#include "DataManager.h"
TurretData* TurretManager::GetTurretData(int turretID)
{
    return dataManager->turretDataMap[turretID];
}
