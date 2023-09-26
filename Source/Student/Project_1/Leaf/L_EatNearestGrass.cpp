#include <pch.h>
#include "L_EatNearestGrass.h"

L_EatNearestGrass::L_EatNearestGrass() : timer(0.0f), target_pos(Vec3(0, 0, 0))
{}

void L_EatNearestGrass::on_enter()
{
   target_pos = agent->get_blackboard().get_value<Agent*>("target_grass")->get_position();
   BehaviorNode::on_leaf_enter();
}

void L_EatNearestGrass::on_update(float dt)
{
   const auto result = agent->move_toward_point(target_pos, dt);

   if (result == true)
   {
      agents->destroy_agent(agent->get_blackboard().get_value<Agent*>("target_grass"));
      on_success();
   }

   display_leaf_text();
}
