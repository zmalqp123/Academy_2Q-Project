#include "WaveSystem.h"
#include <iostream> 

void WaveSystem::Update(float deltaTime)
{
    // 몬스터가 맵에 남아있는지 확인하는 부분은 RemoveMonster가 아닌 다른 시스템에서 처리
    waveTimer -= deltaTime;  // deltaTime 만큼 waveTimer 감소
    if (waveTimer <= 0.0f)
    {
        StartNextWave();
    }
}

// SpawnWave 함수: 현재 wave에 해당하는 몬스터를 스폰.
void WaveSystem::SpawnWave()
{
    int numMonstersToSpawn = currentWave; // 현재 웨이브 번호에 따라 몬스터 수 결정

    for (int i = 0; i < numMonstersToSpawn; ++i)
    {
        // 몬스터 스폰 로직
        std::cout << "몬스터가 생성되었습니다" << std::endl;
        // 실제 몬스터 생성 코드 나중에 하기
    }
}

// StartNextWave 함수: wave를 진행시키고 타이머를 초기화
void WaveSystem::StartNextWave()
{
    if (currentWave < maxWave)
    {
        currentWave++;
        waveTimer = 1.0f;  // 타이머 초기화
        SpawnWave();        // 새로운 wave 스폰
    }
    // maxWave에 도달했을 경우 추가적인 처리 필요 (게임 종료 또는 루프 등)
}

// IsMapEmpty 함수: 맵에 몬스터가 하나도 없는지 확인
bool WaveSystem::IsMapEmpty()
{
    // 맵에서 몬스터가 남아있는지 확인하는 로직 (필요 시 사용)
    return false;  // 기본적으로 false 반환
}
