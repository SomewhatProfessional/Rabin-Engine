#include <pch.h>
#include "L_AimAtTarget.h"

L_AimAtTarget::L_AimAtTarget()
{}

void L_AimAtTarget::on_enter()
{

   BehaviorNode::on_leaf_enter();
}

void L_AimAtTarget::on_update(float dt)
{
   Agent* target = agent->get_blackboard().get_value<Agent*>("target");
   agent->get_blackboard().set_value("target_pos", target->get_position());

   on_success();
   display_leaf_text();
}
