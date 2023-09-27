#pragma once
#include "BehaviorNode.h"

class L_LeadTarget : public BaseNode<L_LeadTarget>
{
public:
   L_LeadTarget();

protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};