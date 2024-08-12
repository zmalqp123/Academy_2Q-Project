#include "GamePlayManager.h"
#include "../D2DEngine/InputManager.h"
#include "../D2DEngine/EventSystem.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Camera.h"
#include "../D2DEngine/SpriteRenderer.h"
#include "PineAppleTile.h"
#include "MainPineApple.h"
#include "Turret.h"
#include "DataManager.h"
#include "../D2DEngine/BoxCollider.h"
#include "SelectTurretContainer.h"

std::wstring hmm;
int Turret_Type = 0; // 터렛 타입 가지는 변수


void GamePlayManager::Update(float deltaTime)
{
	// 터렛 배치용
	if (isDrag == true) {
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
					// 터렛 활성화
					pTile->turret->SetActive(true);
					pTile->SetActivateTurret(hmm);

					// 터렛 스탯 초기화
					auto turret = pTile->turret->GetComponent<Turret>();
					auto& d = DataManager::GetInstance();
					turret->turretData = *(d.GetTurretData(Turret_Type));
					std::cout << "터렛 설치 : " << turret->turretData.cost << std::endl;
					auto& pd = MainPineApple::GetInstance();
					// 터렛을 설치하면, 파인애플의 gold를 소모 시키는 func 을 호출해야한다. 
					pd.spendGold(turret->turretData.cost);
				}
			}
		}
	}


	else if (isAngle == true) {
		Vector2 mousePos = InputManager::GetInstance().GetMousePosition();
		auto temp = turrets;
		for (auto& object : temp) {

			Vector2 dir = camera->ScreenToWorldPosition(mousePos) - Vector2(object->gameObject->transform->m_WorldTransform.dx, object->gameObject->transform->m_WorldTransform.dy);
			dir.Normalize();

			float x1 = 1.f;
			float y1 = 0.f;

			float e = atan2f(x1 * dir.y - y1 * dir.x, x1 * dir.x + y1 * dir.y) / 3.14159f * 180.f;

			auto spr = object->gameObject->GetComponent<SpriteRenderer>();
			if (spr) {
				if (dir.x > 0)
					spr->SetFilp(false, false);
				else {
					spr->SetFilp(false, true);
				}
			}
			object->gameObject->transform->m_RelativeRotation = e;
			//std::cout << e << std::endl;
			if ((!InputManager::GetInstance().GetPrevMouseState().left && InputManager::GetInstance().GetMouseState().left)) {
				isAngle = false;
				turrets.clear();
				object->currAngle = e;
			}
			else if ((!InputManager::GetInstance().GetPrevMouseState().right && InputManager::GetInstance().GetMouseState().right)) {
				//dragObj->transform->m_RelativeRotation = angle;
				isAngle = false;
				turrets.clear();
				object->gameObject->transform->m_RelativeRotation = object->prevAngle;
				if (object->prevAngle > 90 || object->prevAngle < -90) 
					spr->SetFilp(false, true);
				else
					spr->SetFilp(false, false);
			}
		}
	}

	// 터렛 선택용
	else if (isDrag == false && EventSystem::GetInstance().GetCurrUIObject() == nullptr) {
		if (isSelect == true) {
			Vector2 mousePos = InputManager::GetInstance().GetMousePosition();
			mousePos = camera->ScreenToWorldPosition(mousePos);

			Vector2 center = (mousePos + startPos) * 0.5f;
			Vector2 extent = (mousePos - startPos) * 0.5f;
			extent.x = std::abs(extent.x);
			extent.y = std::abs(extent.y);

			multiSelectBox->SetCenter(center);
			multiSelectBox->SetExtent(extent);
			if (InputManager::GetInstance().GetPrevMouseState().left && !InputManager::GetInstance().GetMouseState().left) {
				// todo?
				isSelect = false;
				selectBoxObj->SetActive(false);
				turrets = selectTurrets->GetContainer();
				int size = turrets.size();
				if (size > 0) {
					isAngle = true;

					for (auto& t : turrets) {
						t->prevAngle = t->gameObject->transform->m_RelativeRotation;
					}
				}
			}
		}
		else if (!InputManager::GetInstance().GetPrevMouseState().left && InputManager::GetInstance().GetMouseState().left) {
			Vector2 mousePos = InputManager::GetInstance().GetMousePosition();

			startPos = camera->ScreenToWorldPosition(mousePos);
			isSelect = true;
			selectBoxObj->SetActive(true);
			multiSelectBox->SetCenter(mousePos);
			multiSelectBox->SetExtent({ 0.f, 0.f });
			selectTurrets->ClearContainer();
		}
	}
}
void GamePlayManager::StartBatch(int type)
{
	isDrag = true;
	dragObj->SetActive(true);
	auto spr = dragObj->GetComponent<SpriteRenderer>();
	//hmm = type == 0 ? L"../Resource/CrossBow.png" : L"../Resource/Musket.png";
	switch (type)
	{
	case 0:
		hmm = L"../Resource/30501.png"; // 석궁
		Turret_Type = 30501;
		break;
	case 1:
		hmm = L"../Resource/30511.png"; // 머스켓
		Turret_Type = 30511;
		break;
	case 2:
		hmm = L"../Resource/30521.png"; // 대포
		Turret_Type = 30521;
		break;
	case 3:
		hmm = L"../Resource/30531.png"; // 슈퍼 석궁
		Turret_Type = 30531;
		break;
	case 4:
		hmm = L"../Resource/30541.png"; // 슬로우 완드
		Turret_Type = 30541;
		break;
	case 5:
		hmm = L"../Resource/30551.png"; // 슬로우 완드
		Turret_Type = 30551;
		break;
	default:
		break;
	}
	spr->LoadTexture(hmm);
	
	std::cout << type << std::endl;
}
