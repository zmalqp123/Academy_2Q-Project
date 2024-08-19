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
        std::cout << "���� ���� ���ξ��� ��� : " << gold << std::endl;
    } 
}

// ���Ϳ��� ȣ�� 
void MainPineApple::monAcquireEXP(float exp)
{
    float dyKillMultiply = rewardData->GetRewardPineAppleStat().killMultiply;
    // ���ͷκ��� ����ġ�� ȹ��
    currentEXP += exp * (killMultiply + dyKillMultiply);

    // currentEXP�� maxEXP�� �ʰ��ϸ� maxEXP���� ����
    if (currentEXP > maxEXP)
    {
        currentEXP = maxEXP;
    }
}

// ���� atk ���� ȣ�� 
void MainPineApple::pineAppleDamageHP(int damage)
{
    if (HP > 0)
    {
        std::cout << "�ʱ� HP : " << HP << std::endl;
        HP -= damage;
        std::cout << "������ �� HP : " << HP << std::endl;
    }
    else
    {
        HP = 0;
    }
}

void MainPineApple::solarAcquireEXP(float deltaTime)
{
    // ���� ����ġ�� ������Ű����, �ִ� maxEXP������ ���
    if (currentEXP <= maxEXP)
    {
        currentEXP += solarGain * deltaTime;

        // currentEXP�� maxEXP�� �ʰ��ϸ� maxEXP���� ����
        if (currentEXP >= maxEXP)
        {
            currentEXP = maxEXP;
        }
    }
}

void MainPineApple::throwUiEXP(int currentEXP)
{
    // maxEXP�� 100�̰� currentEXP�� 0���� 100 ������ ��쿡�� ����
    if ( currentEXP >= 0 && currentEXP <= maxEXP)
    {
        expbar->ImageRender->slideBar = currentEXP / maxEXP;
    }
}

void MainPineApple::throwUiHP(int HP)
{
    // HP�� maxHP�� �ʰ��ϰų� 0 �̸����� �������� �ʵ��� ����
    if (HP < 0)
        HP = 0;
    else if (HP > maxHP)
        HP = maxHP;

    // UI �ٸ� ������Ʈ (������ ����Ͽ� ����)
    hpbar->ImageRender->slideBar = HP / maxHP;
}

void MainPineApple::UpdateMaxEXP()
{
    maxEXP = EXP_TABLE[LV - 1];
}

void MainPineApple::Harvest()
{
    // HP ȸ��
    HP = maxHP;

    
    // ����ġ�� �ִ�ġ�� ���
    if (currentEXP == maxEXP)
    {
        //UpdateMaxEXP(); // ���ο� �ִ� ����ġ ����
        std::cout << "���� ��! ���� ����: " << LV << std::endl;
        //currentEXP = 0;

        // 4. ���ο� ���ξ��� ����
        if (LV >= 5 && LV < 11)
        {
            //SpawnNewPineapple();
        }
        else if (LV >= 11)
        {
            //SpawnSuperPineapple();
        }

        // �ڸ𼭽� �ִϸ��̼� ���
        //comosus->SetAnimation(1, false);
        comosusFsm->SetState("Phase1");

        // �ͷ� ��Ȱ��ȭ
        
        // ���� ��ư Ȱ��ȭ
        //randomReward->UIon();

        // ���� ���� �Ϸ� �� ��� �ͷ� ��Ȱ��ȭ (���� ����)
    }
    else
    {
        // ��Ȯ ���� ���� Ȯ�� (��: ���� ����ġ�� Ư�� ���� �̻��� ��)
        if (HarvestAble())
        {
            std::cout << "�ִ����ġ ���� ��Ȯ: " << maxEXP << std::endl;
            //UpdateMaxEXP(); // ���ο� �ִ� ����ġ ����
            //currentEXP = 0;

            // 4. ���ο� ���ξ��� ����
            if (LV >= 5 && LV < 11)
            {
                //SpawnNewPineapple();
            }
            else if (LV >= 11)
            {
                //SpawnSuperPineapple();
            }

            // �ڸ𼭽� �ִϸ��̼� ���
            //comosus->SetAnimation(1, false);
            comosusFsm->SetState("Phase1");

            // �ͷ� ��Ȱ��ȭ
            //DisableAllTurrets();

            // ���� ��ư Ȱ��ȭ
            //randomReward->UIon();

            // ���� ���� �Ϸ� �� ��� �ͷ� ��Ȱ��ȭ (���� ����)
        }
        else
        {
            std::cout << "��Ȯ �Ұ�: " << maxEXP << std::endl;
        }
    }
}

void MainPineApple::DisableRewardButtons()
{
    // ���� ��ư���� ��Ȱ��ȭ�ϴ� �Լ�
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
        // �ʴ� ��Ȯ��
        if (waveSystem->getCurrentWave() % 4 != 0) {
            solarAcquireEXP(deltaTime);
        }

        // UI HP�� ������Ʈ  
        throwUiHP(GetPineAppleHP());
    
        // UI MP�� ������Ʈ 
        throwUiEXP(GetCurrentExp());

        goldbar->text = std::to_wstring( GetPineAppleGold()).c_str();



        LVbar->text = std::to_wstring(GetPineAppleLV()).c_str();

    }

    // ��Ȯ ��ư Ȱ��ȭ
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
