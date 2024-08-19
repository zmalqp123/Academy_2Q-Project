#pragma once

#include "Component.h"
#include <set>
#include "Vector.h"
enum class ColliderType {
	None,
	Circle,
	Box
};
enum class CollisionType {
	None,
	Block, // Collision
	Overlap // Trigger
};
#define BLOCK CollisionType::Block
#define OVERLAP CollisionType::Overlap
class Collider;
class IColliderNotify {
public:
	Vector2 resoultion;
	virtual void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) = 0;
	virtual void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) = 0;
	virtual void OnStayOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) = 0;
	virtual void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) = 0;
};

class Collider : virtual public Component
{
protected:
	Vector2 offset;

	ColliderType m_ColliderType = ColliderType::None;
	CollisionType m_CollisionType = CollisionType::None;

	std::set<Collider*> m_ColliderStateCurr;
	std::set<Collider*> m_ColliderStatePrev;
public:
	bool isKinemetic = false;
	bool ignoreEventSystem = false;
	Vector2 prevPosition;

	Collider() = default;
	virtual ~Collider() = default;

	CollisionType GetCollisionType() { return m_CollisionType; }
	void SetCollisionType(CollisionType Type) { m_CollisionType = Type; }
	ColliderType GetColliderType() { return m_ColliderType; }

	void ClearAndBackupCollideState();

	bool IsEmptyCollideStateCurr() { return m_ColliderStateCurr.empty(); }

	void InsertCollideState(Collider* pColliderComponent) { m_ColliderStateCurr.insert(pColliderComponent); }
	void ProcessOverlap();
	void ProcessBlock(Collider* pOtherComponent);

	virtual bool isCollide(Collider* collider, Vector2& resolution) = 0;
	virtual bool isCollide(const Vector2& point) = 0;

	virtual void Update(float deltaTime);

	void SetPosition(Vector2 position);
	void AddPosition(Vector2 position);
	bool isBlock();

	const Vector2& GetOffset() { return offset; }
};

