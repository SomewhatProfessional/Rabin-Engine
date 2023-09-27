#include <pch.h>
#include "L_CheckForCollision.h"

#define COLLISION_DIST 1
static bool hit = false;

L_CheckForCollision::L_CheckForCollision()
{}

void L_CheckForCollision::on_enter()
{
   hit = false;
   Vec3 our_pos = agent->get_position();

   std::vector<Agent*> possible_targets = agents->get_all_agents();

   size_t size = possible_targets.size();
   for (int i = 0; i < size; i++)
   {
      if (possible_targets[i]->get_type() != "Hunter" && possible_targets[i]->get_type() != "Projectile")
      {
         Vec3 target_pos = possible_targets[i]->get_position();
         float dist = sqrt((target_pos.x - our_pos.x) * (target_pos.x - our_pos.x) + (target_pos.z - our_pos.z) * (target_pos.z - our_pos.z));

         if (dist <= COLLISION_DIST)
         {
            // Delete the projectile and the object it hit.
            agents->destroy_agent(agent);
            agents->destroy_agent(possible_targets[i]);
            hit = true;
            break;
         }
      }
   }

   // If we hit the edge of the map, delete ourselves.
   if(our_pos.x <= 0 || our_pos.x  >= 100 || our_pos.z <= 0 || our_pos.z >= 100)
      agents->destroy_agent(agent);

   BehaviorNode::on_leaf_enter();
}

void L_CheckForCollision::on_update(float dt)
{
   if(hit)
      on_success();
   else
      on_failure();

   display_leaf_text();
}
