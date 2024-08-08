#include "GamePlayManager.h"
#include "../D2DEngine/InputManager.h"
#include "../D2DEngine/EventSystem.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Camera.h"
#include "../D2DEngine/SpriteRenderer.h"
#include "PineAppleTile.h"
#include "Turret.h"

void GamePlayManager::Update(float deltaTime)
{
	if (isAngle == true) {

	}
	else if (isDrag == true) {
		if (!InputManager::GetInstance().GetPrevMouseState().right && InputManager::GetInstance().GetMouseState().right) {
			isDrag = false;
			dragObj->SetActive(false);
		}

		auto curWorldObject = EventSystem::GetInstance().GetCurrWorldObject();
		Vector2 mousePos = InputManager::GetInstance().GetMousePosition();

		dragObj->transform->pos.worldPosition = camera->ScreenToWorldPosition(mousePos);

		if (curWorldObject != nullptr) {
			auto pTile = curWorldObject->GetComponent<PineAppleTile>();
			if (pTile != nullptr) {
				if (pTile->IsPlaceable() == false) return;
				dragObj->transform->pos.worldPosition.x = pTile->gameObject->transform->m_WorldTransform.dx;
				dragObj->transform->pos.worldPosition.y = pTile->gameObject->transform->m_WorldTransform.dy;

				if ((!InputManager::GetInstance().GetPrevMouseState().left && InputManager::GetInstance().GetMouseState().left))
				{
					//설치 가능할 때 좌클릭 시 설치.
					isDrag = false;
					dragObj->SetActive(false);

					// 해당 타일의 터렛을 활성화.
					isAngle = true;
				}
			}
		}
	}
}

void GamePlayManager::StartBatch(int type)
{
	isDrag = true;
	dragObj->SetActive(true);
	auto spr = dragObj->GetComponent<SpriteRenderer>();
	spr->LoadTexture(type == 0 ? L"../Resource/Sun.png" : L"../Resource/Earth.png");
}
