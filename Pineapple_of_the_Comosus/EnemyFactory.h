#pragma once  // #pragma once는 헤더 파일이 한 번만 포함되도록 보장합니다.

#include "SwordMan.h"
#include "BombCart.h"
#include "Griffin.h"
#include "HeavyKnight.h"
#include "MusketShooter.h"
#include "../D2DEngine/Scene.h"  // Scene 헤더를 포함합니다.

#include <vector>
#include <unordered_map>
#include <random>
class BulletFactory;
class MainPineApple;
class EnemyFactory
{
public:
    int enemyType;
    EnemyFactory(Scene* scene);
    ~EnemyFactory();

    // 적을 생성하는 메서드
    Enemy* CreateEnemy(int type);

    // 랜덤 적을 생성하는 메서드
    Enemy* CreateRandomEnemy();

    // 풀에서 적을 가져오는 메서드
    Enemy* GetEnemyFromPool(int type);

    // 적을 풀에 반환하는 메서드
    void ReturnEnemyToPool(Enemy* enemy);

    void InitializePool(); // 적 풀 초기화 메서드

    BulletFactory* bulletFactory;
    MainPineApple* mainPineApple;
private:
    Scene* scene;

    std::unordered_map<std::wstring, std::vector<Enemy*>> enemyPool;

    std::vector<Enemy*> m_EnemyPool;  // 적 풀을 저장하는 벡터
    const int initialPoolSize = 20;   // 초기 풀 크기 (임의로 설정, 필요에 따라 변경 가능)
};
