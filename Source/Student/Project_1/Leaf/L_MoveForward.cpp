#include <pch.h>
#include "L_MoveForward.h"

#define SPEED 6

L_MoveForward::L_MoveForward()
{}

void L_MoveForward::on_enter()
{
   BehaviorNode::on_leaf_enter();
}

void L_MoveForward::on_update(float dt)
{
   // Add our forward vector to our position
   Vec3 new_position = agent->get_position() + agent->get_forward_vector();

   // If this puts us off of the world, just go as close to the edge as possible.
   if (new_position.x < 0)
      new_position.x = 0;
   else if (new_position.x > 100)
      new_position.x = 100;

   if (new_position.z < 0)
      new_position.z = 0;
   else if (new_position.z > 100)
      new_position.z = 100;

   agent->move_toward_point(new_position, dt * SPEED);

   on_success();
   display_leaf_text();
}
