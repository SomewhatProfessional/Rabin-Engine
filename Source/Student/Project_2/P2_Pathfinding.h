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
   GridPos gridPos;
   Node* parent;
   float finalCost;
   float givenCost;
   List onList;
};


class FastArray
{
public:
   FastArray();

   void Push(Node* node);

   Node* PopCheapest();
   void Clear();
   bool Empty();

private:
   Node* data[1600]; // Max size = 40*40
   int last; // The index of the last element in the array
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
   float OctileDistance(GridPos start, GridPos end);
   FastArray open_list;
   Node map[40][40];

   GridPos neighbors[8];
};