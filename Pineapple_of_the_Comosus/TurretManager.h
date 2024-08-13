#pragma once

class DataManager;
class TurretData;
class TurretManager
{
public:
	TurretManager() {};
	virtual ~TurretManager() {};

	DataManager* dataManager = nullptr;

	TurretData* GetTurretData(int turretID);
};

