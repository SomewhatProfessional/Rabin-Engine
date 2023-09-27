#pragma once
#include "BehaviorNode.h"

class L_FindMouse : public BaseNode<L_FindMouse>
{
public:
   L_FindMouse();

protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};