#pragma once
#include "Enemy.h"

class MusKetShooter : public Enemy
{
public:
	MusKetShooter();

    virtual void Init() override;
    virtual void Update(float delta) override;
    virtual void Render(D2D1_MATRIX_3X2_F cameraMat) override;
};

