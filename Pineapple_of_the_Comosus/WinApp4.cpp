#include "WinApp4.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/SpriteAnimationAsset.h"
#include "../D2DEngine/SpriteAnimation.h"
#include "../D2DEngine/ResourceManager.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/CircleCollider.h"
#include "../D2DEngine/Scene.h"
#include "../D2DEngine/SpriteRenderer.h"
#include "../D2DEngine/Camera.h"
#include "../D2DEngine/PublicData.h"

#include "../D2DEngine/InputManager.h"
#include "../D2DEngine/TextRenderer.h"
#include "../D2DEngine/Button.h"
#include "../D2DEngine/ImageUIRenderer.h"

#include "DataManager.h"
#include "TestDropDown.h"
void WinApp4::Initialize(HINSTANCE hInstance, int nCmdShow, float x, float y)
{
	// 기본 초기화 + 카메라 생성
	__super::Initialize(hInstance, nCmdShow, x, y);
	scene = new Scene();
	auto camera = scene->CreateGameObject<GameObject>();
	auto pCam = camera->CreateComponent<Camera>();
	scene->SetMainCamera(pCam);

	DataManager::GetInstance().LoadEnemySheetFromCSV(L"../Resource/EnemyData.csv");

}

void WinApp4::Update(float deltaTime)
{
	__super::Update(deltaTime);

	scene->Update(deltaTime);
}

void WinApp4::Render(D2DRenderer* _render)
{
	__super::Render(_render);
	scene->Render(_render);
}

void WinApp4::Uninitialize()
{
	__super::Uninitialize();
}
