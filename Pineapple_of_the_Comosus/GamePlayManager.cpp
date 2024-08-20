#include "GamePlayManager.h"
#include "../D2DEngine/InputManager.h"
#include "../D2DEngine/EventSystem.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/Camera.h"
#include "../D2DEngine/SpriteRenderer.h"
#include "../D2DEngine/SpriteAnimation.h"
#include "PineAppleTile.h"
#include "MainPineApple.h"
#include "Turret.h"
#include "DataManager.h"
#include "../D2DEngine/BoxCollider.h"
#include "SelectTurretContainer.h"
#include "DynamicData.h"

//std::wstring hmm;
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
					auto& d = DataManager::GetInstance();
					//설치 가능할 때 좌클릭 시 설치.
					isDrag = false;
					dragObj->SetActive(false);
					// 터렛 활성화
					pTile->turret->SetActive(true);
					pTile->SetActivateTurret(Turret_Type);

					// 터렛 스탯 초기화
					auto turret = pTile->turret->GetComponent<Turret>();
					turret->turretData = (d.GetTurretData(Turret_Type));
					std::cout << "터렛 설치 : " << turret->turretData->cost << std::endl;
					//turret->UpdateTurretImage();
					//auto& pd = MainPineApple::GetInstance();
					// 터렛을 설치하면, 파인애플의 gold를 소모 시키는 func 을 호출해야한다. 
					pineApple->spendGold(turret->turretData->cost);
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

			auto spr = object->gameObject->GetComponent<SpriteAnimation>();
			if (object->turretType != TurretType::GrowthPromoter) {
				if (spr) {
					if (dir.x > 0) {
						spr->SetFlip(false, false);
						object->selectOutline->SetFilp(false, false);
					}
					else {
						spr->SetFlip(false, true);
						object->selectOutline->SetFilp(false, true);
					}
				}
				object->gameObject->transform->m_RelativeRotation = e;
			}
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
				if (object->turretType != TurretType::GrowthPromoter) {
					object->gameObject->transform->m_RelativeRotation = object->prevAngle;
					if (object->prevAngle > 90 || object->prevAngle < -90){
						spr->SetFlip(false, true);
						object->selectOutline->SetFilp(false, true);
					}
					else {
						spr->SetFlip(false, false);
						object->selectOutline->SetFilp(false, false);
					}
				}
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
				if ((startPos - mousePos).LengthSquared() < 100.f) { // 조건추가 : 클릭시작 지점에서 현재 마우스 위치를 빼도록.? 무슨버그
					// 바로 눌렀다 뗄정도의 거리라면
					auto curWorldObject = EventSystem::GetInstance().GetCurrWorldObject();
					if (curWorldObject != nullptr) {
						if (auto oneTurret = curWorldObject->GetComponent<Turret>()) {
							turrets.insert(oneTurret);
							oneTurret->prevAngle = oneTurret->gameObject->transform->m_RelativeRotation;
						}
						else if (auto oneTurret = curWorldObject->GetComponent<PineAppleTile>()) {
							if (auto tur = oneTurret->turret->GetComponent<Turret>()) {
								turrets.insert(tur);
								tur->prevAngle = tur->gameObject->transform->m_RelativeRotation;
							}
						}
						isAngle = true;
					}
					isSelect = false;
					selectBoxObj->SetActive(false);
				}
				else {
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
			else if (InputManager::GetInstance().GetPrevMouseState().right && !InputManager::GetInstance().GetMouseState().right) {
				if ((startPos - mousePos).LengthSquared() < 100.f) { // 조건추가 : 클릭시작 지점에서 현재 마우스 위치를 빼도록.? 무슨버그
					// 바로 눌렀다 뗄정도의 거리라면
					auto curWorldObject = EventSystem::GetInstance().GetCurrWorldObject();
					if (curWorldObject != nullptr) {
						if (auto oneTurret = curWorldObject->GetComponent<Turret>()) {
							turrets.insert(oneTurret);
							//oneTurret->prevAngle = oneTurret->gameObject->transform->m_RelativeRotation;
						}
						else if (auto oneTurret = curWorldObject->GetComponent<PineAppleTile>()) {
							if (auto tur = oneTurret->turret->GetComponent<Turret>()) {
								turrets.insert(tur);
								//tur->prevAngle = tur->gameObject->transform->m_RelativeRotation;
								oneTurret->Refund();
							}
						}
					}
					selectBoxObj->SetActive(false);
					isSelect = false;
					//isAngle = true;
				}
				else {
					// todo?
					isSelect = false;
					selectBoxObj->SetActive(false);
					turrets = selectTurrets->GetContainer();
					int size = turrets.size();
					if (size > 0) {
						//isAngle = true;

						for (auto& t : turrets) {
							//t->prevAngle = t->gameObject->transform->m_RelativeRotation;
							t->Refund();
						}
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
		else if (!InputManager::GetInstance().GetPrevMouseState().right && InputManager::GetInstance().GetMouseState().right) {
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
	auto data = DataManager::GetInstance().GetTurretData(type);

	if (pineApple->rewardData->isUpgrade == false) {
		if (data->cost > pineApple->GetPineAppleGold() || pineApple->rewardData->isHarvest == true) return;

		isDrag = true;
		dragObj->SetActive(true);
		auto spr = dragObj->GetComponent<SpriteAnimation>();
		//hmm = type == 0 ? L"../Resource/CrossBow.png" : L"../Resource/Musket.png";
		Turret_Type = type;

		spr->LoadTexture(data->imagePath.c_str());
		spr->LoadAnimationAsset(data->csvPath.c_str());
		spr->SetAnimation(pineApple->rewardData->GetTurretLevel((TurretType)type));

		std::cout << "Turret Type ID : " << type << std::endl;
	}
	else {
		auto upgradeData = pineApple->rewardData->GetNextStaticTurretData((TurretType)type);
		if (upgradeData == nullptr) return;
		if (upgradeData->cost > pineApple->GetPineAppleGold() || pineApple->rewardData->isHarvest == true) return;

		pineApple->rewardData->UpgradeTurret((TurretType)type);
		pineApple->spendGold(upgradeData->cost);

		pineApple->UpdateTurretImage();
	}
}
