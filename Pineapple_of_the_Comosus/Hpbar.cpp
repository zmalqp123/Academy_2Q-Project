#include "Hpbar.h"

// 기본 생성자
Hpbar::Hpbar()
    : maxHp(100.0f), currentHp(100.0f) {}

// 생성자: 체력 바의 최대 체력과 너비를 초기화
Hpbar::Hpbar(float initialHp, float width)
    : maxHp(initialHp), currentHp(initialHp) {}

// 체력 업데이트: 몬스터의 공격에 따른 체력 감소
void Hpbar::takeDamage(float damage)
{
    currentHp -= damage;
    if (currentHp < 0)
        currentHp = 0; // 체력은 0보다 작을 수 없다.
}

// 체력 바의 현재 상태를 반환
float Hpbar::getCurrentHp() const
{
    return currentHp;
}

// 체력 바의 현재 너비를 계산
float Hpbar::getBarWidth() const
{
    return (currentHp / maxHp);
}
