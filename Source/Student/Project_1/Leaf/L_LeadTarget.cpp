#include <pch.h>
#include "L_LeadTarget.h"

#define LEAD_DISTANCE 5

L_LeadTarget::L_LeadTarget()
{}

void L_LeadTarget::on_enter()
{
   BehaviorNode::on_leaf_enter();
}

void L_LeadTarget::on_update(float dt)
{
   Agent* target = agent->get_blackboard().get_value<Agent*>("target");

   // Only lead the target if it is a tiger.
   if (target->get_type() == "Tiger")
   {
      Vec3 target_pos = target->get_position();
      target_pos += target->get_forward_vector() * LEAD_DISTANCE;


      agent->get_blackboard().set_value("target_pos", target_pos);
      on_success();
   }
   else
      on_failure();

   display_leaf_text();
}
