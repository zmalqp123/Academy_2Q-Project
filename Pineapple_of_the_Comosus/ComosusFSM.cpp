#include "ComosusFSM.h"
#include "CameraShake.h"
#include "DynamicData.h"
#include "MainPineApple.h"
#include "ComosusLightSelector.h"
#include "EnemyColliderNotify.h"
#include "Enemy.h"
#include <iostream>
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/SpriteAnimation.h"
#include "../D2DEngine/GameTime.h"
#include "../D2DEngine/SpriteRenderer.h"
#include "../D2DEngine/TextUIRenderer.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/SoundManager.h"
#include "ramdomReward.h"
// Phase Defalue
void ComosusPhaseDefault::Enter()
{
	std::wcout << "comosus is baby." << std::endl;
}

void ComosusPhaseDefault::Update(float deltaTime)
{
}

void ComosusPhaseDefault::Exit()
{
}
bool ComosusPhase1::IsTiming(float prev, float curr, float timing)
{
	return prev < timing && curr >= timing;
}
void ComosusPhase1::OnComosusDamage()
{
	auto container = lightSeletor->GetContainer();
	for (auto enemy : container) {
		enemy->enemy->Ondamage(40.f, BulletType::Comosus, true);
	}
	std::cout << "light on" << std::endl;
}
// phase1
void ComosusPhase1::Enter()
{
	isMaxExp = pineApple->IsMaxEXP();

	SoundManager::GetInstance().PlaySoundW(L"LightOfComos'us_Se");

	float randomvalue = rand() % 2;
	if (randomvalue == 0) {
		SoundManager::GetInstance().PlaySoundW(L"SurprisedStands_Se");
		std::cout << "50light" << std::endl;
	}

	phase1Duration = 0.f;
	fadeOutDutation = 0.f;
	std::wcout << "comosus is on" << std::endl;
	cameraShaker->ShakeOnCamera(true);
	dynamicData->isHarvest = true;
	comosusLightAnim->SetAnimation(1, false);

	comosusLightAnim->gameObject->transform->m_RelativeScale.x = 1.3f * ((dynamicData->GetRewardPineAppleStat().comosusLight / 100.f) + 1.f);
	lightBox->SetExtent({ 400.f * ((dynamicData->GetRewardPineAppleStat().comosusLight / 200.f) + 1.f), 540.f });
}

void ComosusPhase1::Update(float deltaTime)
{
	float prevTime = phase1Duration;
	phase1Duration += deltaTime;
	if (phase1Duration < 0.15f) {
		if (comosusLightAnim->IsLastFrame())
			comosusLightAnim->SetAnimation(3);
	}

	if (phase1Duration < 1.f) {
		cameraShaker->SetAmplitude(phase1Duration * 20.f);
	}
	for (int i = 0; i < 40; i++) {
		if (IsTiming(prevTime, phase1Duration, (float)i / 10.f))
			OnComosusDamage();
	}

	if (prevTime < 1.f && phase1Duration >= 1.f) {
		comosusSpriteAnim->SetAnimation(1, false);
	}
	if (phase1Duration >= 1.5f && comosusSpriteAnim->IsLastFrame()) {
		fadeOutDutation += deltaTime;
		
		cameraShaker->SetAmplitude((1.f - fadeOutDutation) * 20.f);
		if (fadeOutDutation > 1.f) {
			cameraShaker->ShakeOnCamera(false);
		}
	}

	if (phase1Duration <= 2.f) {
		float value = pineApple->GetCurrentExp() * ((2.f - phase1Duration) / 2.f);
		pineApple->throwUiEXP(value);
	}

	if (phase1Duration > 1.f) {
		if (IsTiming(prevTime, phase1Duration, 1.25f)) {
			pineApple->gameObject->transform->pos.worldPosition.y += 50.f; //50
		}
		if (IsTiming(prevTime, phase1Duration, 3.25f)) {
			pineApple->gameObject->transform->pos.worldPosition.y += 100.f; // 150
		}
		if (IsTiming(prevTime, phase1Duration, 3.3f)) {
			pineApple->gameObject->transform->pos.worldPosition.y += 200.f; // 350
		}
		if (IsTiming(prevTime, phase1Duration, 3.35f)) {
			pineApple->gameObject->transform->pos.worldPosition.y += 200.f; // 550
		}
		if (IsTiming(prevTime, phase1Duration, 3.4f)) {
			pineApple->gameObject->transform->pos.worldPosition.y += 650.f; // can't see
		}
		if (prevTime < 4.0f && phase1Duration >= 4.0f) {
			fsm->SetState("Phase2");
		}
	}
}

void ComosusPhase1::Exit()
{
	pineApple->currentEXP = 0.f;
	pineApple->LV++;
	pineApple->UpdateMaxEXP();
	pineApple->RefundAll();
	if (isMaxExp) {
		pineApple->randomReward->UIon();
		//DataManager::GetInstance().plzmoney.fn();
		pineApple->randomReward->textHeader->text = pineApple->randomReward->comosusSuggestion[pineApple->LV - 2];
		auto rewardMoney = DataManager::GetInstance().getMoneyData(pineApple->GetPineAppleLV() - 2);
		pineApple->randomReward->rewardMoney->text = std::to_wstring(rewardMoney).c_str();
		GameTime::GetInstance().SetTimeScale(0.f);
	}
	cameraShaker->ShakeOnCamera(false);

	if (pineApple->LV == 6)
	{
		//SpawnNewPineapple();
		auto spr = pineApple->gameObject->GetComponent<SpriteRenderer>();
		pineApple->pineAppleLv = 2;
		spr->LoadTexture(L"../Resource/30302_02.png");
	}
	else if (pineApple->LV == 11)
	{
		//SpawnSuperPineapple();
		auto spr = pineApple->gameObject->GetComponent<SpriteRenderer>();
		pineApple->pineAppleLv = 3;
		spr->LoadTexture(L"../Resource/30303_03.png");
	}
}

bool ComosusPhase2::IsTiming(float prev, float curr, float timing)
{
	return prev < timing && curr >= timing;
}

void ComosusPhase2::OnComosusDamage()
{
	auto container = lightSeletor->GetContainer();
	for (auto enemy : container) {
		enemy->enemy->Ondamage(40.f, BulletType::Comosus, true);
	}
}

// phase2
void ComosusPhase2::Enter()
{
	std::wcout << "comosus is off" << std::endl;
	fallDuration = 0.f;
	startY = pineApple->gameObject->transform->pos.worldPosition.y;
	//dynamicData->isHarvest = false;
	//comosusLightAnim->SetAnimation(2, false);
	
}

void ComosusPhase2::Update(float deltaTime)
{

	float prevTime = fallDuration;
	fallDuration += deltaTime;
	if (IsTiming(prevTime, fallDuration, .3f)) {
		if (pineApple->LV == 6 || pineApple->LV == 11) {
			SoundManager::GetInstance().PlaySoundW(L"NewPineappleAppears_Se");
		}
	}
	if (IsTiming(prevTime, fallDuration, 2.0f)) {
		pineApple->gameObject->transform->pos.worldPosition.y = 550.f;
	}
	if (IsTiming(prevTime, fallDuration, 2.05f)) {
		pineApple->gameObject->transform->pos.worldPosition.y = 350.f;
	}
	if (IsTiming(prevTime, fallDuration, 2.1f)) {
		pineApple->gameObject->transform->pos.worldPosition.y = 150.f;
	}
	if (IsTiming(prevTime, fallDuration, 2.15f)) {
		pineApple->gameObject->transform->pos.worldPosition.y = 0.f;
		comosusSpriteAnim->SetAnimation(2, false);
	}
	if (fallDuration > 2.2f) {
		if (comosusSpriteAnim->IsLastFrame()) {
			comosusSpriteAnim->SetAnimation(0, false);
		}
	}

	for (int i = 0; i < 40; i++) {
		if (IsTiming(prevTime, fallDuration, i / 10.f))
			OnComosusDamage();
	}

	if (fallDuration > 4.f) {
		fallDuration = 4.f;
		fsm->SetState("Default");
	}
	//float value = pow(time, 3);

	//pineApple->gameObject->transform->pos.worldPosition.y = startY + (0.f - startY) * (0.2f + 0.8f * value);
}

void ComosusPhase2::Exit()
{
	comosusSpriteAnim->SetAnimation(0, false);
	comosusLightAnim->SetAnimation(0, false);
	dynamicData->isHarvest = false;
	pineApple->SetMaxHP(50.f);
}
