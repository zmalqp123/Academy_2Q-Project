#pragma once
#include "../D2DEngine/Component.h"

class ImageUIRenderer;
class Hpbar : public Component
{
private:
    float maxHp;          // 최대 체력
    float currentHp;      // 현재 체력

public:

    ImageUIRenderer* ImageRender;
    // 기본 생성자
    Hpbar();
    // 생성자: 체력 바의 최대 체력과 너비를 초기화
    Hpbar(float initialHp, float width);

    // 체력 업데이트: 몬스터의 공격에 따른 체력 감소
    void takeDamage(float damage);

    // 체력 바의 현재 상태를 반환
    float getCurrentHp() const;

    // 체력 바의 현재 너비를 계산
    float getBarWidth() const;

};
