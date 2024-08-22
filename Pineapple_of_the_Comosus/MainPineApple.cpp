#include "MainPineApple.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/ImageUIRenderer.h"
#include "../D2DEngine/SpriteAnimation.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/GameTime.h"
#include "../D2DEngine/TextUIRenderer.h"
#include "../D2DEngine/Button.h"
#include "../D2DEngine/SpriteUIAnimation.h"
#include "Mpbar.h"
#include "Hpbar.h"
#include "DynamicData.h"
#include "Comosus.h"
#include <iostream>
#include <random>
#include "ramdomReward.h"
#include "ComosusFSM.h"
#include "WaveSystem.h"
#include "gamePopup.h"
#include "../D2DEngine/SoundManager.h"

void MainPineApple::PrintIndex(int index)
{
    //std::cout << index << std::endl;
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
        //std::cout << "alive pineapple : " << gold << std::endl;
    } 
}

// monster call
void MainPineApple::monAcquireEXP(float exp)
{
    float dyKillMultiply = rewardData->GetRewardPineAppleStat().killMultiply;
    // from monster acquire

    AddExp(exp * (killMultiply + dyKillMultiply));
}

// monster atk call
void MainPineApple::pineAppleDamageHP(int damage)
{
    if (HP > 0)
    {
        //std::cout << "start HP : " << HP << std::endl;
        HP -= damage;
        std::cout << HP << std::endl;

        float randomvalue = rand() % 2;
        if (randomvalue == 0) {
            SoundManager::GetInstance().PlaySoundW(L"BooingStands_Se");
        }

        //std::cout << "later HP : " << HP << std::endl;
        if (HP < 0.f) {
            HP = 0;
            isDie = true;
        }
    }
    else
    {
        HP = 0;
        isDie = true;
    }
}

void MainPineApple::solarAcquireEXP(float deltaTime)
{   
    if (waveSystem->getCurrentWave() % 4 != 0) {
		solarGain = morningValue + rewardData->GetRewardPineAppleStat().morningValue;
	}
    else if (waveSystem->getCurrentWave() % 4 == 0) {
        solarGain = nightValue + rewardData->GetRewardPineAppleStat().nightValue;
    }

    // maxexp ok
    if (currentEXP <= maxEXP)
    {
        float tmp = solarGain + rewardData->GetRewardPineAppleStat().solarGain;
        AddExp(tmp * deltaTime);
    }
}

void MainPineApple::throwUiEXP(int currentEXP)
{
    if ( currentEXP >= 0 && currentEXP <= maxEXP)
    {
        expbar->ImageRender->slideBar = currentEXP / maxEXP;
    }
}

void MainPineApple::throwUiHP(int HP)
{
    if (HP < 0)
        HP = 0;
    else if (HP > maxHP + rewardData->GetRewardPineAppleStat().maxHp)
        HP = maxHP + rewardData->GetRewardPineAppleStat().maxHp;

    hpbar->ImageRender->slideBar = HP / (maxHP + rewardData->GetRewardPineAppleStat().maxHp);
}

void MainPineApple::UpdateMaxEXP()
{
    maxEXP = EXP_TABLE[LV - 1];
}

void MainPineApple::Harvest()
{
    // HP recover
    HP = maxHP + rewardData->GetRewardPineAppleStat().maxHp;

    
    // maxexp
    if (currentEXP == maxEXP)
    {
        //UpdateMaxEXP(); // set new harvestexp
        //std::cout << "low harvest : " << LV << std::endl;
        //currentEXP = 0;

        // 4.  new pineapple generation
        if (LV >= 5 && LV < 11)
        {
            //SpawnNewPineapple();
        }
        else if (LV >= 11)
        {
            //SpawnSuperPineapple();
        }

        // comosus animation play
            //comosus->SetAnimation(1, false);
        comosusFsm->SetState("Phase1");

    }
    else
    {
        // harvestable check
        if (HarvestAble())
        {
            //std::cout << "low harvest : " << maxEXP << std::endl;
            //UpdateMaxEXP(); // set new harvestexp
            //currentEXP = 0;

            // 4. new pineapple generation
            if (LV >= 5 && LV < 11)
            {
                //SpawnNewPineapple();
            }
            else if (LV >= 11)
            {
                //SpawnSuperPineapple();
            }

            // comosus animation play
            //comosus->SetAnimation(1, false);
            comosusFsm->SetState("Phase1");

        }
        else
        {
            std::cout << "cant harvest: " << maxEXP << std::endl;
        }
    }
}

MainPineApple::MainPineApple()
{
    // 사운드 초기화 및 로드
    // 수확가능시
    SoundManager::GetInstance().LoadSound(L"HarvestOn_Se", L"../Media/6_Sound/scene3/Se/HarvestOn_Se.wav");
    SoundManager::GetInstance().SetVolume(L"HarvestOn_Se", 0.5f);  

    // 풍족한 수확가능시
    SoundManager::GetInstance().LoadSound(L"HarvestOn_Se", L"../Media/6_Sound/scene3/Se/HarvestOn_Se.wav");
    SoundManager::GetInstance().SetVolume(L"HarvestOn_Se", 0.5f);

}

void MainPineApple::DisableRewardButtons()
{
    for (auto& element : rewardbtn)
    {
        element->isActive = false;
    }
}

bool MainPineApple::HarvestAble()
{
    return currentEXP >= GetOfferingValue();
}

float MainPineApple::GetOfferingValue()
{
    return maxEXP * (offeringMultiply + rewardData->GetRewardPineAppleStat().offeringMultiply);
}

void MainPineApple::Update(float deltaTime)
{
    if (isWin == true) {
        dieTime += deltaTime;
        if (dieTime >= 1.f) {
            dieTime = 0.f;
            GameTime::GetInstance().SetTimeScale(0.f);
            endpopup->victoryUIon();
        }
    }
    if (isDie == true)
    {
        dieTime += deltaTime;
        if (dieTime >= 1.f) {
            dieTime = 0.f;
            GameTime::GetInstance().SetTimeScale(0.f);
            endpopup->defeatUIon();
        }
    }

    if (rewardData->isHarvest == false) {
        // second per haverst
        //if (waveSystem->getCurrentWave() % 4 != 0) 
        solarAcquireEXP(deltaTime);


        // UI HPbar update  
        throwUiHP(GetPineAppleHP());
    
        // UI MPbar update
        throwUiEXP(GetCurrentExp());

        goldbar->text = std::to_wstring( GetPineAppleGold()).c_str();



        LVbar->text = std::to_wstring(GetPineAppleLV()).c_str();

    }

    UpdateHarvestableAnim();

    // harvest open
    if (HarvestAble() && rewardData->isHarvest == false)
    {
        harvestbtn->LoadTexture(L"../Resource/30208_Harvest1btn.png");
    }
    else
    {
        harvestbtn->LoadTexture(L"../Resource/30208_Harvest2btn.png");
    }
}

void MainPineApple::RefundAll()
{
    for (auto turret : turrets) {
        turret->Refund();
    }
}

void MainPineApple::SetMaxHP(float increaseHp)
{
    maxHP += increaseHp;
    HP = +rewardData->GetRewardPineAppleStat().maxHp + maxHP;
}

void MainPineApple::UpdateTurretImage()
{
    for (auto turret : turrets) {
        turret->UpdateTurretImage();
    }
}

bool MainPineApple::IsMaxEXP()
{
    return currentEXP == maxEXP;
}

void MainPineApple::AddExp(float exp)
{
    float prev = currentEXP;
    currentEXP += exp;

    float offeringValue = offeringMultiply + rewardData->GetRewardPineAppleStat().offeringMultiply;
    offeringValue *= maxEXP;

    if(prev < offeringValue  && currentEXP >= offeringValue){
        // 수확가능시 사운드
        SoundManager::GetInstance().PlaySoundW(L"HarvestOn_Se");
    }

    if (prev != maxEXP && currentEXP >= maxEXP)
    {
        // 풍족한 사운드
        SoundManager::GetInstance().PlaySoundW(L"HarvestOn_Se");
    }


    if (currentEXP > maxEXP)
        currentEXP = maxEXP;
}

void MainPineApple::UpdateHarvestableAnim()
{
    float bar = expbar->ImageRender->slideBar;

    float offeringValue = offeringMultiply + rewardData->GetRewardPineAppleStat().offeringMultiply;

    //{ 385.f, 7.f }, { 1200.f,27.f }
    float width = 1200.f - 385.f;
    width *= offeringValue;
    width += 385.f;

    if (std::abs(offeringValue - prevOfferingValue) > 0.01f) {
        std::cout << "수확가능 구간 변경됨" << std::endl;
        prevOfferingValue = offeringValue;

        if (std::abs(prevOfferingValue - 0.75f) < 0.01f) {
            harvestableAnim->LoadTexture(L"../Resource/30407_01.png");
            harvestableAnim->LoadAnimationAsset(L"HarvestAbleBar75");
        }
        else if (std::abs(prevOfferingValue - 0.70f) < 0.01f) {
            harvestableAnim->LoadTexture(L"../Resource/30407_02.png");
            harvestableAnim->LoadAnimationAsset(L"HarvestAbleBar70");
        }
        else if (std::abs(prevOfferingValue - 0.65f) < 0.01f) {
            harvestableAnim->LoadTexture(L"../Resource/30407_03.png");
            harvestableAnim->LoadAnimationAsset(L"HarvestAbleBar65");
        }
        else if (std::abs(prevOfferingValue - 0.60f) < 0.01f) {
            harvestableAnim->LoadTexture(L"../Resource/30407_04.png");
            harvestableAnim->LoadAnimationAsset(L"HarvestAbleBar60");
        }
        else if (std::abs(prevOfferingValue - 0.55f) < 0.01f) {
            harvestableAnim->LoadTexture(L"../Resource/30407_05.png");
            harvestableAnim->LoadAnimationAsset(L"HarvestAbleBar55");
        }
        else if (std::abs(prevOfferingValue - 0.50f) < 0.01f) {
            harvestableAnim->LoadTexture(L"../Resource/30407_06.png");
            harvestableAnim->LoadAnimationAsset(L"HarvestAbleBar50");
        }
        else if (std::abs(prevOfferingValue - 0.45f) < 0.01f) {
            harvestableAnim->LoadTexture(L"../Resource/30407_07.png");
            harvestableAnim->LoadAnimationAsset(L"HarvestAbleBar45");
        }
        else if (std::abs(prevOfferingValue - 0.40f) < 0.01f) {
            harvestableAnim->LoadTexture(L"../Resource/30407_08.png");
            harvestableAnim->LoadAnimationAsset(L"HarvestAbleBar40");
        }
        else {
            harvestableAnim->LoadTexture(L"../Resource/30407.png");
            harvestableAnim->LoadAnimationAsset(L"HarvestAbleBar");
        }
        harvestableAnim->SetAnimation(0, false);
    }

    harvestableAnim->gameObject->transform->pos.rectposition.leftBottom.x = width;
    //std::cout << "width : " << width << std::endl;

    if (bar >= offeringValue) {
        if (bar >= 1.f) {
            // max
            harvestableAnim->SetAnimation(1, false, true);
        }
        else {
            // 수확가능하지만 max아님
            harvestableAnim->SetAnimation(0, false);
        }
    }
}
