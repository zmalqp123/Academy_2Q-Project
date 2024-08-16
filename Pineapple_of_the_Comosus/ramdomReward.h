#pragma once
#include <vector>

class Button;
class ImageUIRenderer;
class TextUIRenderer;
class ramdomReward 
{
public:

	std::vector<Button*>  btns;
	std::vector<ImageUIRenderer*>  Uis;
	std::vector<TextUIRenderer*>  TextNameUis;
	std::vector<TextUIRenderer*>  TextStatUis;

	ramdomReward() {};
	void shuffle();
	void setValue();
	void UIon();
	void UIoff();
};

