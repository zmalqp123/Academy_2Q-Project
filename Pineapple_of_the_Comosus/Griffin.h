#pragma once
#include "Enemy.h"

class Griffin : public Enemy
{
public:
    Griffin() = default;

    virtual void Init() override;
    virtual void Update(float delta) override;
    virtual void Render(D2D1_MATRIX_3X2_F cameraMat) override;
};

