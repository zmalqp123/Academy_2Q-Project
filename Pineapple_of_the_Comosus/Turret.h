#pragma once
#include "../D2DEngine/Component.h"
#include "Bullet.h"
#include "DataManager.h"

class MainPineApple;
class TurretData;
class DynamicData;
class SpriteRenderer;
enum class TurretType {

	Crossbow = 30501,
	Musket = 30511,
	Cannon = 30521,
	SuperCrossbow = 30531,
	SlowWand = 30541,
	GrowthPromoter = 30551

};

class BulletFactory;
class Turret : public Component
{	
	//float shootCooldown = 1.f;           // 총알 발사 간격을 위한 쿨다운 타이머 // 실시간 가져오는것으로 대체됨.
	float timeSinceLastShot;       // 마지막으로 총알을 발사한 이후의 시간
public:
	TurretType turretType;
	MainPineApple* parentPineApple;
	TurretData* turretData;
	DynamicData* dynamicData;
	GameObject* fireTr;
	SpriteRenderer* selectOutline;

	float prevAngle;
	float currAngle;
	Turret() = default;
	virtual ~Turret() = default;

	void virtual Init() override;
	void virtual Update(float delta) override;

	void Shoot();  // 총알 발사 함수

	void SelectTurret();
	void DeSelectTurret();

	void Refund();
	void ResetTurret();
};

