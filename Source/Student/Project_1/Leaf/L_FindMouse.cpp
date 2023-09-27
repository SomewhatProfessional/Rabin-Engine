#include <pch.h>
#include "L_FindMouse.h"

L_FindMouse::L_FindMouse()
{}

void L_FindMouse::on_enter()
{
   // grab the current mouse pos
   const auto& mousePos = InputHandler::get_mouse_position();

   // we want to know where on the ground the mouse is
   const auto& plane = terrain->get_terrain_plane();

   // find out where on the plane the mouse is
   const auto worldPos = renderer->screen_to_world(mousePos.x, mousePos.y, plane);

   // if the mouse pos is actually on the plane
   if (worldPos.second == true)
   {
      // write the world position into the blackboard
      agent->get_blackboard().set_value("mouse_pos", worldPos.first);
   }
   else
   {
      // write a default position value into the blackboard
      agent->get_blackboard().set_value("mouse_pos", Vec3(-1, -1, -1));
   }

   BehaviorNode::on_leaf_enter();
}

void L_FindMouse::on_update(float dt)
{
   on_success();
   display_leaf_text();
}
