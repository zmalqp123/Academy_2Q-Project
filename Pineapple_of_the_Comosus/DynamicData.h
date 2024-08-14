#pragma once
#include "../D2DEngine/Component.h"
#include <unordered_map>
#include "Turret.h"

struct RewardTurretStat {
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
	int maxHp;
	int solarGain;
	int morningValue;
	int nightValue;
	float comosusLight;
	float offeringMultiply;
};

class DynamicData : public Component
{
private:
	std::unordered_map<TurretType, int> turretLevel;
public:
	std::unordered_map<TurretType, RewardTurretStat> rewardTurretStat;
	RewardPineAppleStat rewardPineAppleStat;

	DynamicData() {};
	virtual ~DynamicData() {};

	void Init();

	void UpgradeTurret(TurretType turretType);

	const TurretData* GetStaticTurretData(TurretType turretType);
	const RewardTurretStat GetRewardTurretData(TurretType turretType);
	const RewardPineAppleStat GetRewardPineAppleStat();
};

