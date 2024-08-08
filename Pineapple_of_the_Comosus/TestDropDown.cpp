#include "TestDropDown.h"
#include "../D2DEngine/InputManager.h"
#include "../D2DEngine/EventSystem.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Camera.h"
#include "../D2DEngine/SpriteRenderer.h"
#include "PineAppleTile.h"
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

		auto spr = dragObj->GetComponent<SpriteRenderer>();
		if (spr) {
			if (dir.x > 0)
				spr->SetFilp(false, false);
			else {
				spr->SetFilp(false, true);
			}
		}
		dragObj->transform->m_RelativeRotation = e;
		std::cout << e << std::endl;
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

		if (dragObj != nullptr) {
			auto coll = dragObj->GetComponent<Collider>();
			coll->ignoreEventSystem = false;
		}

		if (a != nullptr) {
			auto pTile = a->GetComponent<PineAppleTile>();
			if (pTile != nullptr) {
				gameObject->transform->pos.worldPosition.x = pTile->gameObject->transform->m_WorldTransform.dx;
				gameObject->transform->pos.worldPosition.y = pTile->gameObject->transform->m_WorldTransform.dy;
				pTile->turret = gameObject;
			}
		}
	}
	else if ((!InputManager::GetInstance().GetPrevMouseState().left && InputManager::GetInstance().GetMouseState().left) && isDrag == false && state == 0) {
		if (a == nullptr) return;
		isDrag = true;
		dragObj = a;
		Vector2 mousePos = InputManager::GetInstance().GetMousePosition();
		offset = dragObj->transform->pos.worldPosition - camera->ScreenToWorldPosition(mousePos);

		angle = dragObj->transform->m_RelativeRotation;

		auto coll = dragObj->GetComponent<Collider>();
		coll->ignoreEventSystem = true;
	}
	else if (isDrag && state == 0) {
		Vector2 mousePos = InputManager::GetInstance().GetMousePosition();
		if(dragObj != nullptr)
			dragObj->transform->pos.worldPosition = camera->ScreenToWorldPosition(mousePos) + offset;

		if (a != nullptr) {
			auto pTile = a->GetComponent<PineAppleTile>();
			if (pTile != nullptr) {
				if (pTile->IsPlaceable() == false) return;
				gameObject->transform->pos.worldPosition.x = pTile->gameObject->transform->m_WorldTransform.dx;
				gameObject->transform->pos.worldPosition.y = pTile->gameObject->transform->m_WorldTransform.dy;
			}
		}
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

void TestDropDown::TestlamdaFunc()
{
	std::cout << " 이게 진짜 될리 없어~" << std::endl;
}
