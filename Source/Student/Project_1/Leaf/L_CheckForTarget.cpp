#include <pch.h>
#include "L_CheckForTarget.h"

#define DIST_TO_TARGET 20
static bool success = false;

L_CheckForTarget::L_CheckForTarget()
{}

void L_CheckForTarget::on_enter()
{
   success = false;
   float nearest_distance = D3D10_FLOAT32_MAX;

   // If near a grass agent
   Vec3 our_pos = agent->get_position();

   std::vector<Agent*> possible_targets = agents->get_all_agents_by_type("Deer");
   std::vector<Agent*> tigers = agents->get_all_agents_by_type("Tiger");
   possible_targets.insert(possible_targets.end(), tigers.begin(), tigers.end());

   size_t size = possible_targets.size();
   for (int i = 0; i < size; i++)
   {
      Vec3 target_pos = possible_targets[i]->get_position();
      float dist = sqrt((target_pos.x - our_pos.x) * (target_pos.x - our_pos.x) + (target_pos.z - our_pos.z) * (target_pos.z - our_pos.z));

      if (dist <= DIST_TO_TARGET)
      {
         if (dist < nearest_distance)
         {
            nearest_distance = dist;
            agent->get_blackboard().set_value("target", possible_targets[i]);
         }

         success = true;
      }
   }

   BehaviorNode::on_leaf_enter();
}

void L_CheckForTarget::on_update(float dt)
{
   if(success)
      on_success();
   else
      on_failure();

   display_leaf_text();
}
