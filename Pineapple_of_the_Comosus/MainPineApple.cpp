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
	currentEXP = exp * killMultiply;
}

void MainPineApple::solarAcquireEXP(float deltaTime)
{
	currentEXP += solarGain * deltaTime;


	//expbar->takeMp(10.f);
	//expbar->ImageRender->slideBar = expbar->getBarWidth();
	//std::cout << expbar->ImageRender->m_DstRect.right << std::endl;
	//std::cout << expbar->getBarWidth() << std::endl;

}

void MainPineApple::throwUiEXP(int currentEXP)
{
	// maxEXP가 100이고 currentEXP가 0에서 100 사이일 경우에만 동작
	if (maxEXP <= 100 && currentEXP >= 0 && currentEXP <= 100)
	{
		expbar->takeMp(currentEXP);
		expbar->ImageRender->slideBar = expbar->getBarWidth();
	}
}


void MainPineApple::Harvest()
{
	// harvest UI 호출
}

void MainPineApple::Update(float deltaTime)
{
	// 초당 수확량
	solarAcquireEXP(deltaTime);
	std::cout << GetCurrentExp() << std::endl;
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
