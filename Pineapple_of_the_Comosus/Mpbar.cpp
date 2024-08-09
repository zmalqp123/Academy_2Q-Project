#include "Mpbar.h"

Mpbar::Mpbar()
	: maxMp(100.0f), currentMp(0.0f) {}

Mpbar::Mpbar(float initialHp, float width)
	: maxMp(initialHp), currentMp(initialHp) {}

void Mpbar::takeMp(float manaPoint)
{
	currentMp += manaPoint;
	if (currentMp >= 100)
		currentMp = 100;
}

float Mpbar::getCurrMp() const 
{
	return currentMp;
}

float Mpbar::getBarWidth() const
{
	return (currentMp / maxMp);
}
