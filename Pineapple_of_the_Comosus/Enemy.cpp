#include "Enemy.h"
#include "DataManager.h"
void Enemy::Init()
{
    // SpriteRenderer 컴포넌트 생성 및 설정


}

void Enemy::Update(float delta)
{
    //// 이동 로직 예시 : 이동 범위를 넘지 않도록 조정
    //    position.x += speed * delta;
    //if (position.x < minBounds.x)
    //    position.x = minBounds.x;
    //if (position.x > maxBounds.x)
    //    position.x = maxBounds.x;
}

void Enemy::Render(D2D1_MATRIX_3X2_F cameraMat)
{
}
