#include <pch.h>
#include "L_EatNearestGrass.h"

L_EatNearestGrass::L_EatNearestGrass() : timer(0.0f)
{}

void L_EatNearestGrass::on_enter()
{
   BehaviorNode::on_leaf_enter();
}

void L_EatNearestGrass::on_update(float dt)
{
   Agent* target = agent->get_blackboard().get_value<Agent*>("target_grass");
   const auto result = agent->move_toward_point(target->get_position(), dt);

   if (result == true)
   {
      agents->destroy_agent(target);
      on_success();
   }

   display_leaf_text();
}
