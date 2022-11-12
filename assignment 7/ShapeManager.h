#pragma once

#include <vector>
#include <fstream>

#include "fssimplewindow.h"
#include "yssimplesound.h"
#include "Shape2D.h"

class ShapeManager {
private: 
	std::vector<Shape2D> theShapes;
	int currShape = -1;

	int winWidth = 800, winHeight = 600;
	int panX = 0, panY = winHeight;
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

	// for panning and zooming
	int prevScreenX = -1000, prevScreenY = -1000;

	// audio feedback on inside/outside check
	YsSoundPlayer theSoundPlayer;
	YsSoundPlayer::SoundData insideSound;
	YsSoundPlayer::SoundData outsideSound;

public:
	ShapeManager() {};

	ShapeManager(int width, int height);


	bool manage();

	// displays full menu of user options on console
	void showMenu();

private:
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
};