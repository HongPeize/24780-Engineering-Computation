//
//  main.cpp
//  Assignment 6
//
//  Created by James Hong on 10/10/2022.
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
    int mouseEvent, leftButton, middleButton, rightButton, locX, locY;
    ifstream myFile;
    string Name;
    Maze aMaze;
    Entity aBlock;
    aBlock.setMaze(aMaze);
    vector<cell> route;
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
    // data log into maze class

    int winWidth = aMaze.colSize * 20;
    int winHeight = aMaze.rowSize * 20; // adaptive window size
    FsOpenWindow(16, 16, winWidth, winHeight, 1, "Maze (PH 2022)");
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    cell End = aMaze.getEnd();
    cell Start = aMaze.getStart();
    aBlock.EntityCell = Start; //set block to start point
    cout << aMaze << endl;
    aMaze.menu();
    int key = FSKEY_NULL;
    while (key != FSKEY_ESC) {
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        aMaze.paint(); //show the maze
        FsPollDevice();key = FsInkey();
        mouseEvent = FsGetMouseEvent(leftButton, middleButton, rightButton, locX, locY);
        if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN){
            aMaze.changeMapState(locX, locY, mouseEvent);
            cout << aMaze << endl;
        }
        switch (key) {
            case FSKEY_DOWN:
            if (aMaze.isNavigable(aBlock.EntityCell.row+1, aBlock.EntityCell.col, aMaze.rowSize, aMaze.colSize)){
                aBlock.move(key);
            }else{cout << "Invalid Move!" << endl;}
            break;
        case FSKEY_UP:
            if (aMaze.isNavigable(aBlock.EntityCell.row-1, aBlock.EntityCell.col, aMaze.rowSize, aMaze.colSize)){
                aBlock.move(key);
            }else{cout << "Invalid Move!" << endl;}
            break;
        case FSKEY_LEFT:
            if (aMaze.isNavigable(aBlock.EntityCell.row, aBlock.EntityCell.col-1, aMaze.rowSize, aMaze.colSize)){
                aBlock.move(key);
            }else{cout << "Invalid Move!" << endl;}
            break;
        case FSKEY_RIGHT:
            if (aMaze.isNavigable(aBlock.EntityCell.row, aBlock.EntityCell.col+1, aMaze.rowSize, aMaze.colSize)){
                aBlock.move(key);
            }else{cout << "Invalid Move!" << endl;}
            break;
        case FSKEY_R:
            aBlock.reset();
            break;
        case FSKEY_S:
            aMaze.changeMapState(locX, locY, key);
            cout << aMaze << endl;
            break;
        case FSKEY_E:
            aMaze.changeMapState(locX, locY, key);
            cout << aMaze << endl;
            break;
        case FSKEY_G:
            route = aBlock.findShortestPath();
            break;
        case FSKEY_W:
            string fileName;
            cout << endl << "Enter a name of file to save >> ";
            cin >> fileName;
            fileName = fileName + ".map";
            ofstream outFile(fileName);
            outFile << aMaze;
            outFile.close();
            break;
        }
        
        End = aMaze.getEnd();
        Start = aMaze.getStart();
        aBlock.paint(Start, End); //show the block move

        if (aBlock.reachedGoal()){
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
