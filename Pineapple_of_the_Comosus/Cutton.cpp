#include "Cutton.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/SpriteUIAnimation.h"

void Cutton::Update(float deltaTime)
{
	if (UiCutton->IsLastFrame())
	{
		UiCutton->SetAnimation(1, false);
		if (check == true) {
			if (ctfn) ctfn();
		}
	}
}


