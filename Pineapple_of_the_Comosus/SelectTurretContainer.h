#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/Collider.h"
#include <vector>
class Turret;
class SelectTurretContainer : public Component, public IColliderNotify
{
public:
	SelectTurretContainer() {}
	virtual ~SelectTurretContainer() {}

	std::vector<Turret*> container;

	// IColliderNotify을(를) 통해 상속됨
	void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) override;

	void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;

	void OnStayOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;

	void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;

};

