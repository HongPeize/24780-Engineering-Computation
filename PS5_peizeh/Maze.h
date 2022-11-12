//
//  Maze.h
//  Assignment 5
//
//  Created by James Hong on 1/10/2022.
//

#pragma once
using namespace std;
#include "fssimplewindow.h"
#include <vector>
#include <fstream>

struct cell{
    
    int col, row, col_last, row_last;
    
};

class Maze{
//protected:
public:
    int rowSize=0, colSize, startRow, startCol, endRow, endCol, winWidth, winHeight;
    cell Start;
    cell End;
    vector<vector<int>> map; //vector can do null size initialization
    void paint();
    void readFile(ifstream &input);
    bool isNavigable(int row, int col, int MaxRow, int MaxCol);
    cell getStart();
    cell getEnd();
    friend ostream& operator<<(ostream& os, const Maze& aMaze);
};
