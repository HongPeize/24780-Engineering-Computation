#include <iostream>
#include <fstream>
#include <sstream>
#include "DrawingUtilNG.h"
#include "GraphicFont.h"
#include "StringPlus.h"
#include "ysglfontdata.h"
#include "yssimplesound.h"
#include "TrackManager.h"

using namespace std;

TrackManager::TrackManager(int width, int height)
{
	// for testing, just load a track (comment out when done)
	//ifstream inFile("loop2.track");
	//theTrack.readFile(inFile);
	//inFile.close();

	winWidth = width;
	winHeight = height;

	FsOpenWindow(16, 16, winWidth, winHeight, 1, "Track Manager (NG 2022)");

	// set color and width
	glColor3b(255, 0, 0);  // red
	//glLineWidth(3);

		// load sounds and start player
	//if (YSOK != insideSound.LoadWav("cash_register.wav"))
	//	cout << "   ERROR: Unable to load cash_register.wav " << endl;
	//if (YSOK != outsideSound.LoadWav("buzzer.wav"))
	//	cout << "   ERROR: Unable to load cash_register.wav " << endl;
	//theSoundPlayer.Start();

	ButtonCollection* myButtons = new ButtonCollection; // put this AFTER FsOpenWindow()
	GraphicFont* buttonFont = new ComicSansFont;
	buttonFont->setColorRGB(0, 0, 0); // black

	addButtonsVert(buttonFont, winWidth - 108, 100);

	resetView();
}

void TrackManager::showMenu()
{
	cout << "\n\n";
	cout << "Use these keys on the screen:" << endl;
	cout << " Arws : pan in all directions (also Ctrl+LeftButtonDrag)" << endl;
	cout << "  +/- : zoom in and out (also Shft+LeftButtonDrag)" << endl;
	cout << "    Z : Zoom the view so whole track fits" << endl;		// PS04
	//cout << "    F : show all shapes Filled" << endl;		// Extra
	cout << "    H : change Hue angle of shape by +10 deg" << endl;			// PS04
	cout << endl;

	cout << "    L : Load track from file" << endl;
	cout << "    S : Save the track" << endl;			// PS04
	cout << "    E : toggle Edit mode" << endl;								// PS04
	cout << "      Left Mouse : move points" << endl;
	cout << "      D : Delete higlighted point" << endl;
	cout << "      A : Add a point just back of higlighted point" << endl;			// PS04
	cout << endl;

	cout << "    B : add Box to model" << endl;
	cout << "    R : Remove box from model" << endl;
	cout << "    I : set model to Initial condition" << endl;

	cout << "SPACE : start/pause simulation" << endl;

	cout << "  ESC : exit program" << endl;
}

void TrackManager::resetView()
{
	if (theTrack.getLowerBound().x == -INFINITY)
		resetView({ 0, 0 }, { 20,20 });
	else
		resetView(theTrack.getLowerBound(), theTrack.getUpperBound());
}

void TrackManager::resetView(Point2D lowerB, Point2D upperB)
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

void TrackManager::paintEditIndicator()
{
	bool useAwful = false;

	if (!useAwful) {
		// draw yellow square all around, with the word "EDIT" at top right and
		// bottom left corners

		// box around (big yellow rectangle with slightly smaller white rectangle)
		glColor3ub(255, 255, 0); // yellow
		int frameThickness = 5;
		DrawingUtilNG::drawRectangle(frameThickness, frameThickness,
			winWidth - 2 * frameThickness - 1, winHeight - 2 * frameThickness - 1, true,
			winWidth, winHeight);

		// little boxes for EDIT label
		glColor3ub(255, 255, 0); // yellow
		int boxW = 40, boxH = 18;
		DrawingUtilNG::drawRectangle(winWidth - boxW, 0, boxW, boxH, true);
		DrawingUtilNG::drawRectangle(0, winHeight - boxH, boxW, boxH, true);

		// label "EDIT"
		glColor3ub(0, 0, 0); // black
		glRasterPos2i(winWidth - boxW + 3, boxH - 3);  // top right
		YsGlDrawFontBitmap8x12("EDIT");
		glRasterPos2i(3, winHeight - 3);  // bottom left
		YsGlDrawFontBitmap8x12("EDIT");

		// little box for instructions on adding and deleting points
		glColor3ub(255, 255, 0); // yellow
		DrawingUtilNG::drawRectangle(winWidth, winHeight, -4 * boxW, -2 * boxH, true);
		glColor3ub(0, 0, 0); // black
		glRasterPos2i(winWidth - 3.7 * boxW + 3, winHeight - boxH - 3);
		YsGlDrawFontBitmap8x12("A : Add point");
		glRasterPos2i(winWidth - 3.7 * boxW + 3, winHeight - 3);
		YsGlDrawFontBitmap8x12("D : Delete point");

	}
	else {
		// awful edit indicator (but simple to code :-)
		glColor3ub(0, 0, 0); // black
		glRasterPos2i(0, 30);  // top right
		YsGlDrawFontBitmap20x28("YOU ARE NOW IN EDIT MODE");
	}
}

Point2D TrackManager::getScreenCoords(Point2D worldCoords)
{
	float screenX = worldCoords.x * scale + panX;
	float screenY = worldCoords.y * -scale + panY;
	return { screenX, screenY };
}

Point2D TrackManager::getWorldCoords(Point2D screenCoords)
{
	float worldX = (screenCoords.x - panX) / scale;
	float worldY = (screenCoords.y - panY) / -scale;
	return { worldX, worldY };
}

void TrackManager::manageMouse()
{
	// handle mouse input (OpenGL is still in screen coords)
	stringstream coordStream;     // for displaying coordinates on screen
	FsPollDevice();
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

		//if (mouseEvent == FSMOUSEEVENT_RBUTTONDOWN) {
		//	// put whatever code is needed to indicate if right click 
		//	// is inside or outside of current shape
		//	if (theShapes.at(currShape).isContained(worldPnt)) {
		//		theSoundPlayer.PlayOneShot(insideSound);
		//	}
		//	else 
		//		theSoundPlayer.PlayOneShot(outsideSound);
		//}

		// figure out if there's a point near mouse location
		if (!vertexIsMoving) { // avoid changing currVertex while moving a vertex
			currVertex = theTrack.getIndex(worldPnt, hoverDistance);
			//if (currVertex > 0)
			//	cout << "Hovered over Pnt " << currVertex << endl;
		}
		if (mouseEvent == FSMOUSEEVENT_LBUTTONUP) {
			vertexIsMoving = false;
		}
		else if (leftButton && mouseEvent == FSMOUSEEVENT_MOVE && currVertex > 0) {
			vertexIsMoving = true;
			theTrack.movePoint(worldPnt, currVertex);
		}
	}

	// capture location of first button press (needed for panning and zooming)
	if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN || mouseEvent == FSMOUSEEVENT_MBUTTONDOWN) {
		prevScreenX = screenX; prevScreenY = screenY;
	}

	// disallow panning and zooming with mouse when a vertex is moving
	if (!vertexIsMoving) {

		// pan in x and y axes when Ctrl key is held down and left button is down
		// note: I added middle button (wheel) drag for panning
		if (middleButton || (FsGetKeyState(FSKEY_CTRL) && leftButton)) {
			// no need for scale since the screen-to-model ratio is not applicable
			panX += (screenX - prevScreenX);
			panY += (screenY - prevScreenY);
			prevScreenX = screenX; prevScreenY = screenY; // reset previous values to continue move
		}

		// zoom in and out when Shft key is held down and left button is down
		// note: I added wheel rolling for zoomimg, which accidentally is also
		//       triggered by touchpad pinch and two finger scroll
		else if (key == FSKEY_WHEELUP || key == FSKEY_WHEELDOWN
			|| (FsGetKeyState(FSKEY_SHIFT) && leftButton)) {
			double oldScale = scale;
			if (key == FSKEY_WHEELUP)
				scale *= 1.03; // less jumpy than zooming with +/- keys
			else if (key == FSKEY_WHEELDOWN)
				scale /= 1.02;
			else if (screenY < prevScreenY)
				scale *= max(1.02, (prevScreenY - screenY) * 0.1);
			else if (screenY > prevScreenY)
				scale /= max(1.02, (prevScreenY - screenY) * -0.1);

			// adjust panX and panY so point under mouse does not move
			// i.e., we can zoom in/out on a specific point
			// a bit complicated since you have to convert old origin to screen coords
			// then adjust pan, then convert to model coords. 
			// what you see below is the simplified equation after all substitutions
			// rounding reduces "shifting"
			if (key == FSKEY_WHEELUP || key == FSKEY_WHEELDOWN) {
				panX = (int)round((screenX * (oldScale - scale)
					+ panX * scale) / oldScale);
				panY = (int)round((screenY * (oldScale - scale)
					+ panY * scale) / oldScale);
			}
			prevScreenX = screenX; prevScreenY = screenY; // reset previous values to continue move
		}
	}
}

void TrackManager::addButtonsVert(GraphicFont* aFont, int xLoc, int wid)
{
	int hei = 30;
	int spacing = 10;

	int currY = 30;
	theButtons.add(xLoc, currY, wid, hei, FSKEY_L, "Load", aFont,
		"Load a track from a file");
	
	currY += hei + spacing;
	theButtons.add(xLoc, currY, wid, hei, FSKEY_S, "Save", aFont,
		"Save track to a file");

	currY += hei + spacing;
	theButtons.add(xLoc, currY, wid, hei, FSKEY_H, "Hue", aFont,
		"Cycle through several colors of track");

	//currY += hei + spacing;
	//theButtons.add(xLoc, currY, wid, hei, FSKEY_Q, "Sound", aFont,
	//	"Toggle sound feedback on/off");

	currY += hei + spacing;
	theButtons.add(xLoc, currY, wid, hei, FSKEY_Z, "View All", aFont,
		"Adjust view to fit the whole track");

	currY += hei + spacing * 3;
	theButtons.add(xLoc, currY, wid, hei, FSKEY_E, "Edit", aFont,
		"Toggle Edit Mode");

	currY += hei + spacing * 3;
	theButtons.add(xLoc, currY, wid, hei, FSKEY_B, "Add Box", aFont,
		"Add a box to the track");

	currY += hei + spacing;
	theButtons.add(xLoc, currY, wid, hei, FSKEY_R, "Remove", aFont,
		"Remove box from the track");

	currY += hei + spacing;
	theButtons.add(xLoc, currY, wid, hei, FSKEY_I, "Initial", aFont,
		"Initialize model (put all boxes at initial positions)");

	currY += hei + spacing * 3;
	GraphicFont* boldFont = new JokermanFont;
	boldFont->setColorRGB(1., 0., 0.);
	theButtons.add(xLoc, currY, wid, hei, FSKEY_SPACE, "GO/STOP", boldFont,
		"Start/Stop the simulation");

	// to disable a button (will gray out and won't return its value)
	//theButtons.disableButton(FSKEY_SPACE);

}

void TrackManager::addSlideBox()
{
	sendUserToConsole();

	printAllBoxes();

	theBoxes.push_back(SlideBox(&theTrack));
	theBoxes.back().loadFromConsole();

	showMenu();
}

void TrackManager::printAllBoxes()
{
	int i = 1;
	if (theBoxes.size() > 0) {
		cout << endl << "Slide boxes currently in model:" << endl;
		for (auto& currBox : theBoxes) {
			cout << "   " << i++ << ") " << currBox << endl;
		}
		cout << endl;
	}
}

void TrackManager::sendUserToConsole() {
	glColor3f(0, 0, 0);
	glRasterPos2d(100, 200);
	YsGlDrawFontBitmap20x28("Input required on console . . .");
	FsSwapBuffers();
}

void TrackManager::removeSlideBox()
{
	if (theBoxes.size() == 0) {
		cout << endl << "No slide boxes to remove" << endl;
	}
	else {
		sendUserToConsole();
		printAllBoxes();

		int userSelection;
		cout << "     Select a slide box to remove (0 for none) >> ";
		cin >> userSelection;
		if (1 <= userSelection && userSelection <= theBoxes.size())
			theBoxes.erase(theBoxes.begin() + userSelection - 1);
	}
	showMenu();
}

bool TrackManager::manage()
{
	ofstream outFile;
	int buttonKey;

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	// reset all transformations
	glLoadIdentity();

	FsPollDevice();
	key = FsInkey();

	// handle mouse input (remember that OpenGL is still in screen coords)
	manageMouse();

	// check if a button was clicked
	if (key == FSKEY_NULL && mouseEvent == FSMOUSEEVENT_LBUTTONDOWN) {
		buttonKey = theButtons.checkClick(screenX, screenY);

		if (buttonKey != FSKEY_NULL)
			key = buttonKey;  // pretend the user pressed a key 
	}

	switch (key) {
	case FSKEY_L: // load a track file
		fileName = DrawingUtilNG::getStringFromScreen("Enter name of file to load.",
			"Press ENTER when done, ESC to cancel.");
		if (fileName.length() > 0) {

			if (fileName.find(".track") == string::npos)
				fileName += ".track";

			inFile.open(fileName);
			if (inFile.is_open()) {
				theTrack.readFile(inFile);
				inFile.close();
				cout << "       A new track was loaded from file " << fileName << endl;

				// change zoom to show newly loaded track
				resetView();
			}
			else
				cout << "       ERROR: Was not able to open file " << fileName << endl;
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
	case FSKEY_Z:   // reset Zoom to fit all shapes
		resetView();
		break;
	case FSKEY_E:
		inEditMode = !inEditMode;
		break;
	case FSKEY_S: // save current track (similar to load track above)
		//sendUserToConsole();
		//cout << "Filename for saving current track >> ";
		//cin >> fileName;
		fileName = DrawingUtilNG::getStringFromScreen("Enter name of file to save.",
			"Press ENTER when done, ESC to cancel.");
		if (fileName.length() > 0) {

			if (fileName.find(".track") == string::npos)
				fileName += ".track";

			outFile.open(fileName);
			if (outFile.is_open()) {
				outFile << theTrack;
				outFile.close();
				cout << "Just saved " << fileName << " to current folder." << endl;
			}
			else {
				cout << "Cannot open file " << fileName << " for output." << endl;
			}
			showMenu();
		}
		break;
	case FSKEY_H:
		theTrack.changeColor(10.f);
		break;
	case FSKEY_B:
		addSlideBox();
		break;
	case FSKEY_R:
		removeSlideBox();
		break;
	case FSKEY_I:  // set to initial state
		for (auto& currBox : theBoxes) {
			currBox.reset();
		}
		break;
	case FSKEY_SPACE:
		simulationIsRunning = !simulationIsRunning;
		break;

	}

	if (inEditMode) {  // also for PS04
		paintEditIndicator();
		switch (key) {
		case FSKEY_A:   // add a point for spline control
			if (currVertex > 0) { // there is a highlighted point
				theTrack.addPoint(currVertex, 0.5);
			}
			break;
		case FSKEY_D:   // delete a point
			if (currVertex > 0) { // there is a highlighted point
				theTrack.removePoint(currVertex);
			}
			break;
		case FSKEY_P:  // toggle showing points for current shape
			showThePoints = !showThePoints;
			break;
		}
	}

	// draw edit mode indicator
	if (inEditMode)
		paintEditIndicator();

	// set up axes to "math normal" (origin at lower left, y-axis going up)
	// and pan and scale
	glTranslatef(panX, panY, 0);
	glScalef(scale, -scale, 1);

	theTrack.paint(false, useFillMode, showThePoints || inEditMode);

	// highlight point that could be selected
	if (inEditMode && currVertex > 0) {
		glColor3ub(215, 215, 0);
		theTrack.paintPoint(currVertex, 6. / scale);
	}

	int i = 2;
	double red, green, blue;
	for (auto& currBox : theBoxes) {
		// here Nestor is painting each box a different color (60 degrees different in HSV)
		// your box may have its own color (or material/texture)
		DrawingUtilNG::hsv2rgb(i++ * 60, 1, 1, red, green, blue);
		glColor3f(red, green, blue);

		currBox.paint();
		if (simulationIsRunning)
			currBox.move(0.025);  // 25 milliseconds (should change this to do "real" time?)
	}

	// reset all transformations and paint the buttons on top of everything
	glLoadIdentity();
	theButtons.paint();
	theButtons.checkHover(screenX, screenY); // remove hover feedback for better performance ?


	return key != FSKEY_ESC;
}

