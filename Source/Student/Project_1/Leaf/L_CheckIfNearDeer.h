#pragma once
#include "BehaviorNode.h"

class L_CheckIfNearDeer : public BaseNode<L_CheckIfNearDeer>
{
public:
   L_CheckIfNearDeer();

protected:
    float timer;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};