#pragma once
#include <vector>
#include "Vector.h"
// ignore layer나 tag를 만들어 eventSystem에 검출되지 않게 만들어야 할지도
class GameObject;
class Scene;

struct IPointer {
	virtual void IPointerEnter() = 0;
	virtual void IPointerStay() = 0;
	virtual void IPointerExit() = 0;

};

struct IClick {
	virtual void IClickDown() = 0;
	virtual void IClicking() = 0;
	virtual void IClickUp() = 0;
};

struct PointerEventData {
	bool isLeftClick;
	Vector2 delta; // 이전 프레임과 현재 프레임의 마우스 위치 차이
	Vector2 position; // 마우스 현재 위치
	Vector2 pressPosition; // 누른 마우스 현재 위치

	GameObject* pointerDrag; // 드래그중인 오브젝트
	GameObject* pointerEnter;
	GameObject* pointerPress;
};

class EventSystem
{
private:
	EventSystem() {};
	~EventSystem() {};


	GameObject* currentWorldObject = nullptr;
	GameObject* currentUIObject = nullptr;
	GameObject* currentObject = nullptr;

	GameObject* prevWorldObject = nullptr;
	GameObject* prevUIObject = nullptr;
	GameObject* prevObject = nullptr;

	IPointer* curPointer = nullptr;
	IPointer* prevPointer = nullptr;

	std::vector<GameObject*> hovered;

public:
	static EventSystem& GetInstance();

	void Update(Scene* scene, float delta);
	void ResetUpdate();

	GameObject* GetCurrWorldObject(); // 가장 앞에있는 월드의 오브젝트를 가져옴.
	GameObject* GetCurrUIObject();	// 가장 앞에있는 UI의 오브젝트를 가져옴.
	GameObject* GetCurrObject();	// 가장 앞에있는 UI의 오브젝트를 가져옴.
};

