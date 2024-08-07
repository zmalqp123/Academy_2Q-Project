#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/Vector.h"
#include "../D2DEngine/EventSystem.h"
class GameObject;
class Camera;
class TestDropDown : public Component, public IPointer
{
public:
	Camera* camera;

	GameObject* dragObj;
	Vector2 offset;
	bool isDrag = false;
	virtual void Update(float delta);

	// IPointer을(를) 통해 상속됨
	void IPointerEnter() override;
	void IPointerStay() override;
	void IPointerExit() override;
};

