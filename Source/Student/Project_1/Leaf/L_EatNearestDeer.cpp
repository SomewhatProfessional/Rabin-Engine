#include <pch.h>
#include "L_EatNearestDeer.h"

L_EatNearestDeer::L_EatNearestDeer() : timer(0.0f)
{}

void L_EatNearestDeer::on_enter()
{
   BehaviorNode::on_leaf_enter();
}

void L_EatNearestDeer::on_update(float dt)
{
   Agent* target_deer = agent->get_blackboard().get_value<Agent*>("target_deer");
   const auto result = agent->move_toward_point(target_deer->get_position(), dt);

   if (result == true)
   {
      agents->destroy_agent(target_deer);
      on_success();
   }

   display_leaf_text();
}
