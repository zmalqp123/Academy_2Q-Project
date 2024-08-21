#include "SelectTurretContainer.h"
#include "Turret.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"

void SelectTurretContainer::Update(float delta)
{
	//std::cout << "dd" << std::endl;
	//ClearContainer();

}

void SelectTurretContainer::ClearContainer()
{
	container.clear();
}

std::unordered_set<Turret*> SelectTurretContainer::GetContainer()
{
	return container;
}

void SelectTurretContainer::OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void SelectTurretContainer::OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	auto turret = pOtherComponent->gameObject->GetComponent<Turret>();
	if (turret != nullptr) {
		if (turret->turretType == TurretType::GrowthPromoter) return;
		turret->SelectTurret();
		container.insert(turret);
	}
}

void SelectTurretContainer::OnStayOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void SelectTurretContainer::OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	auto turret = pOtherComponent->gameObject->GetComponent<Turret>();
	if (turret != nullptr) {
		turret->DeSelectTurret();
		container.erase(turret);
	}
}
