#include <iostream>
#include <fstream>
#include <sstream>
#include "ShapeManager.h"
#include "ysglfontdata.h"

using namespace std;

ShapeManager::ShapeManager(int width, int height)
{
	// for testing, just load 3 shapes (comment out when done)
	ifstream inFile;
	inFile.open("spur01.shape");
	theShapes.push_back(Shape2D(inFile));
	inFile.close();
	inFile.open("sample01.shape");
	theShapes.push_back(Shape2D(inFile));
	inFile.close();
	inFile.open("rectangle01.shape");
	theShapes.push_back(Shape2D(inFile));
	inFile.close();
	resetView();

	winWidth = width;
	winHeight = height;
	FsOpenWindow(16, 16, winWidth, winHeight, 1, "Shape Manager (NG 2022)");

	// set color and width
	glColor3b(255, 0, 0);  // red
	//glLineWidth(3);

}

bool ShapeManager::manage()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	// reset all transformations
	glLoadIdentity();

	FsPollDevice();
	key = FsInkey();

	switch (key) {
	case FSKEY_L: // load a file and add to shapes
		cout << endl << "   Enter a name of shape file to load > ";
		cin >> fileName;
		if (fileName.length() > 0) {
			if (fileName.find(".shape") == string::npos)
				fileName += ".shape";

			inFile.open(fileName);
			if (inFile.is_open()) {
				theShapes.push_back(Shape2D(inFile));
				inFile.close();
				cout << "       A new shape was added from file " << fileName << endl;
				cout << "       There are now " << theShapes.size() << " shapes." << endl;

				// change zoom to show newly added shape
				resetView(theShapes.back().getLowerBound(),
					theShapes.back().getUpperBound());
			}
			else
				cout << "       ERROR: Was not able to open file " << fileName << endl;
		}
		showMenu(); // So that it is "fresh"
		break;
	case FSKEY_C: // clear all shapes (with confirmation)
		cout << "Are you sure you want to clear all shapes (Y/N) >> ";
		cin >> userChoice;
		if (userChoice == 'Y' || userChoice == 'y') {
			theShapes.clear(); // empties all members of a vector (kills memory too)
		}
		showMenu(); // So that it is "fresh"
		break;
	case FSKEY_RIGHT: panX += 5;
		break;
	case FSKEY_LEFT: panX -= 5;
		break;
	case FSKEY_UP: panY -= 5;
		break;
	case FSKEY_DOWN: panY += 5;
		break;
	case FSKEY_PLUS: scale *= 1.05;
		break;
	case FSKEY_MINUS: scale /= 1.05;
		break;

		// new stuff for PS04
	case FSKEY_R:   // reset Zoom to fit all shapes
		resetView();
		break;
	case FSKEY_E:
		if (!inEditMode && theShapes.size() == 0)
			cout << "Nothing to Edit." << endl;
		else {
			inEditMode = !inEditMode;
			if (inEditMode && currShape < 0) // take care of first entry into edit mode
				currShape = 0;
		}
	}

	if (inEditMode) {  // also for PS04.
		// show user that we are in edit mode
		paintEditIndicator();

		switch (key) {
		case FSKEY_S: // save current shape (similar to load shape above)
			cout << "Filename for saving current shape >> ";
			cin >> fileName;

			if (fileName.find(".shape") == string::npos)
				fileName += ".shape";

			outFile.open(fileName);
			if (outFile.is_open()) {
				outFile << theShapes.at(currShape);
				outFile.close();
				cout << "Just saved " << fileName << " to current folder." << endl;
			}
			else {
				cout << "Cannot open file " << fileName << " for output." << endl;
			}
			showMenu();
			break;
		case FSKEY_COMMA:   // also the '<' key, change currShape
			if (theShapes.size() > 0) {  // too careful perhaps
				currShape--;
				if (currShape < 0)
					currShape = theShapes.size() - 1;
			}
			break;
		case FSKEY_DOT:   // also the '>' key, change currShape
			if (theShapes.size() > 0) {
				currShape++;
				if (currShape >= theShapes.size())
					currShape = 0;
			}
			break;
		case FSKEY_P:  // toggle showing points for current shape
			showThePoints = !showThePoints;
		case FSKEY_H:
			if (0 <= currShape && currShape < theShapes.size())
				theShapes.at(currShape).changeColor(10.f);
			break;
		case FSKEY_Z:  // zoom onto current shape
			if (0 <= currShape && currShape < theShapes.size())
				resetView(theShapes.at(currShape).getLowerBound(),
					theShapes.at(currShape).getUpperBound());
			break;
		}
	}

	// handle mouse input (OpenGL is still in screen coords)
	manageMouse();

	// set up axes to "math normal" (y-axis going up) and pan and scale
	glTranslatef(panX, panY, 0);  
	glScalef(scale, -scale, 1);

	// draw all the shapes, carefully setting parameters
	int i = 0;
	for (auto& aShape : theShapes) {
		if (inEditMode) {
			if (currShape == i)
				aShape.paint(true, false, showThePoints); // show the points maybe
			else
				aShape.paint(true, false, false, 60); // yellow
		}
		else
			aShape.paint(true, false, false); // use shape-maintained colors
		i++;
	}

	return key != FSKEY_ESC;
}

void ShapeManager::showMenu()
{
	// Some of these options need to be programmed by you for PS04

	cout << "\n\n";
	cout << "Use these keys on the screen:" << endl;
	cout << " Arws : pan in all directions (also Ctrl+Drag)" << endl;
	cout << "  +/- : zoom in and out (also Shft+Drag)" << endl;
	cout << "    R : Reset the view so all shapes fit" << endl;		// PS04

	cout << endl;
	cout << "    L : Load shape from file" << endl;
	cout << "    C : Clear all shapes" << endl;
	cout << endl;

	cout << "    E : toggle Edit mode" << endl;								// PS04
	cout << "  \< \> : cycle through shapes to select current shape" << endl;	// PS04 (use FSKEY_COMMA and FSKEY_DOT)
	cout << "    P : toggle showing of Points" << endl;						// PS04
	cout << "    H : change Hue angle of shape by +10 deg" << endl;			// PS04
	cout << "    Z : Zoom into just the current shape" << endl;			// PS04
	cout << "    S : Save the current shape" << endl;			// PS04
	cout << endl;

	cout << "  ESC : exit program" << endl;
}

void ShapeManager::resetView()
{
	if (theShapes.size() > 0) {
		Point2D currLow, currUpper;
		Point2D overallLow = theShapes[0].getLowerBound();
		Point2D overallUpper = theShapes[0].getUpperBound();

		for (auto& aShape : theShapes) {
			currLow = aShape.getLowerBound();
			currUpper = aShape.getUpperBound();
			overallLow.x = min(overallLow.x, currLow.x);
			overallLow.y = min(overallLow.y, currLow.y);
			overallUpper.x = max(overallUpper.x, currUpper.x);
			overallUpper.y = max(overallUpper.y, currUpper.y);
		}
		resetView(overallLow, overallUpper);
	}
}

void ShapeManager::resetView(Point2D lowerB, Point2D upperB)
{
	int extraBorder = 24; // allows for some space around all shape(s)

	// Determine needed scale to completely fill in the screen.
	// We do it for each direction and then choose smallest as overall 
	// new scale, leaving blank space for other direction 

	float horzScale = (winWidth - extraBorder) / (upperB.x - lowerB.x);
	float vertScale = (winHeight - extraBorder) / (upperB.y - lowerB.y);
	scale = min(horzScale, vertScale);

	// To adjust panX and panY, we need to put center of all shapes
	// at the center of screen. Thus, we first pan to center of screen
	// and then pan from center of shapes (average of shape bounds)
	// to world 0,0  , converted to pixels. Note minus for x (moving left)
	// and plus for y (moving down) since we are using pixel dimensions

	panX = winWidth / 2. - (upperB.x + lowerB.x) / 2. * scale;
	panY = winHeight / 2. + (upperB.y + lowerB.y) / 2. * scale;
}

void ShapeManager::paintEditIndicator()
{
	bool useAwful = false;

	if (!useAwful) {
		// draw yellow square all around, with the word "EDIT" at top right and
		// bottom left corners

		// box around (big yellow rectangle with slightly smaller white rectangle)
		glColor3ub(255, 255, 0); // yellow
		glBegin(GL_QUADS);
		glVertex2i(0, 0);
		glVertex2i(winWidth, 0);
		glVertex2i(winWidth, winHeight);
		glVertex2i(0, winHeight);
		glEnd();

		glColor3ub(255, 255, 255); // white
		int frameThickness = 5;
		glBegin(GL_QUADS);
		glVertex2i(frameThickness, frameThickness);
		glVertex2i(winWidth - frameThickness - 1, frameThickness);
		glVertex2i(winWidth - frameThickness - 1, winHeight - frameThickness - 1);
		glVertex2i(frameThickness, winHeight - frameThickness - 1);
		glEnd();

		// little boxes for EDIT label
		glColor3ub(255, 255, 0); // yellow
		int boxW = 40, boxH = 18;
		glBegin(GL_QUADS);
		glVertex2i(winWidth - boxW, 0);
		glVertex2i(winWidth, 0);
		glVertex2i(winWidth, boxH);
		glVertex2i(winWidth - boxW, boxH);
		glEnd();

		glBegin(GL_QUADS);
		glVertex2i(0, winHeight - boxH);
		glVertex2i(boxW, winHeight - boxH);
		glVertex2i(boxW, winHeight);
		glVertex2i(0, winHeight);
		glEnd();

		// label "EDIT"
		glColor3ub(0, 0, 0); // black
		glRasterPos2i(winWidth - boxW + 3, boxH - 3);  // top right
		YsGlDrawFontBitmap8x12("EDIT");
		glRasterPos2i(3, winHeight - 3);  // bottom left
		YsGlDrawFontBitmap8x12("EDIT");
	}
	else {
		// awful edit indicator, but simple to code :-)
		glColor3ub(0, 0, 0); // black
		glRasterPos2i(0, 30);  // top right
		YsGlDrawFontBitmap20x28("YOU ARE NOW IN EDIT MODE");
	}
}

Point2D ShapeManager::getScreenCoords(Point2D worldCoords)
{
	float screenX = worldCoords.x * scale + panX;
	float screenY = worldCoords.y * -scale + panY;
	return { screenX, screenY };
}

Point2D ShapeManager::getWorldCoords(Point2D screenCoords)
{
	float worldX = (screenCoords.x - panX) / scale;
	float worldY = (screenCoords.y - panY) / -scale;
	return { worldX, worldY };
}

void ShapeManager::manageMouse()
{
	// handle mouse input (OpenGL is still in screen coords)
	int mouseEvent, leftButton, middleButton, rightButton;
	int screenX, screenY;
	stringstream coordStream;     // for displaying coordinates on screen

	mouseEvent = FsGetMouseEvent(leftButton, middleButton,
		rightButton, screenX, screenY);

	Point2D worldPnt = getWorldCoords({ screenX * 1.f, screenY * 1.f });

	if (leftButton) { // write coords on screen if left button is held down
		coordStream.str("");  // reset stream
		coordStream.precision(4);
		coordStream << worldPnt.x << ", " << worldPnt.y
			<< " (" << screenX << ", " << screenY << ")";
		glColor3ub(60, 230, 60);
		glRasterPos2i(screenX, screenY - 3);  // set position 3 pix above
		YsGlDrawFontBitmap7x10(coordStream.str().c_str());
	}

	if (inEditMode) {
		float hoverDistance = 3.f / scale; // 3 pixels

		// figure out if there's a point near mouse location
		int currVertex = theShapes.at(currShape).getIndex(worldPnt, hoverDistance);
		//if (currVertex > 0)
		//	cout << "Hovered over Pnt " << currVertex << endl;
	}
}

