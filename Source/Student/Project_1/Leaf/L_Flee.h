#pragma once
#include "BehaviorNode.h"

class L_Flee : public BaseNode<L_Flee>
{
public:
   L_Flee();

protected:
    float timer;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};