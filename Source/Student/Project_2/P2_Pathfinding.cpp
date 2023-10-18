#include <pch.h>
#include "P2_Pathfinding.h"
#include "Projects/ProjectTwo.h"
#include "SimpleMath.h"
#include <algorithm>

#pragma region Extra Credit
bool ProjectTwo::implemented_floyd_warshall()
{
   return false;
}

bool ProjectTwo::implemented_goal_bounding()
{
   return false;
}

bool ProjectTwo::implemented_jps_plus()
{
   return false;
}
#pragma endregion

Node::Node() : gridPos(), parent(nullptr), finalCost(0), givenCost(0), onList(List::None)
{}

// Open List Implementation //
//////////////////////////////
FastArray::FastArray() : data()
{
   last = -1;
}

void FastArray::Push(Node* node)
{
   // Overflow check
   if (last >= 3199)
      return;

   data[++last] = node;
   data[last]->onList = List::Open;
}

Node* FastArray::PopCheapest()
{
   float min_cost = FLT_MAX;
   int min_cost_idx = 0;

   for (int i = 0; i <= last; i++)
   {
      if (data[i]->finalCost < min_cost)
      {
         min_cost = data[i]->finalCost;
         min_cost_idx = i;
      }
   }

   Node* popped_node = data[min_cost_idx];
   data[min_cost_idx] = data[last];
   --last;

   return popped_node;
}

void FastArray::Clear()
{
   last = -1;
}

bool FastArray::Empty()
{
   return (last == -1);
}

// Heuristics Implementation //
///////////////////////////////

float Heuristics::Distance(GridPos start, GridPos end, Heuristic h)
{
   float xDiff = static_cast<float>(std::abs(start.row - end.row));
   float yDiff = static_cast<float>(std::abs(start.col - end.col));

   switch (h)
   {
   case Heuristic::OCTILE:
      return Octile(xDiff, yDiff);
      break;
   case Heuristic::CHEBYSHEV:
      return Chebyshev(xDiff, yDiff);
      break;
   case Heuristic::INCONSISTENT:
      return Inconsistent(start, end, xDiff, yDiff);
      break;
   case Heuristic::MANHATTAN:
      return (xDiff, yDiff);
      break;
   case Heuristic::EUCLIDEAN:
      return Euclidean(xDiff, yDiff);
      break;
   default:
      return 0;
      break;
   }
}

float Heuristics::Octile(float x_diff, float y_diff)
{
   return std::min(x_diff, y_diff) * 1.41f + std::max(x_diff, y_diff) - std::min(x_diff, y_diff);
}

float Heuristics::Chebyshev(float x_diff, float y_diff)
{
   return std::max(x_diff, y_diff);
}

float Heuristics::Inconsistent(GridPos start, GridPos end, float x_diff, float y_diff)
{
   if ((start.row + start.col) % 2 > 0)
   {
      return Euclidean(x_diff, y_diff);
   }

   return 0;
}

float Heuristics::Manhattan(float x_diff, float y_diff)
{
   return x_diff + y_diff;
}

float Heuristics::Euclidean(float x_diff, float y_diff)
{
   return std::sqrt(x_diff * x_diff + y_diff * y_diff);
}

// Post Processing Implementation //
////////////////////////////////////
void PostProcessing::Rubberbanding(Node* end_node)
{
   // Move node up the path, skipping the middle node.
   Node* start_node = end_node->parent;
   if (start_node)
      start_node = start_node->parent;
   else
      return; // We reached the end, can't do anymore.

   // Make sure to update parent pointers.

   // While we haven't reached the start of the path.
   while (start_node)
   {
      // Use the grid positions of the start and end nodes to create a square.
      // Check if any walls exist within that square.
      if (CheckForWalls(start_node, end_node))
      {
         // Eliminate the middle node.
         end_node->parent = start_node;
      }
      else
      {
         // We can't eliminate the middle node. Move both nodes up the path.
         end_node = end_node->parent;
      }

      // The start node should move up with every iteration.
      start_node = start_node->parent;
   }
}

// Returns true if no walls were found.
bool PostProcessing::CheckForWalls(Node* corner_1, Node* corner_2)
{
   int x_min = std::min(corner_1->gridPos.row, corner_2->gridPos.row);
   int x_max = std::max(corner_1->gridPos.row, corner_2->gridPos.row);

   int y_min = std::min(corner_1->gridPos.col, corner_2->gridPos.col);
   int y_max = std::max(corner_1->gridPos.col, corner_2->gridPos.col);

   for (int row = x_min; row <= x_max; row++)
   {
      for (int col = y_min; col <= y_max; col++)
      {
         if (terrain->is_wall(row, col))
            return false;
      }
   }

   return true;
}

void PostProcessing::Smoothing(Node* node, WaypointList& list)
{
   // Need to approach this with a recursive approach, starting from the actual beginning of the path.
   // (Note) Check this end condition
   if (!(node->parent->parent))
      return;

   Smoothing(node->parent, list);

   // Select the first four points. (first point is doubled up)
   Node* p1 = node->parent->parent;
   Node* p2 = p1;
   Node* p3 = node->parent;
   Node* p4 = node;

   list.push_back(terrain->get_world_position(p1->gridPos));

   // Use these to generate 3 new points.
   for (float t = 0.25f; t < 1.0f; t += 0.25f)
   {
      /*
      list.push_back(
           terrain->get_world_position(p1->gridPos) * (-0.5f*t*t*t + t*t - 0.5f*t)
         + terrain->get_world_position(p2->gridPos) * (1.5f*t*t*t + -2.5f*t*t + 1.0f)
         + terrain->get_world_position(p3->gridPos) * (-1.5f*t*t*t + 2.0f*t*t + 0.5f*5)
         + terrain->get_world_position(p4->gridPos) * (0.5f*t*t*t - 0.5f*t*t));
      */

      Vec3 p1_pos = terrain->get_world_position(p1->gridPos);
      Vec3 p2_pos = terrain->get_world_position(p2->gridPos);
      Vec3 p3_pos = terrain->get_world_position(p3->gridPos);
      Vec3 p4_pos = terrain->get_world_position(p4->gridPos);

      list.push_back(XMVectorCatmullRom(p1_pos, p2_pos, p3_pos, p4_pos, t));
   }

   // Once we reach the end, do the last end case.
}


// AStarPather Implementation //
////////////////////////////////

// Uses recursion to start at the goal node, follow the parents up until we hit the start,
// and then push the nodes in the correct order.
void TracePath(Node* node, WaypointList& list)
{
   if (!node)
      return;

   TracePath(node->parent, list);
   list.push_back(terrain->get_world_position(node->gridPos));
}

void AStarPather::ClearNodeMap()
{
   for (int row = 0; row < 40; row++)
   {
      for (int column = 0; column < 40; column++)
      {
         map[row][column].finalCost = 0.0f;
         map[row][column].givenCost = 0.0f;
         map[row][column].onList    = List::None;
         map[row][column].parent    = nullptr;
      }
   }
}

bool AStarPather::initialize()
{
   // handle any one-time setup requirements you have

   /*
       If you want to do any map-preprocessing, you'll need to listen
       for the map change message.  It'll look something like this:

       Callback cb = std::bind(&AStarPather::your_function_name, this);
       Messenger::listen_for_message(Messages::MAP_CHANGE, cb);

       There are other alternatives to using std::bind, so feel free to mix it up.
       Callback is just a typedef for std::function<void(void)>, so any std::invoke'able
       object that std::function can wrap will suffice.
   */

   // Pre-allocate all nodes. Set their positions
   for (int row = 0; row < 40; row++)
   {
      for (int column = 0; column < 40; column++)
      {
         map[row][column].gridPos.row = row;
         map[row][column].gridPos.col = column;
      }
   }

   // Initialize neighbor positional offsets.
   // N
   neighbors[0].row = -1;
   neighbors[0].col = 0;
   // NW
   neighbors[1].row = -1;
   neighbors[1].col = 1;
   // W
   neighbors[2].row = 0;
   neighbors[2].col = 1;
   // SW
   neighbors[3].row = 1;
   neighbors[3].col = 1;
   // S
   neighbors[4].row = 1;
   neighbors[4].col = 0;
   // SE
   neighbors[5].row = 1;
   neighbors[5].col = -1;
   // E
   neighbors[6].row = 0;
   neighbors[6].col = -1;
   // NE
   neighbors[7].row = -1;
   neighbors[7].col = -1;

   return true; // return false if any errors actually occur, to stop engine initialization
}

void AStarPather::shutdown()
{
   /*
       Free any dynamically allocated memory or any other general house-
       keeping you need to do during shutdown.
   */
}

PathResult AStarPather::compute_path(PathRequest& request)
{
   /*
       This is where you handle pathing requests, each request has several fields:

       start/goal - start and goal world positions
       path - where you will build the path upon completion, path should be
           start to goal, not goal to start
       heuristic - which heuristic calculation to use
       weight - the heuristic weight to be applied
       newRequest - whether this is the first request for this path, should generally
           be true, unless single step is on

       smoothing - whether to apply smoothing to the path
       rubberBanding - whether to apply rubber banding
       singleStep - whether to perform only a single A* step
       debugColoring - whether to color the grid based on the A* state:
           closed list nodes - yellow
           open list nodes - blue

           use terrain->set_color(row, col, Colors::YourColor);
           also it can be helpful to temporarily use other colors for specific states
           when you are testing your algorithms

       method - which algorithm to use: A*, Floyd-Warshall, JPS+, or goal bounding,
           will be A* generally, unless you implement extra credit features

       The return values are:
           PROCESSING - a path hasn't been found yet, should only be returned in
               single step mode until a path is found
           COMPLETE - a path to the goal was found and has been built in request.path
           IMPOSSIBLE - a path from start to goal does not exist, do not add start position to path
   */

   GridPos start = terrain->get_grid_position(request.start);
   GridPos goal = terrain->get_grid_position(request.goal);

   Node* parent_node = nullptr;
   GridPos neighbor_pos;
   Node* neighbor = nullptr;
   GridPos diagonal;

   float given_cost = 0;
   float final_cost = 0;


   if (request.settings.debugColoring)
   {
      terrain->set_color(start, Colors::Orange);
      terrain->set_color(goal, Colors::Orange);
   }

   if (request.newRequest)
   {
      // Clear open and closed lists
      ClearNodeMap();
      open_list.Clear();

      // push start node onto open list.
      open_list.Push(&map[start.row][start.col]);
   }

   while (!open_list.Empty())
   {
      parent_node = open_list.PopCheapest();

      if (parent_node->gridPos == goal)
      {
         // Post-Processing
         if(request.settings.rubberBanding)
            post_proc.Rubberbanding(parent_node);

         if (request.settings.smoothing)
            post_proc.Smoothing(parent_node, request.path);
         else 
            TracePath(parent_node, request.path); // Follow the path back and push it.

         return PathResult::COMPLETE;
      }

      parent_node->onList = List::Closed;

      if (request.settings.debugColoring)
         terrain->set_color(parent_node->gridPos, Colors::Yellow);

      // For all neighboring child nodes.
      for (int i = 0; i < 8; i++)
      {
         neighbor_pos.row = parent_node->gridPos.row + neighbors[i].row;
         neighbor_pos.col = parent_node->gridPos.col + neighbors[i].col;

         // Check if in bounds.
         if (terrain->is_valid_grid_position(neighbor_pos))
         {
            // Check if neighbor is wall
            if ((terrain->is_wall(neighbor_pos)))
            {
               continue; // Not valid neighbor node.
            }

            // Check if diagonals are walls.
            // Apply only x-offset, check if wall.
            if (neighbors[i].row != 0 && neighbors[i].col != 0)
            {
               diagonal.col = parent_node->gridPos.col + neighbors[i].col;
               diagonal.row = parent_node->gridPos.row;
               if (terrain->is_wall(diagonal))
                  continue; // Not valid neighbor node.

               // Apply only y-offset, check if wall.
               diagonal.col = parent_node->gridPos.col;
               diagonal.row = parent_node->gridPos.row + neighbors[i].row;
               if (terrain->is_wall(diagonal))
                  continue; // Not valid neighbor node.
            }

            // Compute cost of node.
            neighbor = &map[neighbor_pos.row][neighbor_pos.col];

            // Given cost is the parent node's given cost, plus the given cost from the parent to the node.
            given_cost = parent_node->givenCost;
            if (neighbors[i].row != 0 && neighbors[i].col != 0) // If diagonal.
               given_cost += 1.41f;
            else
               given_cost += 1.0f;

            // f(x) = g(x) + h(x)
            final_cost = given_cost + (heuristics.Distance(neighbor_pos, goal, request.settings.heuristic) * request.settings.weight);

            // If child is not on any list, put it on the open list.
            if ((neighbor->onList == List::None) || (final_cost < neighbor->finalCost))
            {
               neighbor->givenCost = given_cost;
               neighbor->finalCost = final_cost;
               neighbor->parent = parent_node;
               open_list.Push(neighbor);

               if(request.settings.debugColoring)
                  terrain->set_color(neighbor->gridPos, Colors::Blue);
            }
         }
      }

      if (request.settings.singleStep == true)
         return PathResult::PROCESSING;
   }
   
   return PathResult::IMPOSSIBLE;
}
