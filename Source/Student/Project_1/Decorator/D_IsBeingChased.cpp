#include <pch.h>
#include "D_IsBeingChased.h"

#define CHASE_DISTANCE 20

D_IsBeingChased::D_IsBeingChased() : chased(false)
{}

void D_IsBeingChased::on_enter()
{
   chased = false;
   float nearest_distance = D3D10_FLOAT32_MAX;

   // If near a tiger agent
   Vec3 our_pos = agent->get_position();

   std::vector<Agent*> tigers = agents->get_all_agents_by_type("Tiger");
   for (int i = 0; i < tigers.size(); i++)
   {
      Vec3 tiger_pos = tigers[i]->get_position();
      float dist = sqrt((tiger_pos.x - our_pos.x) * (tiger_pos.x - our_pos.x) + (tiger_pos.z - our_pos.z) * (tiger_pos.z - our_pos.z));

      if (dist <= CHASE_DISTANCE)
      {
         if (dist < nearest_distance)
         {
            nearest_distance = dist;
            agent->get_blackboard().set_value("tiger_chaser", tigers[i]);
         }

         chased = true;
      }
   }

    BehaviorNode::on_enter();
}

void D_IsBeingChased::on_update(float dt)
{
    if (chased)
    {
        BehaviorNode *child = children.front();

        child->tick(dt);
        // assume same status as child
        set_status(child->get_status());
        set_result(child->get_result());
    }
    else
    {
       set_status(NodeStatus::EXITING);
       set_result(NodeResult::FAILURE);
    }
}
