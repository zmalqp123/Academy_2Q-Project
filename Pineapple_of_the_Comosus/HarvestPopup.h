#pragma once
#include "../D2DEngine/Component.h"

class ImageUIRenderer;
class HarvestPopup : public Component
{
public:
	HarvestPopup() {}
	ImageUIRenderer* ImageRender;
};

