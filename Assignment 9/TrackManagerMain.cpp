// TrackManagerMain.cpp : main() for Track2D program
//   by Nestor Gomez, to be updated as needed
//   PS09 due: Tues., Nov. 22, 2022
//   


#include <iostream>
#include <fstream>
#include "fssimplewindow.h"
#include "TrackManager.h"

using namespace std;

int main()
{
	// set up track manager
	TrackManager theManager(900, 600);

	theManager.showMenu();

	while (theManager.manage()) {
		// actually display graphics
		FsSwapBuffers();

		// prepare for next loop
		FsSleep(25);
	}

	return 0;
}

