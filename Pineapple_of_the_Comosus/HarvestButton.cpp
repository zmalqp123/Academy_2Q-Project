#include "HarvestButton.h"
#include "Mpbar.h"

HarvestButton::HarvestButton()
    : HarvestMp(0.0f), maxExperience(100.0f), isHarvestable(false)
{
}

void HarvestButton::Harvest()
{
    if (isHarvestable)
    {
        // 수확 로직 구현
    }
}

void HarvestButton::UpdateButtonOpacity()
{
    // 버튼의 Opacity를 설정하는 로직
    // opacity 값의 범위는 0 (완전히 투명)에서 1 (완전히 불투명)까지
    float opacity = isHarvestable ? 1.0f : 0.0f; // 수확 가능 여부에 따라 opacity 조정

    // 버튼의 UI 컴포넌트에서 opacity 값을 설정하는 메서드 호출
    // 예: buttonUI->SetOpacity(opacity); 또는 buttonUI->opacity = opacity;
    // 버튼 UI 컴포넌트의 종류에 따라 다를 수 있습니다.
}

void HarvestButton::Update(float deltaTime)
{
    // 경험치를 확인하고 수확 가능 여부를 설정
    if (mp)
    {
        float currentExperience = mp->getCurrMp(); // Mpbar의 현재 경험치를 가져오는 함수
        isHarvestable = (currentExperience >= maxExperience * 0.75f);

        // 버튼의 투명도 업데이트
        UpdateButtonOpacity();
    }
}
