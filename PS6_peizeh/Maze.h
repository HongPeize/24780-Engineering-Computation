//
//  Maze.h
//  Assignment 6
//
//  Created by James Hong on 10/10/2022.
//

#pragma once
using namespace std;
#include "fssimplewindow.h"
#include <vector>
#include <fstream>
#define SCALE 20

struct cell{
    
    int row = 0, col = 0, row_last = 0, col_last = 0;
    
};

class Maze{
public:
    int rowSize=0, colSize, startRow, startCol, endRow, endCol, winWidth, winHeight;
    cell Start;
    cell End;
    int map[100][100];
    void paint();
    void readFile(ifstream &input);
    bool isNavigable(int row, int col, int MaxRow, int MaxCol);
    void menu();
    cell getStart();
    cell getEnd();
    // mouseX and mouseY are the pixel coordinates of a left click
    // key is either FSMOUSEEVENT_LBUTTONDOWN, FSKEY_S, or FSKEY_E
    // mouse click toggles obstacle state of cell/block below mouse location
    // unless block is start or end (start and end MUST be navigable
    // if block is navigable, S and E will set it to either start or end
    // note, start or end may become undefined (-1, -1)
    void changeMapState(int mouseX, int mouseY, int key);
    friend ostream& operator<<(ostream& os, const Maze& aMaze);
};
