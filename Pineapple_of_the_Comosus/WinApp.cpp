#include "WinApp.h"
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

#include "DataManager.h"
#include "TestDropDown.h"
void WinApp::Initialize(HINSTANCE hInstance, int nCmdShow, float x, float y)
{
	// 기본 초기화 + 카메라 생성
	__super::Initialize(hInstance, nCmdShow, x, y);
	scene = new Scene();
	auto camera = scene->CreateGameObject<GameObject>();
	auto pCam = camera->CreateComponent<Camera>();
	scene->SetMainCamera(pCam);

	auto areaObj = scene->CreateGameObject<GameObject>();
	auto test = areaObj->CreateComponent<TestDropDown>();
	test->camera = scene->camera;
	auto testSpr = areaObj->CreateComponent<SpriteRenderer>();
	//testSpr->m_flipX = true;
	testSpr->LoadTexture(L"../Resource/Sun.png");
	areaObj->transform->pos.worldPosition = { -200.f, 300.f };
	auto circle = areaObj->CreateComponent< CircleCollider>();
	circle->SetRadius(100.f);
	auto box = areaObj->CreateComponent<BoxCollider>();
	box->SetExtent({ 3.f, 10.f });
	
	//areaObj->CreateComponent<MouseDownTest>();
}

void WinApp::Update(float deltaTime)
{
	__super::Update(deltaTime);

	scene->Update(deltaTime);
}

void WinApp::Render(D2DRenderer* _render)
{
	__super::Render(_render);
	scene->Render(_render);
}

void WinApp::Uninitialize()
{
	__super::Uninitialize();
}
