#pragma once
#include "BehaviorNode.h"

class L_CheckIfEaten : public BaseNode<L_CheckIfEaten>
{
public:
   L_CheckIfEaten();

protected:
    float timer;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};