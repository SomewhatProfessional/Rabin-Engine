#pragma once
#include "Misc/PathfindingDetails.hpp"

enum class List
{
   None,
   Open,
   Closed,
};

class Node
{
public:
   Node();
   GridPos gridPos;
   Node* parent;
   List onList;
   float finalCost;
   float givenCost;
};

class FastArray
{
public:
   FastArray()
   {
      last = -1;
   }

   void Push(Node* node)
   {
      // Overflow check
      if (last >= 3199)
         return;

      data[++last] = node;
      data[last]->onList = List::Open;
   }

   Node* PopCheapest()
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

   void Clear()
   {
      last = -1;
   }

   bool Empty()
   {
      return (last == -1);
   }

private:
   Node* data[3200];
   int last; // The index of the last element in the array
};

class Heuristics
{
public:
   float Distance(GridPos start, GridPos end, Heuristic h);

private:
   float Octile(float x_diff, float y_diff);
   float Chebyshev(float x_diff, float y_diff);
   float Inconsistent(GridPos start, GridPos end, float x_diff, float y_diff);
   float Manhattan(float x_diff, float y_diff);
   float Euclidean(float x_diff, float y_diff);
};

class PostProcessing
{
public:
   void Rubberbanding(Node* end_node);
   bool CheckForWalls(Node* corner_1, Node* corner_2);
   void Smoothing(Node* node, WaypointList& list, GridPos goal_pos);
};

class AStarPather
{
public:
    /* 
        The class should be default constructible, so you may need to define a constructor.
        If needed, you can modify the framework where the class is constructed in the
        initialize functions of ProjectTwo and ProjectThree.
    */

    /* ************************************************** */
    // DO NOT MODIFY THESE SIGNATURES
    bool initialize();
    void shutdown();
    PathResult compute_path(PathRequest &request);
    /* ************************************************** */

    /*
        You should create whatever functions, variables, or classes you need.
        It doesn't all need to be in this header and cpp, structure it whatever way
        makes sense to you.
    */

private:
   void ClearNodeMap();
   
   FastArray open_list;
   Node map[40][40];

   GridPos neighbors[8];

   Heuristics heuristics;
   PostProcessing post_proc;
};