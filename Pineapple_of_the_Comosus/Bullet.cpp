#include "Bullet.h"
#include "../D2DEngine/SideMovement.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/Scene.h"
#include "../D2DEngine/SpriteAnimation.h"
#include "../D2DEngine/SpriteAnimationAsset.h"
#include "BulletFactory.h"
#include "Enemy.h"
#include "EnemyColliderNotify.h"



Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

//void Bullet::Init(float initSpeed, const Vector2& initDirection)
//{
//    speed = initSpeed;
//    direction = initDirection;
//
//    if (move)
//    {
//        // 방향 설정
//        //move->SetDirection(D2D1_VECTOR_2F{ direction.x, direction.y });
//
//        // 속도 설정
//        //move->SetSpeed(speed);
//
//        move->AddForce(direction * speed);
//    }
//}

void Bullet::Update(float deltaTime)
{
    

    // BoxCollider를 사용해 충돌 처리
    // 충돌 처리와 관련된 로직을 여기서 구현할 수 있음
    //if (pBoxcollider)
    //{
    //    AABB bound = pBoxcollider->GetBound();
    //    if (bound.m_Center.x < 0 || bound.m_Center.x > 1920 ||
    //        bound.m_Center.y < 0 || bound.m_Center.y > 1080)
    //    {
    //        // 화면 밖으로 나가면 총알을 비활성화
    //        //gameObject->isActive = false;
    //    }
    //}
    float x = gameObject->transform->m_WorldTransform.dx;
    float y = gameObject->transform->m_WorldTransform.dy;
    if (x < -1920.f || x > 1920.f || y < -600.f || y > 1600.f) {
        bulletFactory->ReturnBulletToPool(this);
    }
    OnGround();
    if (bulletType == BulletType::burst && isBursted()) {
        gameObject->isActive = false;
        bulletFactory->ReturnBulletToPool(this);
    }
    
}

void Bullet::Reset()
{
    gameObject->transform->pos.worldPosition = { 0.f, 0.f };
    // 총알의 상태를 초기화
    if (move)
    {
        move->SetSpeed(0.0f);
        move->SetDirection(Vector2{ 0.0f, 0.0f });
        move->isGravity = true;
    }

    // 박스 콜라이더 초기화 (필요시)
    if (pBoxcollider)
    {
        pBoxcollider->SetCenter(Vector2(0.0f, 0.0f));
        pBoxcollider->SetExtent(Vector2(50.0f, 50.0f));
    }

    // 기타 필요한 초기화 코드들
    //speed = 0.0f;
    //direction = Vector2(0.0f, 0.0f);
    id = 0;
    bombRange = 0.f;
    attackPower = 0.f;
    penetratingPower = 0;
    moveSpeed = 0.f;
    slowPower = 0.f;
    slowTime = 0.f;
	isBurst = false; 
    explode->SetAnimation(1, false);
    explode->m_AnimationIndex = 1;
    
}

void Bullet::SetAttackValue(const Vector2& direction,int _id, float _bombRange, float _attackPower, int _penetratingPower, float _moveSpeed, float _slowPower, float _slowTime, BulletType _bulletType)
{   
	id = _id;
    bombRange = _bombRange;
    attackPower = _attackPower;
    penetratingPower = _penetratingPower;
    moveSpeed = _moveSpeed;
    slowPower = _slowPower;
    slowTime = _slowTime;
    bulletType = _bulletType;

    if (move)
    {
        Vector2 dir = direction;
        move->AddForce(dir * moveSpeed);
    }
}

void Bullet::OnBlock(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void Bullet::OnBeginOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
    auto e = pOtherComponent->gameObject->GetComponent<EnemyColliderNotify>();
    if (e != nullptr) {

        //gameObject->isActive = false;
        if (bombRange > 0.f) {
            
        }
        penetratingPower--;
        //e->gameObject->isActive = false;
        //e->gameObject->GetComponent<FiniteStateMachine>()->SetState("Dead");
        e->enemy->Ondamage(attackPower,bulletType);
        if (slowPower > 0.f) e->enemy->OnSlow(slowPower, slowTime);
        std::cout << "bulletID: " <<gameObject->GetInstanceID() << "instanceid: " << e->GetInstanceID() << std::endl;
        if (penetratingPower <= 0) {
            
            if (bulletType == BulletType::burst) {
                OnBurst(bombRange);
            }
            else {
                gameObject->isActive = false;
                bulletFactory->ReturnBulletToPool(this);
            }
            
            
        }
        
    }
}

void Bullet::OnStayOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void Bullet::OnEndOverlap(Collider* pOwnedComponent, Collider* pOtherComponent)
{
}

void Bullet::OnGround()
{
    if (gameObject->transform->pos.worldPosition.y < -300) {
        
        if (bulletType == BulletType::burst) {
            OnBurst(bombRange);
            
        }

    }
    
	
}

void Bullet::OnBurst(float _bombRange) {
    auto iter = gameObject->ownerScene->m_GameObjects.begin();
    
    if(!isBurst){
        explode->SetAnimation(0, false);
		explode->m_AnimationIndex = 0;
		isBurst = true;
    }
    
    this->move->isGravity = false;
    if (isBurst = true) {
        for (; iter != gameObject->ownerScene->m_GameObjects.end(); iter++) {
            if ((*iter)->isActive == false) continue;
            EnemyColliderNotify* thisEnemy = (*iter)->GetComponent<EnemyColliderNotify>();

            if (thisEnemy == nullptr) continue;
            else {
                BoxCollider* thisBox = thisEnemy->gameObject->GetComponent<BoxCollider>();
                /*std::cout << "bound: " << thisBox->GetBound().GetMaxX() << ", " << thisBox->GetBound().GetMinX() << std::endl;
                std::cout << "bombrange: " << gameObject->transform->m_WorldTransform.dx + _bombRange << ", " << gameObject->transform->m_WorldTransform.dx - _bombRange << std::endl;*/

                if (thisBox->GetBound().GetMaxX() > gameObject->transform->m_WorldTransform.dx - _bombRange &&
                    thisBox->GetBound().GetMinX() < gameObject->transform->m_WorldTransform.dx + _bombRange &&
                    thisBox->GetBound().GetMaxY() > gameObject->transform->m_WorldTransform.dy - _bombRange &&
                    thisBox->GetBound().GetMinY() < gameObject->transform->m_WorldTransform.dy + _bombRange)
                {

                    thisEnemy->enemy->Ondamage(attackPower, bulletType);
                    if (slowPower > 0.f) thisEnemy->enemy->OnSlow(slowPower, slowTime);
                }


            }
        }
    }
    
    
}

bool Bullet::isBursted()
{   
    if (explode != nullptr
        && explode->m_AnimationIndex == 0
        && explode->IsLastFrame()) {
        return true;
    }
    else {
        return false;
    }

}
