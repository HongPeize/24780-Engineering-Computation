// ShapeManagerMain.cpp : main() for Shape2D program
//   by Nestor Gomez, to be updated as needed
//   


#include <iostream>
#include <fstream>
#include "fssimplewindow.h"
#include "ShapeManager.h"

using namespace std;

int main()
{
	// set up shape manager
	ShapeManager theManager(800, 600);

	theManager.showMenu();

	while (theManager.manage()) {
		// move the following line to become first line of ShapeManager::manage()
		//glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		// actually display graphics
		FsSwapBuffers();

		// prepare for next loop
		FsSleep(25);
	}

	return 0;
}

