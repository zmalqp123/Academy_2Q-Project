#pragma
#include <vector>
#include "../D2DEngine/Scene.h"
#include "../D2DEngine/GameObject.h"

class Bullet;

class BulletFactory
{
public:
    BulletFactory(Scene* scene);
    ~BulletFactory();

    Bullet* GetBulletFromPool();
    void ReturnBulletToPool(Bullet* bullet);

private:
    Scene* scene;
    std::vector<Bullet*> m_BulletPool;
    const int initialPoolSize = 20;

    void InitializePool();
    Bullet* CreateBullet();
};
