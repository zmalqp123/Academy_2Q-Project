#include "ComosusLightSelector.h"
#include "EnemyColliderNotify.h"
#include "../D2DEngine/GameObject.h"

void ComosusLightSelector::ClearContainer()
{
	container.clear();
}

std::unordered_set<EnemyColliderNotify*> ComosusLightSelector::GetContainer()
{
	return container;
}

void ComosusLightSelector::OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void ComosusLightSelector::OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	auto enemy = pOtherComponent->gameObject->GetComponent<EnemyColliderNotify>();
	if (enemy != nullptr)
		container.insert(enemy);
}

void ComosusLightSelector::OnStayOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void ComosusLightSelector::OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
	auto enemy = pOtherComponent->gameObject->GetComponent<EnemyColliderNotify>();
	if (enemy != nullptr)
		container.erase(enemy);
}
