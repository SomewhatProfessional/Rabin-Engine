#pragma once
#include "Misc/PathfindingDetails.hpp"

enum class List
{
   Open,
   Closed,
   None,
};

class Node
{
public:
   Node();
   Node* parent;
   GridPos gridPos;
   float finalCost;
   float givenCost;
   List onList;
};

class FastArray
{
public:
   FastArray();
   ~FastArray();

   //void Push(Node node);
   void Push(Node* node);

   Node* PopCheapest();
   void Clear();
   bool Empty();

private:
   Node** data;
   int last;
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
   float CalculateGivenCost(Node* node);
   float OctileDistance(GridPos start, GridPos end);
   FastArray open_list;
   Node map[40][40];

   GridPos neighbors[8];
};