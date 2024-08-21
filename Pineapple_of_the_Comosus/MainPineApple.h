#pragma once
#include "../D2DEngine/Component.h"
#include <vector>
#include "HarvestButton.h"

class HarvestPopup;
class BulletFactory;
class Mpbar;
class Hpbar;
class Button;
class DynamicData;
class SpriteAnimation;
class FiniteStateMachine;
class ramdomReward;
class Turret;
class TextUIRenderer;
class WaveSystem;
class gamePopup;
class SpriteUIAnimation;
class MainPineApple : public Component
{
	friend class ComosusPhase1;
	int gold = 300;
	int LV = 1;
	float maxHP = 100;			// ���ξ��� �ִ�ü�� 
	float HP = maxHP;				// ���� ���ξ��� ü��. HP�� 0�̵Ǹ� ���ӿ���
	float currentEXP = 0;		// ���� ���ξ����� ����ġ
	float maxEXP = 100;			// ���ξ��� �ִ� ����ġ ��
	float solarGain = 1.0f;		// ���� ���ξ����� �ʴ� ��Ȯ����ġ��
	int morningValue = 10;		// �� �ð��� ���� ��
	int nightValue = 0;			// �� �ð��� ���� ��
	float killMultiply = 1.0;	// ���� óġ�� ����ġ ����. currentExp = currentExp + ���� óġ exp * killMultiply��
	float offeringMultiply = 0.75; // �⺻ 0.75 ����,  75�� ä���� �� ��밡�� 
	// float offeringValue;

	// ������ �ִ� ����ġ ���̺�
	std::vector<float> EXP_TABLE = {
		100, 200, 300, 400, 500,
		700, 900, 1100, 1300, 1500,
		1900, 2100, 2300, 2500, 2700,
		3100, 3500, 3900, 4300, 4700,
		5200, 5700, 6200, 6700, 7200,
		7200 // ���� 26 �̻��� ��� �ִ� ����ġ
	};

public:
	Mpbar* expbar;
	Hpbar* hpbar;
	Button* Popup;
	Button* harvestbtn;
	HarvestButton* harvest;
	DynamicData* rewardData;
	SpriteAnimation* comosus;
	FiniteStateMachine* fsm;
	TextUIRenderer* goldbar;
	TextUIRenderer* LVbar;
	WaveSystem* waveSystem;
	std::vector<GameObject*> rewardbtn;
	gamePopup* endpopup;
	ramdomReward* randomReward;
	FiniteStateMachine* comosusFsm;
	int pineAppleLv = 1;
	std::vector<Turret*> turrets;

	MainPineApple() { };
	virtual ~MainPineApple() { };

	void DisableRewardButtons();
	void PrintIndex(int index);
	void acquireGold(int cost);		// ���� ����� ȹ���� ���
	void spendGold(int cost);		// �ͷ� ��ġ�� ����� ���
	void monAcquireEXP(float exp);	// ���� ����� ȹ���� ����ġ
	void pineAppleDamageHP(int damage);	// ���Ϳ��� atk �� ���ξ��� ������
	void solarAcquireEXP(float deltaTime);
	void throwUiEXP(int currentEXP);
	void throwUiHP(int HP);
	void UpdateMaxEXP();
	void Harvest();					// ����ġ�� �Һ��ؼ� ���ξ��� ��Ȯ, ���ξ��� �ִ� ����ġ ����
	bool HarvestAble();
	int GetPineAppleGold() { return gold; }	// ���� ���ξ��� ��差
	float GetCurrentExp() { return currentEXP; }			// ���� ���ξ��� ����ġ -> ���ξ��� ��Ȯ Ƚ��									
	int GetPineAppleLV() { return LV; }
	float GetPineAppleHP() { return HP; }				// ���� ���ξ��� hp �������� 
	float GetOfferingValue(); // float offeringValue;
	float elapsedTime = 0.f;
	virtual void Update(float deltaTime);
	const float GetMaxExp() const { return maxEXP; }
	void RefundAll();
	void SetMaxHP(float increaseHp);
	void UpdateTurretImage();
	bool IsMaxEXP();
	void AddExp(float exp);

	SpriteUIAnimation* harvestableAnim;
	void UpdateHarvestableAnim();

	BulletFactory* bulletFactory;
};

