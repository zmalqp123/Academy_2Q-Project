#pragma once

// ignore layer나 tag를 만들어 eventSystem에 검출되지 않게 만들어야 할지도
class GameObject;
class Scene;

struct IPointerEnter {

};
struct IPointerStay {

};
struct IPointerExit {

};
struct IClickDown {

};
struct IClick {

};
struct IClickUp {

};

class EventSystem
{
private:
	EventSystem() {};
	~EventSystem() {};


	GameObject* currentWorldObject = nullptr;
	GameObject* currentUIObject = nullptr;
public:
	static EventSystem& GetInstance();

	void Update(Scene* scene, float delta);
	void ResetUpdate();

	GameObject* GetCurrWorldObject(); // 가장 앞에있는 월드의 오브젝트를 가져옴.
	GameObject* GetCurrUIObject();	// 가장 앞에있는 UI의 오브젝트를 가져옴.
};

