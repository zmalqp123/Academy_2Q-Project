#include "MainPineApple.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/ImageUIRenderer.h"
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
	// 몬스터로부터 경험치를 획득
	currentEXP += exp * killMultiply;

	// currentEXP가 maxEXP을 초과하면 maxEXP으로 설정
	if (currentEXP > maxEXP)
	{
		currentEXP = maxEXP;
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
		expbar->takeMp(currentEXP);
		expbar->ImageRender->slideBar = expbar->getBarWidth();
	}
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
		UpdateMaxEXP(); // 새로운 최대 경험치 설정
		std::cout << maxEXP << std::endl;
		//offeringValue = maxEXP * offeringMultiply; // 새로운 offeringValue 업데이트
		currentEXP = 0;
		LV++;
		// harvest UI 호출 -> harvest btn 애니메이션 호출
	}
	else {
		// 최대 경험치가 아닙니다.
	}
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

	//elapsedTime += deltaTime;
	//float temp = std::sinf(elapsedTime * 10.f) * 30.f;
	////std::cout << temp << std::endl;
	//gameObject->transform->pos.worldPosition.y = temp;
	////gameObject->transform->m_RelativeRotation = elapsedTime * 30.f;
}
