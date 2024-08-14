#pragma once
#include "../D2DEngine/Component.h"
#include <vector>
#include "HarvestButton.h"

class BulletFactory;
class Mpbar;
class Hpbar;
class Button;
class DynamicData;
class MainPineApple : public Component
{
	int gold = 300;
	int LV = 1;
	int maxHP = 100;			// 파인애플 최대체력 
	int HP = maxHP;				// 현재 파인애플 체력. HP가 0이되면 게임오버
	float currentEXP = 0;		// 현재 파인애플의 경험치
	float maxEXP = 100;			// 파인애플 최대 경험치 값
	float solarGain = 50;		// 현재 파인애플의 초당 수확경험치량
	int morningValue = 1;		// 낮 시간대 적용 값
	int nightValue = 0;			// 밤 시간대 적용 값
	float killMultiply = 1.0;	// 몬스터 처치시 경험치 배율. currentExp = currentExp + 몬스터 처치 exp * killMultiply값
	float offeringMultiply = 0.75; // 기본 0.75 설정,  75퍼 채웠을 때 사용가능 
	// float offeringValue;

	// 레벨별 최대 경험치 테이블
	std::vector<float> EXP_TABLE = {
		100, 200, 300, 400, 500,
		700, 900, 1100, 1300, 1500,
		1900, 2100, 2300, 2500, 2700,
		3100, 3500, 3900, 4300, 4700,
		5200, 5700, 6200, 6700, 7200,
		7200 // 레벨 26 이상의 경우 최대 경험치
	};

public:
	Mpbar* expbar;
	Hpbar* hpbar;
	Button* harvestbtn;
	HarvestButton* harvest;
	DynamicData* rewardData;
	MainPineApple() { };
	virtual ~MainPineApple() { };

	void PrintIndex(int index);
	void acquireGold(int cost);		// 몬스터 사망시 획득한 골드
	void spendGold(int cost);		// 터렛 설치시 사용한 골드
	void monAcquireEXP(float exp);	// 몬스터 사망시 획득한 경험치
	void pineAppleDamageHP(int damage);	// 몬스터에서 atk 때 파인애플 데미지
	void solarAcquireEXP(float deltaTime);
	void throwUiEXP(int currentEXP);
	void throwUiHP(int HP);
	void UpdateMaxEXP();
	void Harvest();					// 경험치를 소비해서 파인애플 수확, 파인애플 최대 경험치 참고
	bool HarvestAble();
	int GetPineAppleGold() { return gold; }	// 현재 파인애플 골드량
	int GetCurrentExp() { return currentEXP; }			// 현재 파인애플 경험치 -> 파인애플 수확 횟수									
	int GetPineAppleLV() { return LV; }
	int GetPineAppleHP() { return HP; }				// 현재 파인애플 hp 가져오기 
	float GetOfferingValue(); // float offeringValue;
	float elapsedTime = 0.f;
	virtual void Update(float deltaTime);

	BulletFactory* bulletFactory;
};

