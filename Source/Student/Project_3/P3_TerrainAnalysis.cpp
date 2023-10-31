#include <pch.h>
#include "Terrain/TerrainAnalysis.h"
#include "Terrain/MapMath.h"
#include "Agent/AStarAgent.h"
#include "Terrain/MapLayer.h"
#include "Projects/ProjectThree.h"

#include <iostream>

bool ProjectThree::implemented_fog_of_war() const // extra credit
{
   return false;
}

float distance_to_closest_wall(int row, int col)
{
   /*
       Check the euclidean distance from the given cell to every other wall cell,
       with cells outside the map bounds treated as walls, and return the smallest
       distance.  Make use of the is_valid_grid_position and is_wall member
       functions in the global terrain to determine if a cell is within map bounds
       and a wall, respectively.
   */

   // WRITE YOUR CODE HERE
   float smallest = D3D10_FLOAT32_MAX;

   for (int row_ = -1; row_ < 41; row_++)
   {
      for (int col_ = -1; col_ < 41; col_++)
      {
         if (terrain->is_valid_grid_position(row_, col_) == false)
         {
            float result = static_cast<float>(sqrt(pow(row_ - row, 2) + pow(col_ - col, 2)));
            if (result < smallest && result != 0)
               smallest = result;
         }
         else if (terrain->is_wall(row_, col_))
         {
            float result = static_cast<float>(sqrt(pow(row_ - row, 2) + pow(col_ - col, 2)));
            if (result < smallest && result != 0)
               smallest = result;
         }
      }
   }

   return smallest;
}

bool is_clear_path(int row0, int col0, int row1, int col1)
{
   /*
       Two cells (row0, col0) and (row1, col1) are visible to each other if a line
       between their centerpoints doesn't intersect the four boundary lines of every
       wall cell.  You should puff out the four boundary lines by a very tiny amount
       so that a diagonal line passing by the corner will intersect it.  Make use of the
       line_intersect helper function for the intersection test and the is_wall member
       function in the global terrain to determine if a cell is a wall or not.
   */

   int width = terrain->get_map_width();
   int height = terrain->get_map_height();

   for (float row = 0; row < width; row++)
   {
      for (float col = 0; col < height; col++)
      {
         if (terrain->is_wall(static_cast<int>(row), static_cast<int>(col)))
         {
            // Check all for sides of the wall.
            Vec2 P0 = Vec2(static_cast<float>(row0), static_cast<float>(col0));
            Vec2 P1 = Vec2(static_cast<float>(row1), static_cast<float>(col1));
            float omega = 0.5f;
            Vec2 upper_left  = Vec2(row - omega, col - omega);
            Vec2 upper_right = Vec2(row + omega, col - omega);
            Vec2 lower_left  = Vec2(row - omega, col + omega);
            Vec2 lower_right = Vec2(row + omega, col + omega);

            Vec3 bruh1 = terrain->get_world_position(static_cast<int>(row), static_cast<int>(col));
            Vec3 bruh2 = terrain->get_world_position(static_cast<int>(row + 1), static_cast<int>(col));

            if (line_intersect(P0, P1, upper_left, upper_right)
               || line_intersect(P0, P1, upper_right, lower_right)
               || line_intersect(P0, P1, lower_right, lower_left)
               || line_intersect(P0, P1, lower_left, upper_left))
            {
               return false;
            }


         }

      }
   }

   return true;
}

void analyze_openness(MapLayer<float>& layer)
{
   /*
       Mark every cell in the given layer with the value 1 / (d * d),
       where d is the distance to the closest wall or edge.  Make use of the
       distance_to_closest_wall helper function.  Walls should not be marked.
   */
   int width = terrain->get_map_width();
   int height = terrain->get_map_height();

   for (int row = 0; row < width; row++)
   {
      for (int col = 0; col < height; col++)
      {
         if(!terrain->is_wall(row, col))
            layer.set_value(row, col, (1.0f / static_cast<float>(pow(distance_to_closest_wall(row, col), 2))));
      }
   }
}

void analyze_visibility(MapLayer<float>& layer)
{
   /*
       Mark every cell in the given layer with the number of cells that
       are visible to it, divided by 160 (a magic number that looks good).  Make sure
       to cap the value at 1.0 as well.

       Two cells are visible to each other if a line between their centerpoints doesn't
       intersect the four boundary lines of every wall cell.  Make use of the is_clear_path
       helper function.
   */

   int width = terrain->get_map_width();
   int height = terrain->get_map_height();

   for (int row = 0; row < width; row++)
   {
      for (int col = 0; col < height; col++)
      {
         if (terrain->is_wall(row, col))
            continue;

         int visible_cells = 0;
         
         for (int row_ = 0; row_ < width; row_++)
         {
            for (int col_ = 0; col_ < height; col_++)
            {
               if (!terrain->is_wall(row_, col_) && is_clear_path(row, col, row_, col_))
                  visible_cells++;
            }
         }

         float value = visible_cells / 160.0f;
         if (value > 1.0f)
            value = 1.0f;

         layer.set_value(row, col, value);
      }
   }
}

void analyze_visible_to_cell(MapLayer<float>& layer, int row, int col)
{
   /*
       For every cell in the given layer mark it with 1.0
       if it is visible to the given cell, 0.5 if it isn't visible but is next to a visible cell,
       or 0.0 otherwise.

       Two cells are visible to each other if a line between their centerpoints doesn't
       intersect the four boundary lines of every wall cell.  Make use of the is_clear_path
       helper function.
   */

   // WRITE YOUR CODE HERE
}

void analyze_agent_vision(MapLayer<float>& layer, const Agent* agent)
{
   /*
       For every cell in the given layer that is visible to the given agent,
       mark it as 1.0, otherwise don't change the cell's current value.

       You must consider the direction the agent is facing.  All of the agent data is
       in three dimensions, but to simplify you should operate in two dimensions, the XZ plane.

       Take the dot product between the view vector and the vector from the agent to the cell,
       both normalized, and compare the cosines directly instead of taking the arccosine to
       avoid introducing floating-point inaccuracy (larger cosine means smaller angle).

       Give the agent a field of view slighter larger than 180 degrees.

       Two cells are visible to each other if a line between their centerpoints doesn't
       intersect the four boundary lines of every wall cell.  Make use of the is_clear_path
       helper function.
   */

   // WRITE YOUR CODE HERE
}

void propagate_solo_occupancy(MapLayer<float>& layer, float decay, float growth)
{
   /*
       For every cell in the given layer:

           1) Get the value of each neighbor and apply decay factor
           2) Keep the highest value from step 1
           3) Linearly interpolate from the cell's current value to the value from step 2
              with the growing factor as a coefficient.  Make use of the lerp helper function.
           4) Store the value from step 3 in a temporary layer.
              A float[40][40] will suffice, no need to dynamically allocate or make a new MapLayer.

       After every cell has been processed into the temporary layer, write the temporary layer into
       the given layer;
   */

   float temp_layer[40][40];
   int width = terrain->get_map_width();
   int height = terrain->get_map_height();

   // For each cell
   for (int row = 0; row < width; row++)
   {
      for (int col = 0; col < height; col++)
      {
         float highest = 0;
         float value = 0;
         float distance = 0;

         // For each neighbor of the cell
         for (int row_offset = -1; row_offset < 2; row_offset++)
         {
            for (int col_offset = -1; col_offset < 2; col_offset++)
            {
               if (terrain->is_valid_grid_position(row + row_offset, col + col_offset))
               {
                  if (row_offset == col_offset)
                  {
                     if (row_offset == 0)
                        continue;
                     distance = 1.41f;
                  }
                  else
                     distance = 1.0f;

                  value = layer.get_value(row + row_offset, col + col_offset);
                  value = value * exp(-1 * distance * decay);

                  if (value > highest)
                     highest = value;
               }
            }
         }

         float new_value = lerp(layer.get_value(row, col), highest, growth);
         temp_layer[row][col] = new_value;
      }
   }

   for (int row = 0; row < width; row++)
   {
      for (int col = 0; col < height; col++)
      {
         layer.set_value(row, col, temp_layer[row][col]);
      }
   }
}

void propagate_dual_occupancy(MapLayer<float>& layer, float decay, float growth)
{
   /*
       Similar to the solo version, but the values range from -1.0 to 1.0, instead of 0.0 to 1.0

       For every cell in the given layer:

       1) Get the value of each neighbor and apply decay factor
       2) Keep the highest ABSOLUTE value from step 1
       3) Linearly interpolate from the cell's current value to the value from step 2
          with the growing factor as a coefficient.  Make use of the lerp helper function.
       4) Store the value from step 3 in a temporary layer.
          A float[40][40] will suffice, no need to dynamically allocate or make a new MapLayer.

       After every cell has been processed into the temporary layer, write the temporary layer into
       the given layer;
   */
}

void normalize_solo_occupancy(MapLayer<float>& layer)
{
   /*
       Determine the maximum value in the given layer, and then divide the value
       for every cell in the layer by that amount.  This will keep the values in the
       range of [0, 1].  Negative values should be left unmodified.
   */

   float highest = 0;
   int width = terrain->get_map_width();
   int height = terrain->get_map_height();

   for (int row = 0; row < width; row++)
   {
      for (int col = 0; col < height; col++)
      {
         float value = layer.get_value(row, col);
         if (value > highest)
            highest = value;
      }
   }

   for (int row = 0; row < width; row++)
   {
      for (int col = 0; col < height; col++)
      {
         float value = layer.get_value(row, col);
         if (value > 0)
            layer.set_value(row, col, value / highest);
      }
   }
}

void normalize_dual_occupancy(MapLayer<float>& layer)
{
   /*
       Similar to the solo version, but you need to track greatest positive value AND
       the least (furthest from 0) negative value.

       For every cell in the given layer, if the value is currently positive divide it by the
       greatest positive value, or if the value is negative divide it by -1.0 * the least negative value
       (so that it remains a negative number).  This will keep the values in the range of [-1, 1].
   */

   // WRITE YOUR CODE HERE
}

void enemy_field_of_view(MapLayer<float>& layer, float fovAngle, float closeDistance, float occupancyValue, AStarAgent* enemy)
{
   /*
       First, clear out the old values in the map layer by setting any negative value to 0.
       Then, for every cell in the layer that is within the field of view cone, from the
       enemy agent, mark it with the occupancy value.  Take the dot product between the view
       vector and the vector from the agent to the cell, both normalized, and compare the
       cosines directly instead of taking the arccosine to avoid introducing floating-point
       inaccuracy (larger cosine means smaller angle).

       If the tile is close enough to the enemy (less than closeDistance),
       you only check if it's visible to enemy.  Make use of the is_clear_path
       helper function.  Otherwise, you must consider the direction the enemy is facing too.
       This creates a radius around the enemy that the player can be detected within, as well
       as a fov cone.
   */

   // WRITE YOUR CODE HERE
}

bool enemy_find_player(MapLayer<float>& layer, AStarAgent* enemy, Agent* player)
{
   /*
       Check if the player's current tile has a negative value, ie in the fov cone
       or within a detection radius.
   */

   const auto& playerWorldPos = player->get_position();

   const auto playerGridPos = terrain->get_grid_position(playerWorldPos);

   // verify a valid position was returned
   if (terrain->is_valid_grid_position(playerGridPos) == true)
   {
      if (layer.get_value(playerGridPos) < 0.0f)
      {
         return true;
      }
   }

   // player isn't in the detection radius or fov cone, OR somehow off the map
   return false;
}

bool enemy_seek_player(MapLayer<float>& layer, AStarAgent* enemy)
{
   /*
       Attempt to find a cell with the highest nonzero value (normalization may
       not produce exactly 1.0 due to floating point error), and then set it as
       the new target, using enemy->path_to.

       If there are multiple cells with the same highest value, then pick the
       cell closest to the enemy.

       Return whether a target cell was found.
   */

   // WRITE YOUR CODE HERE

   return false; // REPLACE THIS
}
