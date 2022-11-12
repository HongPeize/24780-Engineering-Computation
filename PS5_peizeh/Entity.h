//
//  Entity.h
//  Assignment 5
//
//  Created by James Hong on 4/10/2022.
//

#pragma once
#include <stdio.h>
#include "Maze.h"


class Entity{
public:
    cell EntityCell;

//public:
    void paint(cell Start, cell End);
    void move(Maze &aMaze, int direction);
    void reset(Maze &aMaze);
    bool reachedGoal(cell End);
};
