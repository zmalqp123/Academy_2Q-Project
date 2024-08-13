#pragma once
#include <vector>
#include <string>


struct reward
{
    std::wstring name;
};


class HarvestReward
{
public:
    // 보상 유형 선택지 벡터
    std::vector<int> rewards; // 선택지 리스트

public:
    HarvestReward();
    ~HarvestReward();

    // 보상 선택지를 초기화하는 함수
    void InitializeRewards();


    // UI에 보상 선택지를 표시하는 함수 (구현은 UI 시스템에 의존)
    void DisplayRewardsUI();


};

