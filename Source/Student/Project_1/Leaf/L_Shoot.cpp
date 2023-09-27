#include <pch.h>
#include "L_Shoot.h"
#include "TreeInfo.h"

L_Shoot::L_Shoot()
{}

void L_Shoot::on_enter()
{
   // Rotate towards the target
   Vec3 target_pos = agent->get_blackboard().get_value<Vec3>("target_pos");
   Vec3 agent_pos = agent->get_position();
   float angle = atan2(target_pos.x - agent_pos.x, target_pos.z - agent_pos.z);
   agent->set_yaw(angle);

   // Fire a projectile
   Agent* projectile = agents->create_behavior_agent("Projectile", BehaviorTreeTypes::Projectile);
   projectile->set_specific_scaling(Vec3(0.5f, 0.5f, 0.5f));
   projectile->set_color(Vec3(0.5f, 0.5f, 0.5f));
   projectile->set_yaw(angle);
   projectile->set_position(agent_pos);

   BehaviorNode::on_leaf_enter();
}

void L_Shoot::on_update(float dt)
{
   on_success();
   display_leaf_text();
}
