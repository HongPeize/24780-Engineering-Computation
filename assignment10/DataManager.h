//
//  DataManager.h
//  assignment10
//
//  Created by James Hong on 2022-11-23.
//
//#include <stdio.h>
//#include <vector>
//#include <iostream>
//#include <fstream>
//#include "QuadraticFit.h"
//#include "Line2D.h"
//
//using namespace std;
//
//class DM{
//
//};

#pragma once

#include <vector>
#include <fstream>
#include "fssimplewindow.h"
#include "yssimplesound.h"
#include "Shape2D.h"
#include "ButtonCollection.h"
#include "QuadraticFit.h"

class DataManager : public Shape2D {
private:
    QF DataSet;
    
    bool displayFit = false;
    std::vector<Point2D> thePoints;
    bool simulationIsRunning = false;

    int winWidth = 1000, winHeight = 600;
    int panX = winWidth, panY = winHeight;
    float scale = 6.f;

    std::string fileName;
    std::ifstream inFile;
    char userChoice = 'N';
    int key = FSKEY_NULL; // just to start it up

    bool inEditMode = false;
    bool showThePoints = false;
    bool useFillMode = false;

    // for moving a vertex with the mouse
    int currVertex = -1;
    bool vertexIsMoving = false;
    int mouseEvent = 0, leftButton = 0, middleButton = 0, rightButton = 0,
        screenX = 0, screenY = 0;

    // for panning and zooming
    int prevScreenX = -1000, prevScreenY = -1000;

    // buttons
    ButtonCollection theButtons;


public:
    DataManager() {};

    DataManager(int width, int height);

    bool manage();

    // displays full menu of user options on console
    // barely needed now that we have buttons
    void showMenu();

protected:
    // resets pan and zoom so that all shapes fit on the window
    void resetView();

    // do the calculations to set values of panx, pany, and zoom
    // such that given bounding box fills the screen
    void resetView(Point2D lowerB, Point2D upperB);

    // if manager is in edit mode, this paints some indication on the graphics
    // screen that this is the case. Otherwise does nothing
    void paintEditIndicator();

    // uses current pan and zoom to convert coordinates from world to screen
    Point2D getScreenCoords(Point2D worldCoords);

    // uses current pan and zoom to convert coordinates from screen to world
    Point2D getWorldCoords(Point2D screenCoords);

    // handle mouse input (OpenGL is still in screen coords)
    void manageMouse();

    // creates the buttons to be shown on interface in a vertical column
    // called by constructor
    void addButtonsVert(GraphicFont* aFont, int xLoc, int buttonWidth);

    // manage slide boxes
    void sendUserToConsole();
    void addSlideBox();
    void removeSlideBox();
    void printAllBoxes();



};



