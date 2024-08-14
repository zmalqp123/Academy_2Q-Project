#include "Enemy.h"
#include "../D2DEngine/Movement.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "MainPineApple.h"


void Enemy::Init()
{
    // SpriteRenderer 컴포넌트 생성 및 설정
    
    // move 컴포넌트 생성 및 설정
    //move = gameObject->GetComponent<Movement>();
}




void Enemy::Update(float delta)
{
  //  // 이동 로직
  //// sin 파동을 이용한 y 좌표 변동을 위한 변수

  //  elapsedTime += delta;

  //  // 현재 위치를 가져옴
  //  auto& position = gameObject->transform->pos.worldPosition;

  //  // y축을 sin 파동으로 변동
  //  float waveAmplitude = 20.f;  // 파동의 진폭 (위아래 움직임의 크기)
  //  float waveFrequency = 10.f;   // 파동의 주기 (움직임의 속도) -> 튀기는 속도 
  //  //position.y += std::sin(elapsedTime * waveFrequency) * waveAmplitude * delta ;

  //  float tmp = std::sinf(elapsedTime * waveFrequency) * waveAmplitude;// *delta;
  //  //std::cout << tmp << std::endl;
  //  if (tmp < 0.f)
  //  {
  //      tmp *= -1.f;
  //  }
  //  position.y = tmp + tmpY;


  //  // 갱신된 위치를 적용
  //  // gameObject->transform->pos.worldPosition = position;  

    //WaveMove(delta);
}

void Enemy::Render(D2D1_MATRIX_3X2_F cameraMat)
{
}

void Enemy::WaveMove(float delta)
{
    // 이동 로직
    // sin 파동을 이용한 y 좌표 변동을 위한 변수

    elapsedTime += delta;

    // 현재 위치를 가져옴
    auto& position = gameObject->transform->pos.worldPosition;

    // y축을 sin 파동으로 변동
    float waveAmplitude = 20.f;  // 파동의 진폭 (위아래 움직임의 크기)
    float waveFrequency = 10.f;   // 파동의 주기 (움직임의 속도) -> 튀기는 속도 
    //position.y += std::sin(elapsedTime * waveFrequency) * waveAmplitude * delta ;

    float tmp = std::sinf(elapsedTime * waveFrequency) * waveAmplitude;// *delta;
    //std::cout << tmp << std::endl;
    if (tmp < 0.f)
    {
        tmp *= -1.f;
    }
    position.y = tmp + tmpY;


    // 갱신된 위치를 적용
    // gameObject->transform->pos.worldPosition = position;  
}

void Enemy::Ondamage(int damage, BulletType bulletType)
{   
    int resist = 0;
    switch (bulletType)
    {
    case BulletType::arrow:
        resist = enemyData.resistArrow;
        break;
    case BulletType::bullet:
        resist = enemyData.resistBullet;
        break;
    case BulletType::burst:
        resist = enemyData.resistBurst;
        break;
    }
    float hundred = 0.01f;
    enemyData.hp -= damage * (1 - resist * hundred);
	if (enemyData.hp <= 0)
	{
        gameObject->isActive = false;
        notify->isActive = false;
        //mainPineApple->acquireGold(enemyData.reward);
        //mainPineApple->monAcquireEXP(enemyData.expReward);
	    gameObject->GetComponent<FiniteStateMachine>()->SetState("Dead");
	}
}


