//
//  Maze.cpp
//  Assignment 6
//
//  Created by James Hong on 10/10/2022.
//

#include <stdio.h>
#include <iostream>     // std::cout, std::end
#include "Maze.h"
#include "ysglfontdata.h"
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void Maze::readFile(ifstream &input)
{
    string wholeLineString; // used to read file one whole line at a time
    stringstream lineStream; // used to easily get numbers from part of line
    int colonLocation; // used to store location of colon in line

    while (!input.eof()) {
        lineStream.clear();// just in case

        getline(input, wholeLineString); // read the whole line into a string

        // if there is a colon, set up lineStream to start just after colon
        // also, remember colonLocation, just in case
        if ((colonLocation = wholeLineString.find(":")) != string::npos)
            lineStream.str(wholeLineString.substr(colonLocation + 1));
        else {
            colonLocation = -1;
            lineStream.str(wholeLineString);
        }

        // check for keywords in the line
        if (wholeLineString.find("Start:") != string::npos) // find() returns npos when not found
            lineStream >> startRow >> startCol; // put values into class variables

        else if (wholeLineString.find("End:") != string::npos) // find() returns npos when not found
            lineStream >> endRow >> endCol; // put values into class variables

        else if (wholeLineString.find("Begin:") != string::npos) {
            lineStream >> colSize;
            bool continueReadingMap = true;
            rowSize = 0;
            while (continueReadingMap && !input.eof()) { // note extra protection for end-of-file
                getline(input, wholeLineString); // read the whole line into a string
                if (wholeLineString.find("End:") != string::npos)
                    continueReadingMap = false;
                else {
                    // convert string into a stringstream and read whole thing into the map
                    lineStream.clear();// just in case
                    lineStream.str(wholeLineString);
                    
                    // read each 0 or 1 on the line directly into map array
                    for (int j = 0; j < colSize; j++)  // using j due to tradition of j as column index
                        lineStream >> map[rowSize][j];
                    rowSize++;
                    // alternatively, we could read without knowing the column size, but it can
                    // give bad results if there is extra stuff after the zeroes and ones
                    //colSize = 0;
                    //while (!lineStream.eof())
                    //    lineStream >> map[rowSize][++colSize];

                }
            }
        }
    }
    startRow = startRow-1; //convert to matrix index
    startCol = startCol-1;
    endRow = endRow-1; //convert to matrix index
    endCol = endCol-1;
}

void Maze::paint(){

    for (int i= 0; i < rowSize; i++){ //row size
        for (int j = 0; j < colSize; j++){ //col size
            if (map[i][j] == 1){
                glColor3ub(0, 0, 0);
            }else if (i == startRow && j == startCol){
                glColor3ub(127,255,0);
            }else if (i == endRow && j == endCol){
                glColor3ub(255, 0, 0);
            }else{
                glColor3ub(255, 255, 255);
            }
            glBegin(GL_QUADS);
            glVertex2d(j * SCALE, i * SCALE);
            glVertex2d(j * SCALE, (i + 1) * SCALE);
            glVertex2d((j+1) * SCALE, (i+1) * SCALE);
            glVertex2d((j + 1) * SCALE, i * SCALE);
            glEnd();
        }
    }
}

bool Maze::isNavigable(int row, int col, int MaxRow, int MaxCol){
    if ((0 <= row && row < MaxRow) && (0 <= col && col < MaxCol)){
        if (map[row][col] != 1){
            return true;
        }
        return false;
    }else{return false;}
}

cell Maze::getStart(){
    Start.col = startCol;
    Start.row = startRow;
    return Start;
}

cell Maze::getEnd(){
    End.col = endCol;
    End.row = endRow;
    return End;
}

void Maze:: changeMapState(int mouseX, int mouseY, int key){
    int selectedRow = mouseY/SCALE;
    int selectedCol = mouseX/SCALE;
    if (0 <= selectedRow && selectedRow < rowSize && 0<=selectedCol && selectedCol < colSize){
        if (key == FSMOUSEEVENT_LBUTTONDOWN){
            if (selectedRow != startRow || selectedCol != startCol){
                if (selectedRow != endRow || selectedCol != endCol){
                    map[selectedRow][selectedCol] = !map[selectedRow][selectedCol];
                }
            }
            //cout << selectedRow << " " << selectedCol << endl;
        }
        else if (key == FSKEY_S && !map[selectedRow][selectedCol]){
            startCol = selectedCol; startRow = selectedRow;
        }
        else if (key == FSKEY_E && !map[selectedRow][selectedCol]){
            endCol = selectedCol; endRow = selectedRow;
        }
    }
}

void Maze:: menu(){
    cout << "Menu" << endl;
    cout << "Up -> move up" << endl;
    cout << "Down -> move down" << endl;
    cout << "Left -> move left" << endl;
    cout << "Right -> move right" << endl;
    cout << "W -> save map" << endl;
    cout << "R -> reset maze" << endl;
    cout << "S -> set start position" << endl;
    cout << "E -> set end position" << endl;
    cout << "G -> find shortest ppath" << endl;
    cout << "Left mouse button -> empty/obstacle" << endl;
}

ostream& operator<<(ostream& os, const Maze& aMaze) {
    
    os << "Start: " << aMaze.startRow+1 << " " << aMaze.startCol+1 << endl;
    os << "End: " << aMaze.endRow+1 << " " << aMaze.endCol+1 << endl;
    os << "Map Begin: " << aMaze.colSize << endl;
    
    for (int i = 0; i < aMaze.rowSize; i++){ //col size
        for (int j = 0; j < aMaze.colSize; j++){
            os << aMaze.map[i][j] << " ";
            if (j == aMaze.colSize-1){
                os << endl;
            }
        }
    }
    
    os << "Map End:" << endl;
    
    return os;
}
