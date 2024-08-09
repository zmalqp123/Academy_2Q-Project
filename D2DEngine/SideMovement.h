#pragma once
#include "Movement.h"

class SideMovement : public Movement
{
public:
    void Update(float delta) override;
};
