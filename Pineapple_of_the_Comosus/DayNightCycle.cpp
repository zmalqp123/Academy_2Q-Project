#include "DayNightCycle.h"
#include "../D2DEngine/Scene.h"
#include "../D2DEngine/SpriteRenderer.h"
#include "../D2DEngine/Transform.h"
#include "iostream"
#include "../D2DEngine/SoundManager.h"
//DayNightCycle::DayNightCycle(WaveSystem* waveSystem)
//    : isNight(false), waveSystem(waveSystem) {}

void DayNightCycle::Update(float deltaTime) {
    //int curWave = waveSystem->getCurrentWave();

    ////std::cout << curWave;
    //// 4의 배수 웨이브에서 밤이 된다.
    //if (curWave % 4 == 0 && curWave != 0) {
    //    if (!isNight) {
    //        isNight = true;
    //        ApplyNightEffects();
    //    }
    //}
    //else {
    //    if (isNight) {
    //        isNight = false;
    //        RemoveNightEffects();
    //    }
    //}
}

bool DayNightCycle::IsNight() const {
    return isNight;
}

void DayNightCycle::ApplyNightEffects(int wave) {
    // 추가하기
    /*waveSystem->IncreaseEnemyAttackPower(0.25f);
    waveSystem->SetHarvestExperience(0.0f);*/
    if (wave % 4 == 0) {
        //std::cout << "밤" << std::endl;
        //SoundManager::GetInstance().PlaySoundW(L"Night_Bgm", false);
    }
}

void DayNightCycle::RemoveNightEffects(int wave) {
    // 추가하기
    //waveSystem->IncreaseEnemyAttackPower(-0.25f);
    //waveSystem->SetHarvestExperience(1.0f); // 기본 수확 경험치를 원래대로 되돌리기
    if (wave % 4 != 0) {
        //std::cout << "낮" << std::endl;
        //SoundManager::GetInstance().PlaySoundW(L"Morning_Bgm", false);
    }
}

void DayNightCycle::SunMove(float deltaTime, int period)
{
    static float elapsedTime = 0.0f;
    static int prevPeriod = 1;
    int curPeriod = period;
    elapsedTime += deltaTime;
    if (period == 3) SunReset();
    else {
        if (elapsedTime < 1.0f) {
            if (m_Sun != nullptr)
                m_Sun->transform->pos.worldPosition.y = (1 - elapsedTime) * sunLocation[period] + elapsedTime * sunLocation[period + 1];
        }
        else if (elapsedTime >= 1.0f && prevPeriod != curPeriod) {
            elapsedTime = 0.0f;
        }
    }
    prevPeriod = curPeriod;
}


void DayNightCycle::SunReset()
{
    if (m_Sun != nullptr)
        m_Sun->transform->pos.worldPosition.y = sunLocation[0];
}

void DayNightCycle::MoonMove(float deltaTime, int period)
{
    static float elapsedTime = 0.0f;
    static int prevPeriod = 1;
    int curPeriod = period;
    elapsedTime += deltaTime;
    if (period == 3) MoonReset();
    else {
        if (elapsedTime < 1.0f) {
            if (m_Moon != nullptr) {
                m_Moon->transform->pos.worldPosition.y = (1 - elapsedTime) * moonLocation[period] + elapsedTime * moonLocation[period + 1];
                if (m_Moon->transform->pos.worldPosition.y < -300.f) MoonReset();
            }


        }
        else if (elapsedTime >= 1.0f && prevPeriod != curPeriod) {
            elapsedTime = 0.0f;
        }
    }
    prevPeriod = curPeriod;
}

void DayNightCycle::MoonReset()
{
    m_Moon->transform->pos.worldPosition.y = moonLocation[0];

}

void DayNightCycle::SwitchBackGround(float deltaTime, int period)
{
	//static float elapsedTime = 0.0f;
	elapsedTime += deltaTime;
	//static int prevPeriod = 0;
	int curPeriod = period;
	bool isTurned = false;
    
    if (prevPeriod != curPeriod) elapsedTime = 0.f;

    if (period % 4 == 0) {
        // night
        if (elapsedTime > 1.f) elapsedTime = 1.f;

        float dayTonight = elapsedTime * 180.f;
        backGroundDay->transform->m_RelativeRotation = dayTonight;
        cloudDay->transform->m_RelativeRotation = dayTonight;
        Mountain1Day->transform->m_RelativeRotation = dayTonight;
        Mountain2Day->transform->m_RelativeRotation = dayTonight;
        Mountain3Day->transform->m_RelativeRotation = dayTonight;
        float nightToday = elapsedTime * 180.f + 180.f;
		backGroundNight->transform->m_RelativeRotation = nightToday;
		cloudNight->transform->m_RelativeRotation = nightToday;
		Mountain1Night->transform->m_RelativeRotation = nightToday;
		Mountain2Night->transform->m_RelativeRotation = nightToday;
		Mountain3Night->transform->m_RelativeRotation = nightToday;
    }

    else if(period % 4 == 1) {
		// morning if (elapsedTime > 1.f) elapsedTime = 1.f;
        if (elapsedTime > 1.f) elapsedTime = 1.f;
        float dayTonight = elapsedTime * 180.f + 180.f;
        backGroundDay->transform->m_RelativeRotation = dayTonight;
        cloudDay->transform->m_RelativeRotation = dayTonight;
        Mountain1Day->transform->m_RelativeRotation = dayTonight;
        Mountain2Day->transform->m_RelativeRotation = dayTonight;
        Mountain3Day->transform->m_RelativeRotation = dayTonight;
		float nightToday = elapsedTime * 180.f + 360.f;
		backGroundNight->transform->m_RelativeRotation = nightToday;
        cloudNight->transform->m_RelativeRotation = nightToday;
        Mountain1Night->transform->m_RelativeRotation = nightToday;
        Mountain2Night->transform->m_RelativeRotation = nightToday;
        Mountain3Night->transform->m_RelativeRotation = nightToday;
    }

	
    prevPeriod = curPeriod;
	
}



