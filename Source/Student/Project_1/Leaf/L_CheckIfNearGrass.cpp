#include <pch.h>
#include "L_CheckIfNearGrass.h"

#define DIST_TO_GRASS 10
static bool success = false;

L_CheckIfNearGrass::L_CheckIfNearGrass() : timer(0.0f)
{}

void L_CheckIfNearGrass::on_enter()
{
   success = false;
   float nearest_distance = D3D10_FLOAT32_MAX;

   // If near a grass agent
   Vec3 our_pos = agent->get_position();

   std::vector<Agent*> grasses = agents->get_all_agents_by_type("Grass");
   for (int i = 0; i < grasses.size(); i++)
   {
      Vec3 grass_pos = grasses[i]->get_position();
      float dist = sqrt((grass_pos.x - our_pos.x) * (grass_pos.x - our_pos.x) + (grass_pos.z - our_pos.z) * (grass_pos.z - our_pos.z));

      if (dist <= DIST_TO_GRASS)
      {
         if (dist < nearest_distance)
         {
            nearest_distance = dist;
            agent->get_blackboard().set_value("target_grass", grasses[i]);
         }

         success = true;
      }
   }

   BehaviorNode::on_leaf_enter();
}

void L_CheckIfNearGrass::on_update(float dt)
{
   if(success)
      on_success();
   else
      on_failure();

   display_leaf_text();
}
