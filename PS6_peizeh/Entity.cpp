//
//  Entity.cpp
//  Assignment 6
//
//  Created by James Hong on 10/10/2022.
//
#include <iostream>
#include "Entity.h"
#include "Maze.h"
#include "fssimplewindow.h"
#include <fstream>
using namespace std;


void Entity::move(int direction){
    EntityCell.col_last = EntityCell.col;
    EntityCell.row_last = EntityCell.row;
    if (direction == FSKEY_DOWN){
        EntityCell.row++;
        cout << "Row: " << EntityCell.row << " Col: " << EntityCell.col << endl;

    }else if(direction == FSKEY_UP){
        EntityCell.row--;
        cout << "Row: " << EntityCell.row << " Col: " << EntityCell.col << endl;

    }else if(direction == FSKEY_LEFT){
        EntityCell.col--;
        cout << "Row: " << EntityCell.row << " Col: " << EntityCell.col << endl;

    }else if(direction == FSKEY_RIGHT){
        EntityCell.col++;
        cout << "Row: " << EntityCell.row << " Col: " << EntityCell.col << endl;
    }
}
        
bool Entity::reachedGoal(){
    if (EntityCell.row == myMaze->endRow && EntityCell.col == myMaze->endCol){
        return true;
    }else{return false;}
}

void Entity::paint(cell Start, cell End){
    if (EntityCell.row_last == Start.row && EntityCell.col_last == Start.col){
        glColor3ub(127, 255, 0);
    }else if (EntityCell.row_last == End.row && EntityCell.col_last == End.col){
        glColor3ub(255, 0, 0);
    }else if (myMaze->map[EntityCell.row_last][EntityCell.col_last]!=1){
        glColor3ub(255, 255, 255);
    }else{
        glColor3ub(0, 0, 0);
    }
    
    glBegin(GL_QUADS);
    glVertex2d(EntityCell.col_last * SCALE, EntityCell.row_last * SCALE);
    glVertex2d(EntityCell.col_last * SCALE, (EntityCell.row_last + 1) * SCALE);
    glVertex2d((EntityCell.col_last+1) * SCALE, (EntityCell.row_last + 1) * SCALE);
    glVertex2d((EntityCell.col_last + 1) * SCALE, EntityCell.row_last * SCALE);
    glEnd();
    
    if (!route.empty()){
        for (int i = (int)route.size()-1; i >= 0 ; i--){
            glColor3ub(0, 0, 255);
            glPointSize(5.0f);
            glBegin(GL_POINTS); //starts drawing of points
            glVertex3i(route[i].col * SCALE + 10, route[i].row * SCALE + 10, 0);//upper-right corner
            glEnd();
        }
    }
    glColor3ub(255, 255, 0);
    glBegin(GL_QUADS);
    glVertex2d(EntityCell.col * SCALE, EntityCell.row * SCALE);
    glVertex2d(EntityCell.col * SCALE, (EntityCell.row + 1) * SCALE);
    glVertex2d((EntityCell.col+1) * SCALE, (EntityCell.row+1) * SCALE);
    glVertex2d((EntityCell.col + 1) * SCALE, EntityCell.row * SCALE);
    glEnd();
}

void Entity::reset(){
    glColor3ub(255, 255, 255);
    glBegin(GL_QUADS);
    glVertex2d(EntityCell.col * SCALE, EntityCell.row * SCALE);
    glVertex2d(EntityCell.col * SCALE, (EntityCell.row + 1) * SCALE);
    glVertex2d((EntityCell.col+1) * SCALE, (EntityCell.row+1) * SCALE);
    glVertex2d((EntityCell.col + 1) * SCALE, EntityCell.row * SCALE);
    glEnd();
    EntityCell.row = myMaze->startRow;
    EntityCell.col = myMaze->startCol;
    route.clear();
}

vector<cell> Entity::findShortestPath(){
    route = {};
    int rowAdjust[] = { -1, 0, 1, 0 };
    int colAdjust[] = { 0, 1, 0, -1 };
    cell Start_node = EntityCell; //start from current location
    cell End_node; //define end node
    End_node.col = myMaze->endCol;
    End_node.row = myMaze->endRow;
 
    if (myMaze->map[Start_node.row][Start_node.col] == 1 || myMaze->map[End_node.row][End_node.col] == 1){
        cout << "No route found!" << endl;
        return {};
    }
    bool_p_parents visited[myMaze->rowSize][myMaze->colSize];
    for (int i=0; i<myMaze->rowSize; i++){
        for (int j=0; j<myMaze->colSize; j++){
            visited[i][j] = {false, {-1,-1}};
        }
    }
    // Mark the start cell as visited
    visited[Start_node.row][Start_node.col].seen = true; // seen, parents
    
    // Create a queue for BFS
    queue<Nodes> frontier;
    
    // Distance of start cell is 0
    Nodes s = {Start_node, 0}; //node coord, curr dist
    frontier.push(s);  // Enqueue BFS root cell
    
    // Do a BFS starting from source cell
    while (!frontier.empty())
    {
        Nodes curr = frontier.front();
        cell coord = curr.coord;

        // If we have reached the destination cell, we are done
        if (coord.row == End_node.row && coord.col == End_node.col){
            cout << "Route:" << endl;
            while (coord.row != Start_node.row || coord.col != Start_node.col){
                coord = visited[coord.row][coord.col].parents;
                route.push_back(coord);
                cout << coord.row << " " << coord.col << endl;
            }
            route.pop_back();
            return route;
        }
        // Otherwise dequeue the front cell in the queue and enqueue its adjacent cells
        frontier.pop();
        for (int i = 0; i < 4; i++) //loop cw dir
        {
            int row = coord.row + rowAdjust[i];
            int col = coord.col + colAdjust[i];

            // if adjacent cell is valid, has path and not visited yet, enqueue it.
            if ((myMaze->isNavigable(row, col, myMaze->rowSize, myMaze->colSize)) && (visited[row][col].seen == false)){
                // mark cell as visited and enqueue it
                visited[row][col].seen = true;
                visited[row][col].parents = coord;
                Nodes Adjcell = { {row, col}, curr.dist + 1 };
                frontier.push(Adjcell);
            }
        }
    }
    // Return -1 if destination cannot be reached
    cout << "No route found!" << endl;
    return {};
}
