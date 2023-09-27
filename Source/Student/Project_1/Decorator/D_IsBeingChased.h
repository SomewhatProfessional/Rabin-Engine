#pragma once
#include "BehaviorNode.h"

class D_IsBeingChased : public BaseNode<D_IsBeingChased>
{
public:
   D_IsBeingChased();

protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

    bool chased;
};