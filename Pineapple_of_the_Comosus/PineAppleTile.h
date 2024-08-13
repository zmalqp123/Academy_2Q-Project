#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/EventSystem.h"
#include <string>
class MainPineApple;
class GameObject;
class PineAppleTile : public Component, public IPointer 
{
public:
	PineAppleTile() {};
	virtual ~PineAppleTile() {};

	void Update(float deltaTime) override;

	// IPointer을(를) 통해 상속됨
	void IPointerEnter() override;
	void IPointerStay() override;
	void IPointerExit() override;

	bool IsPlaceable();

	GameObject* turret = nullptr;
	MainPineApple* pApple = nullptr;
	int index;

	bool isSelected = false;

	void SetActivateTurret(int typeID);
};

