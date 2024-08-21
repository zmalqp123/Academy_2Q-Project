#include "Boss.h"
#include"../D2DEngine/SoundManager.h"
#include"../D2DEngine/GameTime.h"
#include "DataManager.h"
#include "MainPineApple.h"
#include "gamePopup.h"
#include <iostream>

void Boss::Init()
{
	__super::Init();
}

void Boss::Update(float delta)
{
	__super::Update(delta);

	if (enemyData.hp <= 0.f) {
		mainPineApple->isWin = true;
	}
}

void Boss::Render(D2D1_MATRIX_3X2_F cameraMat)
{
	__super::Render(cameraMat);
}
