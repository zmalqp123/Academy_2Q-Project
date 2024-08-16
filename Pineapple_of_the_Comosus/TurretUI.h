#pragma once
#include "../D2DEngine/Component.h"
#include "Turret.h"
class TurretUI : public Component
{
	TurretType type = TurretType::Crossbow;
	int index = 0;
public:
	TurretUI() {}
	virtual ~TurretUI() {}
	
	void SetIndex(int _index) { index = _index; }
	void SetTurret(TurretType _type) { type = _type; }



	int GetIndex() { return index; }
	TurretType GetTurretType() { return type; }
};

