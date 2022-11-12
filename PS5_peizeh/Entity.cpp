//
//  Entity.cpp
//  Assignment 5
//
//  Created by James Hong on 4/10/2022.
//
#include <iostream>
#include "Entity.h"
#include "Maze.h"
#include "fssimplewindow.h"
#include <fstream>
using namespace std;


void Entity::move(Maze &aMaze, int direction){
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
        
bool Entity::reachedGoal(cell End){
    if (EntityCell.row == End.row && EntityCell.col == End.col){
        return true;
    }else{return false;}
}

void Entity::paint(cell Start, cell End){
    int scale = 20;
    if (EntityCell.row_last == Start.row && EntityCell.col_last == Start.col){
        glColor3ub(127, 255, 0);
    }else if (EntityCell.row_last == End.row && EntityCell.col_last == End.col){
        glColor3ub(255, 0, 0);
    }else{
        glColor3ub(255, 255, 255);
    }//paint visited to white
    
    glBegin(GL_QUADS);
    glVertex2d(EntityCell.col_last * scale, EntityCell.row_last * scale);
    glVertex2d(EntityCell.col_last * scale, (EntityCell.row_last + 1) * scale);
    glVertex2d((EntityCell.col_last+1) * scale, (EntityCell.row_last + 1) * scale);
    glVertex2d((EntityCell.col_last + 1) * scale, EntityCell.row_last * scale);
    glEnd();
    
    glColor3ub(255, 255, 0);
    glBegin(GL_QUADS);
    glVertex2d(EntityCell.col * scale, EntityCell.row * scale);
    glVertex2d(EntityCell.col * scale, (EntityCell.row + 1) * scale);
    glVertex2d((EntityCell.col+1) * scale, (EntityCell.row+1) * scale);
    glVertex2d((EntityCell.col + 1) * scale, EntityCell.row * scale);
    glEnd();
}

void Entity::reset(Maze &aMaze){
    int scale = 20;
    glColor3ub(255, 255, 255);
    glBegin(GL_QUADS);
    glVertex2d(EntityCell.col * scale, EntityCell.row * scale);
    glVertex2d(EntityCell.col * scale, (EntityCell.row + 1) * scale);
    glVertex2d((EntityCell.col+1) * scale, (EntityCell.row+1) * scale);
    glVertex2d((EntityCell.col + 1) * scale, EntityCell.row * scale);
    glEnd();
    EntityCell.row = aMaze.startRow;
    EntityCell.col = aMaze.startCol;
    //return true;
}



