#include "TestDropDown.h"
#include "../D2DEngine/InputManager.h"
#include "../D2DEngine/EventSystem.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Camera.h"
#include "../D2DEngine/SpriteRenderer.h"
int state = 0;
float angle = 0.f;
void TestDropDown::Update(float delta)
{
	auto a = EventSystem::GetInstance().GetCurrWorldObject();



	if (state == 1) {
		Vector2 mousePos = InputManager::GetInstance().GetMousePosition();

		Vector2 dir = camera->ScreenToWorldPosition(mousePos) - dragObj->transform->pos.worldPosition;
		dir.Normalize();

		float x1 = 1.f;
		float y1 = 0.f;

		float e = atan2f(x1 * dir.y - y1 * dir.x, x1 * dir.x + y1 * dir.y) / 3.14159f * 180.f;

		if (dir.x > 0) 
			dragObj->GetComponent<SpriteRenderer>()->SetFilp(false, false);
		else {
			dragObj->GetComponent<SpriteRenderer>()->SetFilp(false, true);
		}
		dragObj->transform->m_RelativeRotation = e;
		if ((!InputManager::GetInstance().GetPrevMouseState().left && InputManager::GetInstance().GetMouseState().left)) {
			state = 0;
			dragObj = nullptr;
		}
		else if ((!InputManager::GetInstance().GetPrevMouseState().right && InputManager::GetInstance().GetMouseState().right)) {
			state = 0;
			dragObj->transform->m_RelativeRotation = angle;
			dragObj = nullptr;
		}
	}
	//std::cout << (a == nullptr ? 1 : 2) << std::endl;
	if (!InputManager::GetInstance().GetPrevMouseState().left && InputManager::GetInstance().GetMouseState().left && isDrag == true && state == 0) {
		//dragObj = nullptr;
		isDrag = false;

		state = 1;
	}
	else if ((!InputManager::GetInstance().GetPrevMouseState().left && InputManager::GetInstance().GetMouseState().left) && isDrag == false && state == 0) {
		if (a == nullptr) return;
		isDrag = true;
		dragObj = a;
		Vector2 mousePos = InputManager::GetInstance().GetMousePosition();
		offset = dragObj->transform->pos.worldPosition - camera->ScreenToWorldPosition(mousePos);

		angle = dragObj->transform->m_RelativeRotation;
	}
	else if (isDrag && state == 0) {
		Vector2 mousePos = InputManager::GetInstance().GetMousePosition();
		if(dragObj != nullptr)
			dragObj->transform->pos.worldPosition = camera->ScreenToWorldPosition(mousePos) + offset;
	}
}

void TestDropDown::IPointerEnter()
{
	std::cout << "enter" << std::endl;
}

void TestDropDown::IPointerStay()
{
	//std::cout << "stay" << std::endl;
}

void TestDropDown::IPointerExit()
{
	std::cout << "exit" << std::endl;
}
