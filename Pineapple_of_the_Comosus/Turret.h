#pragma once
#include "../D2DEngine/GameObject.h"

enum class BulletType
{	
	Normal,
	Arrow,
	Bullet,
	Burst
};

class Turret : public GameObject
{	
private:
	int cost;
	int refund;

	BulletType bulletType;
	float bulletSpeed;
	int damage;
	float fireRate;
	int penetration;

	float angle;

public:
	Turret() = default;
	virtual ~Turret() = default;

	virtual void Init() = 0; //여기서 위의 private 변수들을 초기화 해줘야함.

	void SetCost(int cost) { this->cost = cost; }
	int GetCost() { return cost; }

	void SetRefund(int refund) { this->refund = refund; }
	int GetRefund() { return refund; }

	void SetBulletType(BulletType bulletType) { this->bulletType = bulletType; }
	BulletType GetBulletType() { return bulletType; }

	void SetBulletSpeed(float bulletSpeed) { this->bulletSpeed = bulletSpeed; }
	float GetBulletSpeed() { return bulletSpeed; }

	void SetDamage(int damage) { this->damage = damage; }
	int GetDamage() { return damage; }

	void SetFireRate(float fireRate) { this->fireRate = fireRate; }
	float GetFireRate() { return fireRate; }

	void SetPenetration(int penetration) { this->penetration = penetration; }
	int GetPenetration() { return penetration; }

	void SetAngle(float angle) { this->angle = angle; }
	float GetAngle() { return angle; }




};

