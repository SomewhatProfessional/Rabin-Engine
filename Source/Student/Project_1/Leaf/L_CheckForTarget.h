#pragma once
#include "BehaviorNode.h"

class L_CheckForTarget : public BaseNode<L_CheckForTarget>
{
public:
   L_CheckForTarget();

protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};