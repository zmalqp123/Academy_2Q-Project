#include "MainPineApple.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/ImageUIRenderer.h"
#include "../D2DEngine/SpriteAnimation.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/GameTime.h"
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
        expbar->ImageRender->slideBar = currentEXP / maxEXP;
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
    hpbar->ImageRender->slideBar = HP / maxHP;
}

void MainPineApple::UpdateMaxEXP()
{
    maxEXP = EXP_TABLE[LV - 1];
}

void MainPineApple::Harvest()
{
    // HP 회복
    HP = maxHP;

    
    // 경험치가 최대치인 경우
    if (currentEXP == maxEXP)
    {
        //UpdateMaxEXP(); // 새로운 최대 경험치 설정
        std::cout << "레벨 업! 현재 레벨: " << LV << std::endl;
        //currentEXP = 0;

        // 4. 새로운 파인애플 생성
        if (LV >= 5 && LV < 11)
        {
            //SpawnNewPineapple();
        }
        else if (LV >= 11)
        {
            //SpawnSuperPineapple();
        }

        // 코모서스 애니메이션 재생
        //comosus->SetAnimation(1, false);
        comosusFsm->SetState("Phase1");

        // 터렛 비활성화
        
        // 보상 버튼 활성화
        //randomReward->UIon();

        // 보상 선택 완료 후 모든 터렛 재활성화 (추후 구현)
    }
    else
    {
        // 수확 가능 조건 확인 (예: 현재 경험치가 특정 비율 이상일 때)
        if (HarvestAble())
        {
            std::cout << "최대경험치 이하 수확: " << maxEXP << std::endl;
            //UpdateMaxEXP(); // 새로운 최대 경험치 설정
            //currentEXP = 0;

            // 4. 새로운 파인애플 생성
            if (LV >= 5 && LV < 11)
            {
                //SpawnNewPineapple();
            }
            else if (LV >= 11)
            {
                //SpawnSuperPineapple();
            }

            // 코모서스 애니메이션 재생
            //comosus->SetAnimation(1, false);
            comosusFsm->SetState("Phase1");

            // 터렛 비활성화
            //DisableAllTurrets();

            // 보상 버튼 활성화
            //randomReward->UIon();

            // 보상 선택 완료 후 모든 터렛 재활성화 (추후 구현)
        }
        else
        {
            std::cout << "수확 불가: " << maxEXP << std::endl;
        }
    }
}

void MainPineApple::DisableRewardButtons()
{
    // 보상 버튼들을 비활성화하는 함수
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
        // 초당 수확량
        if (waveSystem->getCurrentWave() % 4 != 0) {
            solarAcquireEXP(deltaTime);
        }

        // UI HP바 업데이트  
        throwUiHP(GetPineAppleHP());

        // UI MP바 업데이트 
        throwUiEXP(GetCurrentExp());
    }

    // 수확 버튼 활성화
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
