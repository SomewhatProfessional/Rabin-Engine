#pragma once
#include "BehaviorNode.h"

class L_EatNearestDeer : public BaseNode<L_EatNearestDeer>
{
public:
   L_EatNearestDeer();

protected:
    float timer;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};