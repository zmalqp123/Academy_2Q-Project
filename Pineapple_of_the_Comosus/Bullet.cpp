#include "Bullet.h"
#include "../D2DEngine/SideMovement.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include "Enemy.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::Init(float initSpeed, const Vector2& initDirection)
{
    speed = initSpeed;
    direction = initDirection;

    if (move)
    {
        // 방향 설정
        //move->SetDirection(D2D1_VECTOR_2F{ direction.x, direction.y });

        // 속도 설정
        //move->SetSpeed(speed);

        move->AddForce(direction * speed);
    }
}

void Bullet::Update(float deltaTime)
{
    

    // BoxCollider를 사용해 충돌 처리
    // 충돌 처리와 관련된 로직을 여기서 구현할 수 있음
    if (pBoxcollider)
    {
        AABB bound = pBoxcollider->GetBound();
        if (bound.m_Center.x < 0 || bound.m_Center.x > 1920 ||
            bound.m_Center.y < 0 || bound.m_Center.y > 1080)
        {
            // 화면 밖으로 나가면 총알을 비활성화
            //gameObject->isActive = false;
        }
    }
}

void Bullet::Reset()
{
    // 총알의 상태를 초기화
    if (move)
    {
        move->SetSpeed(0.0f);
        move->SetDirection(D2D1_VECTOR_2F{ 0.0f, 0.0f });
    }

    // 박스 콜라이더 초기화 (필요시)
    if (pBoxcollider)
    {
        pBoxcollider->SetCenter(Vector2(0.0f, 0.0f));
        pBoxcollider->SetExtent(Vector2(50.0f, 50.0f));
    }

    // 기타 필요한 초기화 코드들
    speed = 0.0f;
    direction = Vector2(0.0f, 0.0f);
}

void Bullet::OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void Bullet::OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
    auto e = pOtherComponent->gameObject->GetComponent<Enemy>();
    if(e!= nullptr)
        gameObject->isActive = false;
}

void Bullet::OnStayOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void Bullet::OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}
