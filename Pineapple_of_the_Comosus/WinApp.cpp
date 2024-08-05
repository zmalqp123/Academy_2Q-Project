#include "WinApp.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/SpriteAnimationAsset.h"
#include "../D2DEngine/SpriteAnimation.h"
#include "../D2DEngine/ResourceManager.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/Scene.h"
#include "../D2DEngine/SpriteRenderer.h"
#include "../D2DEngine/Camera.h"
#include "../D2DEngine/PublicData.h"

#include "../D2DEngine/InputManager.h"
#include "../D2DEngine/TextRenderer.h"
void WinApp::Initialize(HINSTANCE hInstance, int nCmdShow)
{
	// 기본 초기화 + 카메라 생성
	__super::Initialize(hInstance, nCmdShow);
	scene = new Scene();
	auto camera = scene->CreateGameObject<GameObject>();
	auto pCam = camera->CreateComponent<Camera>();
	scene->SetMainCamera(pCam);

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
