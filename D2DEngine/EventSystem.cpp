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
	for (auto& g : m_GameObjects) {
		if (g->isActive == false) continue;
		for (auto& render : g->components) {
			if (Renderer* c = dynamic_cast<Renderer*>(render)) {
				renderer.push_back(c);
			}
		}
	}
	std::sort(renderer.begin(), renderer.end(), [](Renderer* first, Renderer* second) {
		return first->GetSortingLayer() < second->GetSortingLayer();
		}
	);
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
