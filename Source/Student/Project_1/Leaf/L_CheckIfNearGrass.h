#pragma once
#include "BehaviorNode.h"

class L_CheckIfNearGrass : public BaseNode<L_CheckIfNearGrass>
{
public:
   L_CheckIfNearGrass();

protected:
    float timer;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};