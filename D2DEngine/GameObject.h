#pragma once
#include "Object.h"
#include <iostream>
#include <string>
#include <vector>
#include "Collider.h"
class Component;
class Transform;
class SpriteAnimation;
class Scene;
// 게임 오브젝트가 게임오브젝트를 자식으로 가지는 1번
// 모든 게임 오브젝트를 씬에 종속시키고 게임오브젝트가 
// 비활성화 시 상위 오브젝트의 active를 추적하여 실행여부를 결정하는 2번

class GameObject : public Object
{
public:
	bool isActive = true;
	Transform* transform = nullptr;
	SpriteAnimation* spriteAnim = nullptr;

	std::vector<Component*> components;

	Scene* ownerScene = nullptr;

	GameObject();
	virtual ~GameObject();

	virtual void Init();
	virtual void Update(float delta);
	virtual void Render(D2D1_MATRIX_3X2_F cameraMat);

	bool AddComponent(Component* component);

	template <typename T>
	T* CreateComponent() {
		bool bIsBase = std::is_base_of<Component, T>::value;
		//assert(bIsBase == true);
		T* component = new T();
		components.push_back(component);
		component->SetOwner(this);
		return component;
	}

	template <typename T>
	T* GetComponent() {
		bool bIsBase = std::is_base_of<Component, T>::value;
		//assert(bIsBase == true);

		for (auto iter = components.begin(); iter != components.end(); iter++)
		{
			T* result = dynamic_cast<T*>(*iter);
			if (result != nullptr)
				return result;
		}
		return nullptr;

		//// 상속관계인 컴포넌트를 찾을 수 없음.
		//for (auto c : components) {
		//	auto cP = dynamic_cast<T*>(c);
		//	if (cP != nullptr) {
		//		if (typeid(cP) == typeid(T*)) {
		//			return dynamic_cast<T*>(c);
		//		}
		//	}
		//	if (typeid(*c) == typeid(T))
		//		return dynamic_cast<T*>(c);
		//}
		//return nullptr;
	}

	template <typename T>
	std::vector<T*> GetComponents() {
		bool bIsBase = std::is_base_of<Component, T>::value;
		std::vector<T*> comps;
		for (auto iter = components.begin(); iter != components.end(); iter++)
		{
			T* result = dynamic_cast<T*>(*iter);
			if (result) {
				comps.push_back(result);
			}
		}
		return comps;
	}

	void RemoveComponent(Component* Component);

	void SetActive(bool active);

	void SetOwner(Scene* scene);
};

