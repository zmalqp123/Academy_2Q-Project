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

#include "PineAppleTile.h"
#include "MainPineApple.h"
#include "GamePlayManager.h"
#include "TurretUI.h"
#include "Turret.h"
#include "SelectTurretContainer.h"

void WinApp4::Initialize(HINSTANCE hInstance, int nCmdShow, float x, float y)
{
	// 기본 초기화 + 카메라 생성
	__super::Initialize(hInstance, nCmdShow, x, y);
	scene = new Scene();
	auto camera = scene->CreateGameObject<GameObject>();
	auto pCam = camera->CreateComponent<Camera>();
	scene->SetMainCamera(pCam);

	// 게임 매니저 드래그엔 드롭, 파인애플 설치, 터렛 파인애플 몹 데이터 등을 관리함.
	auto gmObj = scene->CreateGameObject<GameObject>();
	auto GameManager = gmObj->CreateComponent<GamePlayManager>();
	GameManager->camera = scene->camera;

	auto boxObj = scene->CreateGameObject<GameObject>();
	boxObj->SetActive(false);
	auto boxColl = boxObj->CreateComponent<BoxCollider>();
	boxColl->SetCollisionType(CollisionType::Overlap);
	auto selector = boxObj->CreateComponent<SelectTurretContainer>();
	GameManager->selectBoxObj = boxObj;
	GameManager->multiSelectBox = boxColl;
	GameManager->selectTurrets = selector;

	// 코모서스 파인애플 (겁나 큼)
	auto paObj = scene->CreateGameObject<GameObject>();
	paObj->transform->pos.worldPosition = { 0.f, -200.f };
	auto pineApple = paObj->CreateComponent<MainPineApple>();

	/*auto turretTest = scene->CreateGameObject<GameObject>();
	auto drop = turretTest->CreateComponent<TestDropDown>();
	drop->camera = scene->camera;
	auto circle = turretTest->CreateComponent<CircleCollider>();
	circle->SetRadius(100.f);
	auto tspr = turretTest->CreateComponent<SpriteRenderer>();
	tspr->LoadTexture(L"../Resource/Sun.png");*/


	auto testDragObj = scene->CreateGameObject<GameObject>();
	testDragObj->SetActive(false);
	auto sproper = testDragObj->CreateComponent<SpriteRenderer>();
	sproper->alpha = 0.5f;
	GameManager->dragObj = testDragObj;

	auto testBtn1 = scene->CreateGameObject<GameObject>();
	testBtn1->transform->type = Type::Ui;
	testBtn1->transform->pos.rectposition.leftBottom = { 100.f, 100.f };
	testBtn1->transform->pos.rectposition.rightTop = { 300.f, 300.f };
	auto btn1 = testBtn1->CreateComponent<Button>();
	auto turretUI = testBtn1->CreateComponent<TurretUI>();
	turretUI->SetIndex(0);
	btn1->LoadTexture(L"../Resource/Sun.png");
	btn1->AddListener([GameManager, turretUI]() {GameManager->StartBatch(turretUI->GetIndex()); });

	auto testBtn2 = scene->CreateGameObject<GameObject>();
	testBtn2->transform->type = Type::Ui;
	testBtn2->transform->pos.rectposition.leftBottom = { 400.f, 100.f };
	testBtn2->transform->pos.rectposition.rightTop = { 600.f, 300.f };
	auto btn2 = testBtn2->CreateComponent<Button>();
	auto turretUI2 = testBtn2->CreateComponent<TurretUI>();
	turretUI2->SetIndex(1);
	btn2->LoadTexture(L"../Resource/Earth.png");
	btn2->AddListener([GameManager, turretUI2]() {GameManager->StartBatch(turretUI2->GetIndex()); });

	{
		// 파인애플 타일들
		auto paTileObj = scene->CreateGameObject<GameObject>();
		paTileObj->transform->SetParent(paObj->transform);
		paTileObj->transform->pos.worldPosition = { -200.f, 200.f };

		auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
		pineTile->pApple = pineApple;
		pineTile->index = 0;

		auto coll = paTileObj->CreateComponent<CircleCollider>();
		coll->SetCollisionType(CollisionType::Overlap);
		coll->isKinemetic = true;
		coll->SetRadius(60.f);

		auto childObj = scene->CreateGameObject<GameObject>();
		childObj->isActive = false;
		childObj->CreateComponent<Turret>();
		auto circleColl = childObj->CreateComponent<CircleCollider>();
		circleColl->SetCollisionType(CollisionType::Overlap);
		childObj->transform->SetParent(paTileObj->transform);
		auto spr = childObj->CreateComponent<SpriteRenderer>();
		pineTile->turret = childObj;
	}
	{
		// 파인애플 타일들
		auto paTileObj = scene->CreateGameObject<GameObject>();
		paTileObj->transform->SetParent(paObj->transform);
		paTileObj->transform->pos.worldPosition = { 0.f, 200.f };

		auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
		pineTile->pApple = pineApple;
		pineTile->index = 1;

		auto coll = paTileObj->CreateComponent<CircleCollider>();
		coll->SetCollisionType(CollisionType::Overlap);
		coll->isKinemetic = true;
		coll->SetRadius(60.f);

		auto childObj = scene->CreateGameObject<GameObject>();
		childObj->isActive = false;
		childObj->CreateComponent<Turret>();
		auto circleColl = childObj->CreateComponent<CircleCollider>();
		circleColl->SetCollisionType(CollisionType::Overlap);
		childObj->transform->SetParent(paTileObj->transform);
		auto spr = childObj->CreateComponent<SpriteRenderer>();
		pineTile->turret = childObj;
	}
	{
		// 파인애플 타일들
		auto paTileObj = scene->CreateGameObject<GameObject>();
		paTileObj->transform->SetParent(paObj->transform);
		paTileObj->transform->pos.worldPosition = { 200.f, 200.f };

		auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
		pineTile->pApple = pineApple;
		pineTile->index = 2;

		auto coll = paTileObj->CreateComponent<CircleCollider>();
		coll->SetCollisionType(CollisionType::Overlap);
		coll->isKinemetic = true;
		coll->SetRadius(60.f);

		auto childObj = scene->CreateGameObject<GameObject>();
		childObj->isActive = false;
		childObj->CreateComponent<Turret>();
		auto circleColl = childObj->CreateComponent<CircleCollider>();
		circleColl->SetCollisionType(CollisionType::Overlap);
		childObj->transform->SetParent(paTileObj->transform);
		auto spr = childObj->CreateComponent<SpriteRenderer>();
		pineTile->turret = childObj;
	}
	{
		// 파인애플 타일들
		auto paTileObj = scene->CreateGameObject<GameObject>();
		paTileObj->transform->SetParent(paObj->transform);
		paTileObj->transform->pos.worldPosition = { -100.f, 100.f };

		auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
		pineTile->pApple = pineApple;
		pineTile->index = 3;

		auto coll = paTileObj->CreateComponent<CircleCollider>();
		coll->SetCollisionType(CollisionType::Overlap);
		coll->isKinemetic = true;
		coll->SetRadius(60.f);

		auto childObj = scene->CreateGameObject<GameObject>();
		childObj->isActive = false;
		childObj->CreateComponent<Turret>();
		auto circleColl = childObj->CreateComponent<CircleCollider>();
		circleColl->SetCollisionType(CollisionType::Overlap);
		childObj->transform->SetParent(paTileObj->transform);
		auto spr = childObj->CreateComponent<SpriteRenderer>();
		pineTile->turret = childObj;
	}
	{
		// 파인애플 타일들
		auto paTileObj = scene->CreateGameObject<GameObject>();
		paTileObj->transform->SetParent(paObj->transform);
		paTileObj->transform->pos.worldPosition = { 100.f, 100.f };

		auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
		pineTile->pApple = pineApple;
		pineTile->index = 4;

		auto coll = paTileObj->CreateComponent<CircleCollider>();
		coll->SetCollisionType(CollisionType::Overlap);
		coll->isKinemetic = true;
		coll->SetRadius(60.f);

		auto childObj = scene->CreateGameObject<GameObject>();
		childObj->isActive = false;
		childObj->CreateComponent<Turret>();
		auto circleColl = childObj->CreateComponent<CircleCollider>();
		circleColl->SetCollisionType(CollisionType::Overlap);
		childObj->transform->SetParent(paTileObj->transform);
		auto spr = childObj->CreateComponent<SpriteRenderer>();
		pineTile->turret = childObj;
	}
	{
		// 파인애플 타일들
		auto paTileObj = scene->CreateGameObject<GameObject>();
		paTileObj->transform->SetParent(paObj->transform);
		paTileObj->transform->pos.worldPosition = { -200.f, 0.f };

		auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
		pineTile->pApple = pineApple;
		pineTile->index = 5;

		auto coll = paTileObj->CreateComponent<CircleCollider>();
		coll->SetCollisionType(CollisionType::Overlap);
		coll->isKinemetic = true;
		coll->SetRadius(60.f);

		auto childObj = scene->CreateGameObject<GameObject>();
		childObj->isActive = false;
		childObj->CreateComponent<Turret>();
		auto circleColl = childObj->CreateComponent<CircleCollider>();
		circleColl->SetCollisionType(CollisionType::Overlap);
		childObj->transform->SetParent(paTileObj->transform);
		auto spr = childObj->CreateComponent<SpriteRenderer>();
		pineTile->turret = childObj;
	}
	{
		// 파인애플 타일들
		auto paTileObj = scene->CreateGameObject<GameObject>();
		paTileObj->transform->SetParent(paObj->transform);
		paTileObj->transform->pos.worldPosition = { 0.f, 0.f };

		auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
		pineTile->pApple = pineApple;
		pineTile->index = 6;

		auto coll = paTileObj->CreateComponent<CircleCollider>();
		coll->SetCollisionType(CollisionType::Overlap);
		coll->isKinemetic = true;
		coll->SetRadius(60.f);

		auto childObj = scene->CreateGameObject<GameObject>();
		childObj->isActive = false;
		childObj->CreateComponent<Turret>();
		auto circleColl = childObj->CreateComponent<CircleCollider>();
		circleColl->SetCollisionType(CollisionType::Overlap);
		childObj->transform->SetParent(paTileObj->transform);
		auto spr = childObj->CreateComponent<SpriteRenderer>();
		pineTile->turret = childObj;
	}
	{
		// 파인애플 타일들
		auto paTileObj = scene->CreateGameObject<GameObject>();
		paTileObj->transform->SetParent(paObj->transform);
		paTileObj->transform->pos.worldPosition = { 200.f, 0.f };

		auto pineTile = paTileObj->CreateComponent<PineAppleTile>();
		pineTile->pApple = pineApple;
		pineTile->index = 7;

		auto coll = paTileObj->CreateComponent<CircleCollider>();
		coll->SetCollisionType(CollisionType::Overlap);
		coll->isKinemetic = true;
		coll->SetRadius(60.f);

		auto childObj = scene->CreateGameObject<GameObject>();
		childObj->isActive = false;
		childObj->CreateComponent<Turret>();
		auto circleColl = childObj->CreateComponent<CircleCollider>();
		circleColl->SetCollisionType(CollisionType::Overlap);
		childObj->transform->SetParent(paTileObj->transform);
		auto spr = childObj->CreateComponent<SpriteRenderer>();
		pineTile->turret = childObj;
	}
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
