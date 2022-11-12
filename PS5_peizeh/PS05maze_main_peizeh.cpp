//
//  main.cpp
//  Assignment 5
//
//  Created by James Hong on 1/10/2022.
//
#include "ysglfontdata.h"
#include <stdio.h>
#include <iostream>
#include "Maze.h"
#include "fssimplewindow.h"
#include <string>
#include <sstream>
#include <fstream>
#include "Entity.h"
using namespace std;


int main(){
    ifstream myFile;
    string Name;
    Maze aMaze;
    Entity aBlock;
    while (!myFile.is_open()){
        cout << "Name of File: ";
        cin >> Name;

        //read file, get startrow, startcol, endrow, endcol
        if (Name == "mazeA"){
            myFile.open("mazeA_10x10.map");
            if (!myFile.is_open()){
                cout << "Error opening the file" << endl;
            }else{
                aMaze.readFile(myFile);
            }
        }else if (Name == "mazeB"){
            myFile.open("mazeB_25x25.map");
            if (!myFile.is_open()){
                cout << "Error opening the file" << endl;
            }else{
                aMaze.readFile(myFile);
            }
        }else if (Name == "mazeC"){
            myFile.open("mazeC_40x20.map");
            if (!myFile.is_open()){
                cout << "Error opening the file" << endl;
            }else{
                aMaze.readFile(myFile);
            }
        }else{
            cout << "File not found!" << endl;
        }
    }
//    cout << aMaze.map.size() << endl;
//    cout << aMaze.map[0].size() << endl;
    //cout << aMaze << endl;
    // data log into maze class

    int winWidth = aMaze.colSize * 20;
    int winHeight = aMaze.rowSize * 20; // adaptive window size
    FsOpenWindow(16, 16, winWidth, winHeight, 1, "Maze (PH 2022)");
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    cell End = aMaze.getEnd();
    cell Start = aMaze.getStart();
    aBlock.EntityCell = Start; //set block to start point
    
    int key = FSKEY_NULL;
    while (key != FSKEY_ESC) {
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        aMaze.paint(); //show the maze
        FsPollDevice();key = FsInkey();
        switch (key) {
            case FSKEY_DOWN:
            if (aMaze.isNavigable(aBlock.EntityCell.row+1, aBlock.EntityCell.col, aMaze.rowSize, aMaze.colSize)){
                aBlock.move(aMaze, key);
            }else{cout << "Invalid Move!" << endl;}
            break;
        case FSKEY_UP:
            if (aMaze.isNavigable(aBlock.EntityCell.row-1, aBlock.EntityCell.col, aMaze.rowSize, aMaze.colSize)){
                aBlock.move(aMaze, key);
            }else{cout << "Invalid Move!" << endl;}
            break;
        case FSKEY_LEFT:
            if (aMaze.isNavigable(aBlock.EntityCell.row, aBlock.EntityCell.col-1, aMaze.rowSize, aMaze.colSize)){
                aBlock.move(aMaze, key);
            }else{cout << "Invalid Move!" << endl;}
            break;
        case FSKEY_RIGHT:
            if (aMaze.isNavigable(aBlock.EntityCell.row, aBlock.EntityCell.col+1, aMaze.rowSize, aMaze.colSize)){
                aBlock.move(aMaze, key);
            }else{cout << "Invalid Move!" << endl;}
            break;
        case FSKEY_R:
                aBlock.reset(aMaze);
            break;
        }

        aBlock.paint(Start, End); //show the block move

        if (aBlock.reachedGoal(End)){
            cout << "You Win" << endl;
            glColor3ub(127, 255, 0);
            glRasterPos2i(winWidth*0.35, winHeight*0.5);  // sets position
            YsGlDrawFontBitmap20x32("You win");
        }
        FsSwapBuffers();
        FsSleep(15);
    }

    return 0;
}
