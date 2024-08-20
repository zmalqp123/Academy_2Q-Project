#include "ramdomReward.h"
#include "DataManager.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Button.h"
#include "../D2DEngine/ImageUIRenderer.h"
#include "../D2DEngine/TextUIRenderer.h"
#include "../D2DEngine/GameTime.h"
#include "random"


void ramdomReward::shuffle()
{
    // 보상 목록을 랜덤하게 섞음

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(DataManager::GetInstance().harvestPopupStruct.begin(), DataManager::GetInstance().harvestPopupStruct.end(), g);
}

void ramdomReward::setValue()
{
    for (int i = 0; i < 4; i++)
    {
        btns[i]->AddListener([this, i]() {
            int a = i;
            DataManager::GetInstance().harvestPopupStruct[a].fn(); 
            std::wcout << L"ddd: " << a << std::endl;
            UIoff();  
            GameTime::GetInstance().SetTimeScale(1.f);
            });
        Uis[i]->LoadTexture(DataManager::GetInstance().harvestPopupStruct[i].Imagepath.c_str());
        TextNameUis[i]->text = DataManager::GetInstance().harvestPopupStruct[i].reward;
        TextStatUis[i]->text = DataManager::GetInstance().harvestPopupStruct[i].rewarOption;
    }
    btns[4]->AddListener([this]() {
      
        DataManager::GetInstance().plzmoney.fn();
        UIoff();
        GameTime::GetInstance().SetTimeScale(1.f);
        });
}

void ramdomReward::UIon()
{
    shuffle();
    setValue();
    for (auto element : btns)
    {
        element->gameObject->isActive = true;
    }
    for (auto element : Uis)
    {
        element->gameObject->isActive = true;
    }
    for (auto element : TextNameUis)
    {
        element->gameObject->isActive = true;
    }
    for (auto element : TextStatUis)
    {
        element->gameObject->isActive = true;
    }
    for (auto element : bgUi)
    {
        element->isActive = true;
    }

}

void ramdomReward::UIoff()
{
    for (auto element : btns)
    {
        element->gameObject->isActive = false;
    }
    for (auto element : Uis)
    {
        element->gameObject->isActive = false;
    }
    for (auto element : TextNameUis)
    {
        element->gameObject->isActive = false;
    }
    for (auto element : TextStatUis)
    {
        element->gameObject->isActive = false;
    }
    for (auto element : bgUi)
    {
        element->isActive = false;
    }
}
