#pragma once
#include "Object.h"
#include "GameObject.h"
#include "AABB.h"
#include <vector>
//class GameObject;
class Camera;
class D2DRenderer;
class Scene : public Object
{
public:
	Scene();
	virtual ~Scene();

	std::vector<GameObject*> m_GameObjects;

	AABB* m_pCullingBound = nullptr;
	AABB m_CullingBoundDefault;

	GameObject* cam = nullptr;
	Camera* camera = nullptr;
	D2D1_MATRIX_3X2_F cameraMat;

	void Start();
	void Update(float deltaTime);
	void Render(D2DRenderer* _render);
	void Clear();
	void SetCullingBound(AABB* pBound);
	void SetMainCamera(Camera* cam);
	
	template<typename T>
	T* CreateGameObject() {
		bool bIsBase = std::is_base_of<GameObject, T>::value;
		//assert(bIsBase == true);	// GameObject를 상속받은 클래스만 생성할 수 있다.
		T* newObject = new T();
		//newObject->SetOwner(this);
		m_GameObjects.push_back(newObject);
		return newObject;
	}
};

