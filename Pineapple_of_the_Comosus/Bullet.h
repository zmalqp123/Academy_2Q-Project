#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/Vector.h"

class SideMovement;
class BoxCollider;

class BulletFactory;
class Bullet : public Component
{
public:
    Bullet();
    ~Bullet();

    void Init(float speed, const Vector2& direction);
    void Update(float deltaTime) override;
    void Reset();

    // Movement와 BoxCollider는 BulletFactory에서 설정
    SideMovement* move;
    BoxCollider* pBoxcollider;

    BulletFactory* bulletFactory;
private:
    float speed;
    Vector2 direction;
};
