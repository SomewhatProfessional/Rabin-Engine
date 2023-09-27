#pragma once
#include "BehaviorNode.h"

class L_MoveForward : public BaseNode<L_MoveForward>
{
public:
   L_MoveForward();

protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};