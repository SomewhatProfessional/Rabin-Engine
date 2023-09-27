#pragma once
#include "BehaviorNode.h"

class L_CheckForCollision : public BaseNode<L_CheckForCollision>
{
public:
   L_CheckForCollision();

protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};