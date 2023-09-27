#include <pch.h>
#include "L_Flee.h"

#define FLEE_DISTANCE 5
#define SPEED_BONUS 2

L_Flee::L_Flee() : timer(0.0f)
{}

void L_Flee::on_enter()
{
   timer = RNG::range(2.0f, 3.0f);

   BehaviorNode::on_leaf_enter();
}

void L_Flee::on_update(float dt)
{
   timer -= dt;

   if (timer > 0)
   {
      // Get the forward vector of the tiger chasing us.
      Agent* tiger = agent->get_blackboard().get_value<Agent*>("tiger_chaser");
      Vec3 tiger_vec = tiger->get_forward_vector() + tiger->get_right_vector();

      // Add the tiger's forward vector to our position
      Vec3 new_position = agent->get_position() + (tiger_vec);

      // If this puts us off of the world, just go as close to the edge as possible.
      if (new_position.x < 0)
         new_position.x = 0;
      else if (new_position.x > 100)
         new_position.x = 100;

      if (new_position.z < 0)
         new_position.z = 0;
      else if (new_position.z > 100)
         new_position.z = 100;

      agent->move_toward_point(new_position, dt * SPEED_BONUS);
   }
   else
   {
      on_success();
   }

   display_leaf_text();
}
