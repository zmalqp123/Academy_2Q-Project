#include "gamePopup.h"
#include "../D2DEngine/GameObject.h"

void gamePopup::victoryUIon()
{
	for (auto element : victory)
	{
		element->isActive = true;
	}
}

void gamePopup::victoryUIoff()
{
	for (auto element : victory)
	{
		element->isActive = false;
	}
}

void gamePopup::defeatUIon()
{
	for (auto element : defeat)
	{
		element->isActive = true;
	}
}

void gamePopup::defeatUIoff()
{
	for (auto element : defeat)
	{
		element->isActive = false;
	}
}
