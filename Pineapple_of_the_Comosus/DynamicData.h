#pragma once
#include "../D2DEngine/Component.h"
#include <unordered_map>
#include "Turret.h"
class DynamicData : public Component
{
public:
	DynamicData() {};
	virtual ~DynamicData() {};

	void Init();

	std::unordered_map<TurretType, int> turretLevel;

};

