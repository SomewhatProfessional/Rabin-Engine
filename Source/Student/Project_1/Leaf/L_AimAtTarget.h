#pragma once
#include "BehaviorNode.h"

class L_AimAtTarget : public BaseNode<L_AimAtTarget>
{
public:
   L_AimAtTarget();

protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};