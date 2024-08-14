#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/Collider.h"

class Enemy;
class EnemyColliderNotify : public Component, IColliderNotify
{
public:
	EnemyColliderNotify() {}
	virtual ~EnemyColliderNotify() {}

	Enemy* enemy = nullptr;

	// IColliderNotify을(를) 통해 상속됨
	void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnStayOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
	void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
};

