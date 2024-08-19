#pragma once
#include "../D2DEngine/Component.h"
#include <functional>

class SpriteUIAnimation;
class Cutton : public Component
{
public:
	SpriteUIAnimation* UiCutton;
	Cutton(){}
	virtual void Update(float deltaTime);

	std::function<void()> ctfn;
	bool check = false;
};

