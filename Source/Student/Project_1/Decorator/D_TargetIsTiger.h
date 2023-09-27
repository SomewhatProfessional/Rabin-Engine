#pragma once
#include "BehaviorNode.h"

class D_TargetIsTiger : public BaseNode<D_TargetIsTiger>
{
public:
   D_TargetIsTiger();

protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};