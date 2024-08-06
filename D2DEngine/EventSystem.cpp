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

void EventSystem::Update(Scene* scene, float delta)
{
	auto m_GameObjects = scene->m_GameObjects;

	std::vector<Renderer*> renderer;
	std::vector<Renderer*> uiRenderer;
	std::vector<IPointer*> pointer;
	std::vector<IClick*> click;
	Vector2 mousePos = InputManager::GetInstance().GetMousePosition();

	for (auto& g : m_GameObjects) {
		if (g->isActive == false) continue;

		bool pushed = false; // 게임오브젝트 하나당 푸쉬되면 ignore
		auto coll = g->GetComponent<Collider>();

		for (auto& comp : g->components) {
			if (Renderer* c = dynamic_cast<Renderer*>(comp)) {
				if (g->transform->type == Type::World) 
				{
					if (coll == nullptr) continue;
					else {
						if (coll->isCollide(scene->camera->ScreenToWorldPosition(mousePos))) {
							renderer.push_back(c);
							pushed = true;
						}
					}
				}
				else if (g->transform->type == Type::Ui)
				{
					if ((g->transform->pos.rectposition.leftBottom.x >= mousePos.x &&
						g->transform->pos.rectposition.rightTop.x <= mousePos.x &&
						g->transform->pos.rectposition.leftBottom.y <= mousePos.y &&
						g->transform->pos.rectposition.rightTop.y <= mousePos.y) || pushed == false) {
						uiRenderer.push_back(c);
						pushed = true;
					}
				}
			}
			if (IPointer* p = dynamic_cast<IPointer*>(comp)) {
				pointer.push_back(p);
			}
			/*if (IClick* ic = dynamic_cast<IClick*>(ic)) {
				click.push_back(ic);
			}*/
		}
	}
	std::sort(renderer.begin(), renderer.end(), [](Renderer* first, Renderer* second) {
		return first->GetSortingLayer() > second->GetSortingLayer();
		}
	);
	std::sort(uiRenderer.begin(), uiRenderer.end(), [](Renderer* first, Renderer* second) {
		return first->GetSortingLayer() > second->GetSortingLayer();
		}
	);

	currentWorldObject = renderer.size() > 0 ? renderer[0]->gameObject : nullptr;
	currentUIObject = uiRenderer.size() > 0 ? uiRenderer[0]->gameObject : nullptr;

	if (currentWorldObject != nullptr || currentWorldObject != nullptr) {
		std::cout << "dw";
	}
}

void EventSystem::ResetUpdate()
{
}

GameObject* EventSystem::GetCurrWorldObject()
{
	return nullptr;
}

GameObject* EventSystem::GetCurrUIObject()
{
	return nullptr;
}
