#include <pch.h>
#include "L_RotateToMouse.h"

L_RotateToMouse::L_RotateToMouse()
{}

void L_RotateToMouse::on_enter()
{
   BehaviorNode::on_leaf_enter();
}

void L_RotateToMouse::on_update(float dt)
{
   // Make sure the mouse pos is valid
   Vec3 mouse_pos = agent->get_blackboard().get_value<Vec3>("mouse_pos");
   if (mouse_pos != Vec3(-1, -1, -1))
   {
      // Calculate which way we need to turn.
      Vec3 agent_pos = agent->get_position();
      float angle = atan2(mouse_pos.x - agent_pos.x, mouse_pos.z - agent_pos.z);
      
      agent->set_yaw(angle);
   }

   on_success();
   display_leaf_text();
}
