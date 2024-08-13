#pragma once
#include "../D2DEngine/Component.h"
#include "Mpbar.h"

class BulletFactory;
class DataManager;
class MainPineApple : public Component
{
	int gold = 300; 
	int HP = 0;					// 현재 파인애플 체력. HP가 0이되면 게임오버
	int maxHP = 100;			// 파인애플 최대체력 
	float currentEXP = 0;			// 현재 파인애플의 경험치
	float maxEXP = 100;			// 파인애플 최대 경험치 값
	float solarGain = 1;			// 현재 파인애플의 초당 수확경험치량
	int morningValue = 1;		// 낮 시간대 적용 값
	int nightValue = 0;			// 밤 시간대 적용 값
	float killMultiply = 1.0;	// 몬스터 처치시 경험치 배율. currentExp = currentExp + 몬스터 처치 exp * killMultiply값
	float offeringMultiply = 0.75; // 기본 0.75 설정,  75퍼 채웠을 때 사용가능 
	float offeringValue = maxEXP * offeringMultiply;
	 
public:
	Mpbar* expbar;
	MainPineApple() { };
	virtual ~MainPineApple() { };

	void PrintIndex(int index);
	void acquireGold(int cost);		// 몬스터 사망시 획득한 골드
	void spendGold(int cost);		// 터렛 설치시 사용한 골드
	void monAcquireEXP(float exp);	// 몬스터 사망시 획득한 경험치 
	void solarAcquireEXP(float deltaTime);
	void throwUiEXP(int currentEXP);
	void Harvest();					// 경험치를 소비해서 파인애플 수확, 파인애플 최대 경험치 참고
	int GetPineAppleGold() { return gold; }	// 현재 파인애플 골드량
	int GetCurrentExp() { return currentEXP; }			// 현재 파인애플 경험치 -> 파인애플 수확 횟수									

	float elapsedTime = 0.f;
	virtual void Update(float deltaTime);

	BulletFactory* bulletFactory;
};

