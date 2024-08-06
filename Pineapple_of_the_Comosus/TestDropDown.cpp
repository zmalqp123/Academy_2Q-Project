#include "TestDropDown.h"
#include "../D2DEngine/InputManager.h"
#include "../D2DEngine/EventSystem.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Camera.h"
void TestDropDown::Update(float delta)
{
	auto a = EventSystem::GetInstance().GetCurrWorldObject();
	//std::cout << (a == nullptr ? 1 : 2) << std::endl;
	if (!InputManager::GetInstance().GetPrevMouseState().left && InputManager::GetInstance().GetMouseState().left && isDrag == true) {
		dragObj = nullptr;
		isDrag = false;
	}
	else if ((!InputManager::GetInstance().GetPrevMouseState().left && InputManager::GetInstance().GetMouseState().left) && isDrag == false) {
		if (a == nullptr) return;
		isDrag = true;
		dragObj = a;
		Vector2 mousePos = InputManager::GetInstance().GetMousePosition();
		offset = a->transform->pos.worldPosition - camera->ScreenToWorldPosition(mousePos);
	}
	else if (isDrag) {
		Vector2 mousePos = InputManager::GetInstance().GetMousePosition();
		dragObj->transform->pos.worldPosition = camera->ScreenToWorldPosition(mousePos) + offset;
	}
}
