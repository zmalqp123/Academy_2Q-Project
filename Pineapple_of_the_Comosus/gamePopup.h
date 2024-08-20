#pragma once
#include <vector>
#include <string>

class Button;
class ImageUIRenderer;
class gamePopup
{
public:
	std::vector<Button*> btns;
	std::vector<ImageUIRenderer*> Uis;
	void UIon();
	void UIoff();
};

