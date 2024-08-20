#include "MainPineApple.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/ImageUIRenderer.h"
#include "../D2DEngine/SpriteAnimation.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/GameTime.h"
#include "../D2DEngine/TextUIRenderer.h"
#include "../D2DEngine/Button.h"
#include "Mpbar.h"
#include "Hpbar.h"
#include "DynamicData.h"
#include "Comosus.h"
#include <iostream>
#include <random>
#include "ramdomReward.h"
#include "ComosusFSM.h"
#include "WaveSystem.h"

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
        //std::cout << "later HP : " << HP << std::endl;
    }
    else
    {
        HP = 0;
    }
}

void MainPineApple::solarAcquireEXP(float deltaTime)
{   
    if (waveSystem->getCurrentWave() % 4 != 0) {
		solarGain = morningValue;
	}
    else if (waveSystem->getCurrentWave() % 4 == 0) {
        solarGain = nightValue;
    }

    // maxexp ok
    if (currentEXP <= maxEXP)
    {
        AddExp(solarGain * deltaTime);
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
    currentEXP += exp;
    if (currentEXP > maxEXP)
        currentEXP = maxEXP;
}
