#pragma once
#include "../D2DEngine/Component.h"

class Mpbar; // 선언
class ImageUIRenderer;
class HarvestButton : public Component
{
private:
    float HarvestMp; // 수확에 필요한 경험치
    float maxExperience; // 최대 경험치
    float harvestMinmumGage = 0.75f;

    // 수확 가능구간 변수
    void UpdateButtonOpacity(); // 버튼의 투명도 업데이트
public:

    ImageUIRenderer* ImageRender;
    HarvestButton();

    Mpbar* mp; // Mpbar 객체에 대한 포인터

    // 수확가능 여부 체크 
    bool HarvestAble();

    // 버튼 상태 업데이트
    void Update(float deltaTime);
};
