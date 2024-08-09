#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/Vector.h"
#include "../D2DEngine/Collider.h"

class SideMovement;
class BoxCollider;
class BulletFactory;
class Bullet : public Component, public IColliderNotify
{
public:
    Bullet();
    ~Bullet();

    void Init(float speed, const Vector2& direction);
    void Update(float deltaTime) override;
    void Reset();

    // Movement�� BoxCollider�� BulletFactory���� ����
    SideMovement* move;
    BoxCollider* pBoxcollider;

    BulletFactory* bulletFactory;
private:
    float speed;
    Vector2 direction;

    // IColliderNotify��(��) ���� ��ӵ�
    void OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent) override;
    void OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
    void OnStayOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
    void OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent) override;
};
