#include "pch.h"
#include "EventSystem.h"
#include "Scene.h"
#include "D2DRenderer.h"
#include "GameObject.h"
#include "Transform.h"
#include "Renderer.h"
#include "InputManager.h"
#include <algorithm>
#include "PublicData.h"

EventSystem& EventSystem::GetInstance()
{
	static EventSystem instance;
	return instance;
}

// 충돌체가 있는 오브젝트들을 받아와서
// 해당 오브젝트들 중 ipointer가 있다면 관련함수 호출
void EventSystem::Update(Scene* scene, float delta)
{
	prevWorldObject = currentWorldObject;
	prevUIObject = currentUIObject;
	prevObject = currentObject;
	prevPointer = curPointer;
	curPointer = nullptr;
	hovered.clear();

	auto m_GameObjects = scene->m_GameObjects;

	//std::vector<Renderer*> renderer;
	//std::vector<Renderer*> uiRenderer;

	std::vector<IPointer*> pointer;
	std::vector<IClick*> click;

	std::vector<GameObject*> worldObjects;
	std::vector<GameObject*> uiObjects;

	Vector2 mousePos = InputManager::GetInstance().GetMousePosition();

	//for (auto& g : m_GameObjects) {
	//	if (g->isActive == false) continue;
	//	bool pushed = false; // 게임오브젝트 하나당 푸쉬되면 ignore
	//	auto coll = g->GetComponent<Collider>();
	//	for (auto& comp : g->components) {
	//		if (Renderer* c = dynamic_cast<Renderer*>(comp)) {
	//			if (g->transform->type == Type::World)
	//			{
	//				if (coll == nullptr) continue;
	//				else {
	//					if (coll->isCollide(scene->camera->ScreenToWorldPosition(mousePos))) {
	//						renderer.push_back(c);
	//						pushed = true;
	//					}
	//				}
	//			}
	//			else if (g->transform->type == Type::Ui)
	//			{
	//				if ((g->transform->pos.rectposition.leftBottom.x >= mousePos.x &&
	//					g->transform->pos.rectposition.rightTop.x <= mousePos.x &&
	//					g->transform->pos.rectposition.leftBottom.y <= mousePos.y &&
	//					g->transform->pos.rectposition.rightTop.y <= mousePos.y) || pushed == false) {
	//					uiRenderer.push_back(c);
	//					pushed = true;
	//				}
	//			}
	//		}
	//		if (IPointer* p = dynamic_cast<IPointer*>(comp)) {
	//			pointer.push_back(p);
	//		}
	//		/*if (IClick* ic = dynamic_cast<IClick*>(ic)) {
	//			click.push_back(ic);
	//		}*/
	//	}
	//}

	// 마우스 위치의 오브젝트들을 모두 objs에 받아옴.
	for (auto& object : m_GameObjects) {
		if (object->isActive == false) continue;

		bool isPointer = false;
		for (auto coll : object->components) {
			if (isPointer == true) continue;
			if (Collider* c = dynamic_cast<Collider*>(coll))
			{
				if (c->ignoreEventSystem == true) continue;

				if (object->transform->type == Type::World) {
					bool result = c->isCollide(scene->camera->ScreenToWorldPosition(mousePos));
					if (result) {
						isPointer = true;
						worldObjects.push_back(object);
					}
				}
				else {
					bool result = c->isCollide(mousePos);

					if (result) {
						isPointer = true;
						uiObjects.push_back(object);
					}
				}
			}
		}
	}

	std::sort(worldObjects.begin(), worldObjects.end(), [](GameObject* first, GameObject* second) {
		return first->transform->GetSortingLayer() > second->transform->GetSortingLayer();
	}
	);
	std::sort(uiObjects.begin(), uiObjects.end(), [](GameObject* first, GameObject* second) {
		return first->transform->GetSortingLayer() > second->transform->GetSortingLayer();
	}
	);

	//currentWorldObject = renderer.size() > 0 ? renderer[0]->gameObject : nullptr;
	//currentUIObject = uiRenderer.size() > 0 ? uiRenderer[0]->gameObject : nullptr;
	
	currentWorldObject = worldObjects.size() > 0 ? worldObjects[0] : nullptr;
	currentUIObject = uiObjects.size() > 0 ? uiObjects[0] : nullptr;

	for (auto& object : worldObjects) {
		hovered.push_back(object);
	}
	for (auto& object : uiObjects) {
		hovered.push_back(object);
	}

	if (currentUIObject != nullptr)
		currentObject = currentUIObject;
	else if (currentWorldObject != nullptr)
		currentObject = currentWorldObject;
	else
		currentObject = nullptr;

	curPointer = nullptr;
	for (auto& object : uiObjects) {
		if (curPointer != nullptr) break;
		for (auto iPointer : object->components) {
			if (curPointer = dynamic_cast<IPointer*>(iPointer)) {
				break;
			}
		}
	}
	for (auto& object : worldObjects) {
		if (curPointer != nullptr) break;
		for (auto iPointer : object->components) {
			if (curPointer = dynamic_cast<IPointer*>(iPointer)) {
				break;
			}
		}
	}

	if (prevPointer == nullptr && curPointer == nullptr) return;
	if ( prevPointer == curPointer) {
		if (curPointer) curPointer->IPointerStay();
	}
	else if (prevPointer != curPointer) {
		if (curPointer) curPointer->IPointerEnter();
		if (prevPointer) prevPointer->IPointerExit();
	}
}

void EventSystem::ResetUpdate()
{
}

GameObject* EventSystem::GetCurrWorldObject()
{
	return currentWorldObject;
}

GameObject* EventSystem::GetCurrUIObject()\

{
	return currentUIObject;
}

GameObject* EventSystem::GetCurrObject()
{
	return currentObject;
}
