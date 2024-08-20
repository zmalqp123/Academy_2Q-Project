#pragma once
#include "../D2DEngine/Component.h"
#include <unordered_map>
#include "Turret.h"

struct RewardTurretStat {
	RewardTurretStat() {
		burstRange = 0.f;
		damage = 0;
		fireRate = 0.f;
		penetration = 0;

		bulletType = 0;
		bulletSpeed = 0.f;
		slowRate = 0;
		slowDuration = 0.f;
	}
	float burstRange;
	int damage;
	float fireRate;
	int penetration;

	int bulletType;
	float bulletSpeed;
	int slowRate;
	float slowDuration;
};

struct RewardPineAppleStat {
	int maxHp = 0;
	int solarGain = 0;
	int morningValue = 0;
	int nightValue = 0;
	float comosusLight = 0.f;
	float killMultiply = 0.f;
	float offeringMultiply = 0.f;
};

class DynamicData : public Component
{
private:
	std::unordered_map<TurretType, int> turretLevel;
public:
	std::unordered_map<TurretType, RewardTurretStat> rewardTurretStat;
	RewardPineAppleStat rewardPineAppleStat;

	bool isHarvest = false;
	bool isUpgrade = false;

	DynamicData() {};
	virtual ~DynamicData() {};

	void Init();

	void UpgradeTurret(TurretType turretType);

	const TurretData* GetStaticTurretData(TurretType turretType);
	const TurretData* GetNextStaticTurretData(TurretType turretType);
	const RewardTurretStat GetRewardTurretData(TurretType turretType);
	const RewardPineAppleStat GetRewardPineAppleStat();
	const int GetTurretLevel(TurretType turretType) { return turretLevel[turretType]; }
};

