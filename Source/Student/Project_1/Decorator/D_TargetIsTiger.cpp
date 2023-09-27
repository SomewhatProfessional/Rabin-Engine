#include <pch.h>
#include "D_TargetIsTiger.h"


D_TargetIsTiger::D_TargetIsTiger()
{}

void D_TargetIsTiger::on_enter()
{
    BehaviorNode::on_enter();
}

void D_TargetIsTiger::on_update(float dt)
{
    if (agent->get_blackboard().get_value<Agent*>("target")->get_type() == "Tiger")
    {
        BehaviorNode *child = children.front();

        child->tick(dt);
        // assume same status as child
        set_status(child->get_status());
        set_result(child->get_result());
    }
    else
    {
       set_status(NodeStatus::EXITING);
       set_result(NodeResult::FAILURE);
    }
}
