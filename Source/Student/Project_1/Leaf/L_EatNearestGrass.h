#pragma once
#include "BehaviorNode.h"

class L_EatNearestGrass : public BaseNode<L_EatNearestGrass>
{
public:
   L_EatNearestGrass();

protected:
    float timer;
    Vec3 target_pos;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};