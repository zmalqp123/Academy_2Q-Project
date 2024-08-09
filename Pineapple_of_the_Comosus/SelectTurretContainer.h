#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/Collider.h"
#include <unordered_set>
class Turret;
class SelectTurretContainer : public Component, public IColliderNotify
{
private:
	std::unordered_set<Turret*> container;
public:
	SelectTurretContainer() {}
	virtual ~SelectTurretContainer() {}

	virtual void Update(float delta);

	// 실행은 GamePlayManager가 컨테이너 탐색 후 할거임.
	void ClearContainer();
	std::unordered_set<Turret*> GetContainer();

	// IColliderNotify을(를) 통해 상속됨
	void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) override;

	void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;

	void OnStayOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;

	void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;

};

