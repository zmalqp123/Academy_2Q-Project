#include "gamePopup.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Button.h"
#include "../D2DEngine/ImageUIRenderer.h"

void gamePopup::UIon()
{
	for (auto element : btns)
	{
		element->gameObject->isActive = true;
	}
	for (auto element : Uis)
	{
		element->gameObject->isActive = true;
	}
}

void gamePopup::UIoff()
{
	for (auto element : btns)
	{
		element->gameObject->isActive = false;
	}
	for (auto element : Uis)
	{
		element->gameObject->isActive = false;
	}
}
