#pragma once
#include "../D2DEngine/Component.h"
#include <unordered_map>
#include "Turret.h"
class DynamicData : public Component
{
private:
	std::unordered_map<TurretType, int> turretLevel;

public:
	DynamicData() {};
	virtual ~DynamicData() {};

	void Init();

	void UpgradeTurret(TurretType turretType);

	TurretData* GetTurretData(TurretType turretType);
};

