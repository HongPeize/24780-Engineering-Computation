// Shape2DTester.cpp : Tester main() for Shape2D and Line2D
//   by Nestor Gomez, to be updated as needed
//   

#include <iostream>
#include <fstream>
#include <vector>
#include "fssimplewindow.h"
#include "Shape2D.h"
#include "Line2D.h"

using namespace std;

void showMenu();

int main()
{
	// change these flags to test only portions of your code
	bool testLine2D = false;
	bool testShape2D = false;
	bool testGraphics = true;

	if (testLine2D) {
		Point2D testPoint1, testPoint2;
		Point2D testPoint3, testPoint4;

		// checking Line2D
		testPoint1.x = 60; testPoint1.y = 28;
		testPoint2.x = 21; testPoint2.y = 47;
 
		cout << "CHECKING LENGTHS ========================  " << endl;
		cout << "Using points, length between (" << testPoint1.x << "," << testPoint1.y << ") and ("
			<< testPoint2.x << "," << testPoint2.y << ") is "
			<< Line2D::getLength(testPoint1, testPoint2) << endl;
		cout << ">>>>>>>>>>  Should be 43.38202393" << endl << endl;

		cout << "Using coords, length between (" << testPoint1.x << "," << testPoint1.y << ") and ("
			<< testPoint2.x << "," << testPoint2.y << ") is "
			<< Line2D::getLength(testPoint1.x, testPoint1.y, testPoint2.x, testPoint2.y) << endl;
		cout << ">>>>>>>>>>  Should be 43.38202393" << endl << endl;

		testPoint3.x = 12; testPoint3.y = 31;
		testPoint4.x = 84; testPoint4.y = 35;

		cout << "Using points, length between (" << testPoint3.x << "," << testPoint3.y << ") and ("
			<< testPoint4.x << "," << testPoint4.y << ") is "
			<< Line2D::getLength(testPoint3, testPoint4) << endl;
		cout << ">>>>>>>>>>  Should be 72.11102551" << endl << endl;

		cout << "Using coords, length between (" << testPoint3.x << "," << testPoint3.y << ") and ("
			<< testPoint4.x << "," << testPoint4.y << ") is "
			<< Line2D::getLength(testPoint3.x, testPoint3.y, testPoint4.x, testPoint4.y) << endl;
		cout << ">>>>>>>>>>  Should be 72.11102551" << endl << endl;

		cout << "Intersection of two line segments ========================  " << endl;
		Point2D intersectA = Line2D::getIntersection(testPoint1, testPoint2, testPoint3, testPoint4);
		Point2D intersectB = Line2D::getIntersection(testPoint1, testPoint3, testPoint2, testPoint4);

		cout << "Segment 1-2 and segment 3-4 intersect at (" << intersectA.x << ", " << intersectA.y << ")" << endl;
		cout << ">>>>>>>>>   Should be (49.5591, 33.0866)" << endl << endl;
		cout << "Segment 1-3 and segment 2-4 intersect at (" << intersectB.x << ", " << intersectB.y << ")" << endl;
		cout << ">>>>>>>>>   Should be (150.419, 22.3488)" << endl << endl;

		cout << "Checking is between ========================  " << endl;
		if (Line2D::isBetween(testPoint1, testPoint2, intersectA))
			cout << "Found between for intersectA which is correct" << endl;
		else
			cout << "Found not between for intersectA which is WRONG" << endl;

		if (Line2D::isBetween(testPoint1, testPoint3, intersectB))
			cout << "Found between for intersectB which is WRONG" << endl;
		else
			cout << "Found not between for intersectB which is correct" << endl;

		cout << endl;
	}

	// checking Shape2D
	if (testShape2D) {
		ifstream inFile;
		inFile.open("sample01.shape");
		if (inFile.is_open()) {
			Shape2D shape01(inFile);
			Point2D testPoint1;
			inFile.close(); // don't need it anymore

			cout << "FIRST READ ===============================" << endl;
			cout << shape01 << endl;
			cout << "Perimeter: " << shape01.perimeter()
				<< "   >>>> Should be 40.6858" << endl << endl;

			// checking addPoint
			cout << "ADDING 13th as pnt (11,12) ===============================" << endl;
			testPoint1.x = 11; testPoint1.y = 12;
			shape01.addPoint(testPoint1, 13);
			cout << shape01 << endl << endl;

			cout << "ADDING 8th as coords (6.2,-.5) ===============================" << endl;
			shape01.addPoint(6.2, -.5, 8);
			cout << shape01 << endl << endl;

			cout << "ADDING 23rd as coords (2.1,10.4) and 100th as coords (1.9,5.2) ===============================" << endl;
			shape01.addPoint(2.1, 10.4, 23);
			shape01.addPoint(1.9, 5.2, 100);
			cout << shape01 << endl << endl;

			cout << "Perimeter: " << shape01.perimeter()
				<< "   >>>> Should be 44.1985" << endl << endl;

			// checking removePoint
			if (shape01.removePoint(1))
				cout << "Removed point 1" << endl;
			else
				cout << "Did not remove point 1, which is ERROR" << endl;

			if (shape01.removePoint(12))
				cout << "Removed point 12" << endl;
			else
				cout << "Did not remove point 12, which is ERROR" << endl;

			if (shape01.removePoint(21))
				cout << "Removed point 21" << endl;
			else
				cout << "Did not remove point 21, which is ERROR" << endl;
			cout << shape01 << endl << endl;

			if (shape01.removePoint(21))
				cout << "Removed point 21 again, which is ERROR" << endl;
			else
				cout << "Did not remove point 21 again" << endl;
			cout << endl << shape01 << endl << endl;

			cout << "Perimeter: " << shape01.perimeter()
				<< "   >>>> Should be 43.8647" << endl << endl;

			// checking addPoint with ratio
			shape01.addPoint(3, 0.5);
			cout << endl << shape01 << endl << endl;

		}

		else {
			cout << "Cannot open file" << endl;
		}

		inFile.open("spur01.shape");
		if (inFile.is_open()) {
			Shape2D shape01(inFile);

			inFile.close(); // don't need it anymore
			cout << "FIRST READ of SPUR ===============================" << endl;
			cout << shape01 << endl;
			cout << "Perimeter: " << shape01.perimeter()
				<< "   >>>> Should be 28.8577" << endl << endl;

		}

		inFile.open("pachiderm.shape");
		if (inFile.is_open()) {
			Shape2D shape01(inFile);

			inFile.close(); // don't need it anymore
			cout << "FIRST READ of PACHIDERM ===============================" << endl;
			cout << shape01 << endl;
			cout << "Perimeter: " << shape01.perimeter()
				<< "   >>>> Should be 958.547" << endl << endl;

		}
	}

	if (testGraphics) {
		// set up graphics window
		const int WIN_WIDTH = 800, WIN_HEIGHT = 600;
		string fileName;
		ifstream inFile;
		char userChoice;
		int panX = 0, panY = WIN_HEIGHT;
		float scale = 6.f;

		FsOpenWindow(16, 16, WIN_WIDTH, WIN_HEIGHT, 1, "Shape Graphics Tester (NG 2022)");
		
		std::vector<Shape2D> theShapes;

		// set color and width
		glColor3b(255, 0, 0);  // red
		//glLineWidth(3);

		int key = FSKEY_NULL; // just to start it up

		showMenu();

		while (key != FSKEY_ESC) {
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

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
					}
					else
						cout << "       ERROR: Was not able to open file " << fileName << endl;
				}
				showMenu(); // So that it is "fresh"
				break;
			case FSKEY_C: // clear all shapes (with confirmation)
				cout << "Are you sure you want to clear all nodes (Y/N) >> ";
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
			}

			// set up axes to "math normal" (origin at lower left, y-axis going up)
			// and pan and scale
			glLoadIdentity();
			glTranslatef(panX, panY, 0);
			glScalef(scale, -scale, 1);

			// draw all the shapes
			for (auto currShape : theShapes) {
				currShape.paint();
			}
			FsSwapBuffers();

			// prepare for next loop
			FsSleep(25);
			FsPollDevice();

			key = FsInkey();
		}

	}

	return 0;
}

void showMenu(){
	cout << "\n\n";
	cout << "Use these keys on the screen:" << endl;
	cout << " Arws : pan in all directions" << endl;
	cout << "  +/- : zoom in and out" << endl;
	cout << endl;
	cout << "    L : load shape from file" << endl;
	cout << "    C : clear all shapes" << endl;
	cout << "  ESC : exit program" << endl;
}
