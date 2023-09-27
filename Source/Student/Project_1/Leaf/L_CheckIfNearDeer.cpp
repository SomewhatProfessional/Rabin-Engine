#include <pch.h>
#include "L_CheckIfNearDeer.h"

#define DIST_TO_GRASS 10
static bool success = false;

L_CheckIfNearDeer::L_CheckIfNearDeer() : timer(0.0f)
{}

void L_CheckIfNearDeer::on_enter()
{
   success = false;
   float nearest_distance = D3D10_FLOAT32_MAX;

   // If near a grass agent
   Vec3 our_pos = agent->get_position();

   std::vector<Agent*> deer = agents->get_all_agents_by_type("Deer");
   for (int i = 0; i < deer.size(); i++)
   {
      Vec3 deer_pos = deer[i]->get_position();
      float dist = sqrt((deer_pos.x - our_pos.x) * (deer_pos.x - our_pos.x) + (deer_pos.z - our_pos.z) * (deer_pos.z - our_pos.z));

      if (dist <= DIST_TO_GRASS)
      {
         if (dist < nearest_distance)
         {
            nearest_distance = dist;
            agent->get_blackboard().set_value("target_deer", deer[i]);
         }

         success = true;
      }
   }

   BehaviorNode::on_leaf_enter();
}

void L_CheckIfNearDeer::on_update(float dt)
{
   if(success)
      on_success();
   else
      on_failure();

   display_leaf_text();
}
