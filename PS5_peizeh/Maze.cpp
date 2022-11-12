//
//  Maze.cpp
//  Assignment 5
//
//  Created by James Hong on 1/10/2022.
//

#include <stdio.h>
#include <iostream>     // std::cout, std::end
#include "Maze.h"
#include "ysglfontdata.h"
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void Maze::readFile(ifstream &input){
    string wholeLineString; // used to read file one whole line at a time
    stringstream lineStream; // used to easily get numbers from part of line
    int colonLocation; // used to store location of colon in line
    while (!input.eof()) {
        vector<int> row;
        lineStream.clear();// just in case
        getline(input, wholeLineString); // read the whole line into a string //get line from input and store into wholeLineString
        // if there is a colon, set up lineStream to start just after colon
        // also, remember colonLocation, just in case
        if ((colonLocation = wholeLineString.find(":")) != string::npos){
            lineStream.str(wholeLineString.substr(colonLocation + 1)); //store content after ":"
        }else {
            colonLocation = -1; //otherwise store whole line
            lineStream.str(wholeLineString);
        }
        // check for keywords in the line
        if (wholeLineString.find("Start:") != string::npos) // find() returns npos when not found
        {lineStream >> startRow >> startCol;} // put values into class variables
        else if (wholeLineString.find("End:") != string::npos) // find() returns npos when not found
        {lineStream >> endRow >> endCol;} // put values into class variables
        else if (wholeLineString.find("Map Begin:") != string::npos) // find() returns npos when not found
        {lineStream >> colSize;}
        else if (wholeLineString.find(":") == string::npos){ //cannot find ":" means it's map
            string tmp_string;
            int cell;
            while (!lineStream.eof()){ //whole bit map
                lineStream >> tmp_string; //read the whole line with space
                if (stringstream(tmp_string) >> cell){
                    row.push_back(cell); //extract the integer only
                }
                tmp_string = "";
            }
            if (row.size() == colSize){
                rowSize++; //wrong
            }
            map.push_back(row);
        }
    }
    startRow = startRow-1; //convert to matrix index
    startCol = startCol-1;
    endRow = endRow-1; //convert to matrix index
    endCol = endCol-1;
}

void Maze::paint(){

    int scale = 20;

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
            glVertex2d(j * scale, i * scale);
            glVertex2d(j * scale, (i + 1) * scale);
            glVertex2d((j+1) * scale, (i+1) * scale);
            glVertex2d((j + 1) * scale, i * scale);
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


//ostream& operator<<(ostream& os, const Maze& aMaze){ //overloading operator
//    for (int i = 0; i <aMaze.map.size(); i++){ //row
//        for (int j = 0; j <aMaze.map[0].size(); j++){ //col
//            os << aMaze.map[i][j];
//        }
//        cout << endl;
//    }
//    return os;
//}


ostream& operator<<(ostream& os, const Maze& aMaze) {
    
    os << "Start: " << aMaze.startRow << " " << aMaze.startCol << endl;
    os << "End: " << aMaze.startRow << " " << aMaze.startCol << endl;
    os << "Map Begin: " << aMaze.colSize << endl;
    
    for (int i = 1; i < aMaze.rowSize + 1; i++){ //col size
        for (int j = 1; j < aMaze.colSize + 1; j++){
            os << aMaze.map[i][j] << " ";
            if (j == aMaze.colSize){
                os << endl;
            }
        }
    }
    
    os << "Map End:" << endl;
    
    return os;
}
