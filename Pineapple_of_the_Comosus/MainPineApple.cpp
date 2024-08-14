#include "MainPineApple.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/ImageUIRenderer.h"
#include "Mpbar.h"
#include "Hpbar.h"
#include "../D2DEngine/Button.h"
#include "DynamicData.h"
#include <iostream>
void MainPineApple::PrintIndex(int index)
{
	std::cout << index << std::endl;
}

void MainPineApple::acquireGold(int cost)
{
	gold += cost;
}

void MainPineApple::spendGold(int cost)
{
	if (gold >= cost)
	{
		gold -= cost;
		std::cout << "현재 남은 파인애플 골드 : " << gold << std::endl;
	}
}

// 몬스터에서 호출 
void MainPineApple::monAcquireEXP(float exp)
{

	float dyKillMultiply = rewardData->GetRewardPineAppleStat().killMultiply;
	// 몬스터로부터 경험치를 획득
	currentEXP += exp * (killMultiply + dyKillMultiply);

	// currentEXP가 maxEXP을 초과하면 maxEXP으로 설정
	if (currentEXP > maxEXP)
	{
		currentEXP = maxEXP;
	}
}

// 몬스터 atk 에서 호출 
void MainPineApple::pineAppleDamageHP(int damage)
{
	if (HP > 0)
	{
		std::cout << "초기 HP : " << HP << std::endl;
		HP -= damage;
		std::cout << "데미지 후 HP : " << HP << std::endl;
	}
	else
	{
		HP = 0;
	}
}

void MainPineApple::solarAcquireEXP(float deltaTime)
{
	// 현재 경험치를 증가시키지만, 최대 maxEXP까지만 허용
	if (currentEXP <= maxEXP)
	{
		currentEXP += solarGain * deltaTime;

		// currentEXP가 maxEXP을 초과하면 maxEXP으로 설정
		if (currentEXP >= maxEXP)
		{
			currentEXP = maxEXP;
		}
	}
}

void MainPineApple::throwUiEXP(int currentEXP)
{
	// maxEXP가 100이고 currentEXP가 0에서 100 사이일 경우에만 동작
	if (maxEXP <= maxEXP && currentEXP >= 0 && currentEXP <= maxEXP)
	{
		//expbar->takeMp(currentEXP);
		expbar->ImageRender->slideBar = currentEXP / maxEXP;//expbar->getBarWidth();
	}
}

void MainPineApple::throwUiHP(int HP)
{
	// HP가 maxHP를 초과하거나 0 미만으로 내려가지 않도록 제한
	if (HP < 0)
		HP = 0;
	else if (HP > maxHP)
		HP = maxHP;

	// UI 바를 업데이트 (비율을 계산하여 전달)
	hpbar->ImageRender->slideBar =HP / maxHP;
}

void MainPineApple::UpdateMaxEXP()
{
	maxEXP = EXP_TABLE[LV - 1];
}


void MainPineApple::Harvest()
{
	// LV조건에 따라 바뀜
	//harvest;
	// 최대 경험치라면 최대 lv
	// 최대 경험치에 도달한 경우 레벨업
	if (currentEXP == maxEXP)
	{
		LV++;
		UpdateMaxEXP(); // 새로운 최대 경험치 설정
		std::cout << maxEXP << std::endl;
		//offeringValue = maxEXP * offeringMultiply; // 새로운 offeringValue 업데이트
		currentEXP = 0;
		// harvest UI 호출 -> harvest btn 애니메이션 호출
	}
	else {
		// 최대 경험치가 아닐때 75퍼면 수확가능 또 아니면 수확불가 
		if (HarvestAble())
		{
			LV++;
			std::cout << "최대경험치 이하 수확 :" << maxEXP << std::endl;
			UpdateMaxEXP(); // 새로운 최대 경험치 설정
			currentEXP = 0;
		}
		else
		{
			std::cout <<  "수확불가 :" << maxEXP << std::endl;
		}
	}
}

bool MainPineApple::HarvestAble()
{
	if (currentEXP >= GetOfferingValue())
	{
		return true;
	}
	return false;
}

float MainPineApple::GetOfferingValue()
{
	return maxEXP * (offeringMultiply+rewardData->GetRewardPineAppleStat().offeringMultiply);
}

void MainPineApple::Update(float deltaTime)
{
	// 초당 수확량
	solarAcquireEXP(deltaTime);
	//std::cout << GetCurrentExp() << std::endl;
	//std::cout << offeringValue << std::endl;
	// UI HP바 업데이트  

	// UI MP바 업데이트 
	// GetCurrentExp() 현재 경험치를 mpbar에게 넘기는 함수 호출 
	throwUiEXP(GetCurrentExp());
	throwUiHP(GetPineAppleHP());

	// 수확 버튼 활성화
	// 수확이 가능하다면 수확 버튼 활성화
	if (HarvestAble())
	{
		harvestbtn->LoadTexture(L"../Resource/harvestable.png");

	}
	else
	{
		harvestbtn->LoadTexture(L"../Resource/harvest.png");
	}

	//elapsedTime += deltaTime;
	//float temp = std::sinf(elapsedTime * 10.f) * 30.f;
	////std::cout << temp << std::endl;
	//gameObject->transform->pos.worldPosition.y = temp;
	////gameObject->transform->m_RelativeRotation = elapsedTime * 30.f;
}
