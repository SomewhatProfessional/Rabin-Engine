#pragma once
#include "BehaviorNode.h"

class L_RotateToMouse : public BaseNode<L_RotateToMouse>
{
public:
   L_RotateToMouse();

protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};