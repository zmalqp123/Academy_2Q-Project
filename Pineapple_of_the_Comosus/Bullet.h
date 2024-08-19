#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/Vector.h"
#include "../D2DEngine/Collider.h"

class SideMovement;
class BoxCollider;
class BulletFactory;
class SpriteAnimation;
enum class BulletType {
    normal,
    arrow,
    bullet,
    burst,
};

class Bullet : public Component, public IColliderNotify
{
public:
    Bullet();
    ~Bullet();
    int id = 0;
	bool isBurst = false;
    //void Init(float speed, const Vector2& direction);
    void Update(float deltaTime) override;
    void Reset();

    void SetAttackValue(const Vector2& direction,int _id, float _bombRange, float _attackPower, int _penetratingPower, float _moveSpeed, float _slowPower, float _slowTime, BulletType _bulletType);

    // Movement�� BoxCollider�� BulletFactory���� ����
    SideMovement* move;
    BoxCollider* pBoxcollider;
	SpriteAnimation* explode;
	SpriteAnimation* bulletSprite;
    BulletFactory* bulletFactory;
private:
	
    float bombRange = 0.f;
    float attackPower = 0.f;
    int penetratingPower = 0;
    float moveSpeed = 0.f;
    float slowPower = 0.f;
    float slowTime = 0.f;
    BulletType bulletType;

private:
    // IColliderNotify��(��) ���� ��ӵ�
    void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) override;
    void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
    void OnStayOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
    void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
    void OnGround();
    void OnBurst(float _bombRange);
    bool isBursted();
};
