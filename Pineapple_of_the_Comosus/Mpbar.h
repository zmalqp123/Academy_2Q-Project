#pragma once
#include "../D2DEngine/Component.h"

class ImageUIRenderer;
class Mpbar : public Component
{
private:
	float maxMp; // 최대 Mp
	float currentMp; // 현재 Mp
public:
	ImageUIRenderer* ImageRender;
	// 기본 생성자 
	Mpbar();
    
	// 생성자: 체력 바의 최대 체력과 너비를 초기화
    Mpbar(float initialHp, float width);
	
	// Mp 업데이트: 몬스터의 mp에 따른 파인애플 mp 증가 
	void takeMp(float manaPoint);

	// Mp 바의 현재 상태를 반환 
	float getCurrMp() const;

	// Mp 바의 현재 너비를 계산
	float getBarWidth() const;


};

