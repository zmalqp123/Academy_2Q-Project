#include "MainPineApple.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include <iostream>
void MainPineApple::PrintIndex(int index)
{
	std::cout << index << std::endl;
}

void MainPineApple::acquireGold(int cost)
{
	PineAppleGold += cost;
}

void MainPineApple::spendGold(int cost)
{
	if (PineAppleGold >= cost)
	{
		PineAppleGold -= cost;
		std::cout << "현재 남은 파인애플 골드 : " << PineAppleGold << std::endl;
	}
}

void MainPineApple::monAcquireEXP(int exp)
{
	currentEXP += exp;
}

void MainPineApple::Harvest(int exp)
{
}

void MainPineApple::Update(float deltaTime)
{
	//elapsedTime += deltaTime;
	//float temp = std::sinf(elapsedTime * 10.f) * 30.f;
	////std::cout << temp << std::endl;
	//gameObject->transform->pos.worldPosition.y = temp;
	////gameObject->transform->m_RelativeRotation = elapsedTime * 30.f;
}
