//
//  Entity.h
//  Assignment 6
//
//  Created by James Hong on 10/10/2022.
//

#pragma once
#include <stdio.h>
#include "Maze.h"
#include <queue>

struct bool_p_parents{
    bool seen;
    cell parents;
};

struct Nodes
{
    cell coord;  // The coordinates of a cell
    int dist;  // cell's distance of from the source
};

class Entity{
public:
    Maze *myMaze = nullptr;
    cell EntityCell;
    vector <cell> route;
    queue<Nodes> frontier;
    void setMaze(Maze &aMaze) { myMaze = &aMaze; }; //log the maze into Entity.h
    void paint(cell Start, cell End);
    void move(int direction);
    void reset();
    bool reachedGoal();
    vector<cell> findShortestPath();
};
