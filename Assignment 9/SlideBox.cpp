#include <iostream>
#include <string>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "StringPlus.h"
#include "DrawingUtilNG.h"
#include "Track2D.h"
#include "StringPlus.h"

#include "SlideBox.h"

const double GRAVITY = 9.80665;  // this implies units are meters and seconds

SlideBox::SlideBox()
{
	// some default parameters for quick testing
	props["width"] = 2.;
	props["height"] = 1.5;
	props["mass"] = 3;   // actually does not affect calculations (cancels out)
	props["mu"] = 0.1;   // coeff of friction b/w box and track
	props["initDist"] = 0;  // at start of slide
	props["initVel"] = 0;   // starts from rest
	props["initAccel"] = 0; // no push

	theTrack = nullptr;
	reset();
}

void SlideBox::loadFromConsole()
{
	using namespace std;

	cout << endl << "Enter parameters for adding a slide box to model:" << endl;
  
	props["width"] =	StringPlus::getDouble(cin, "                               Box width (m) >> ");
    while (props["width"] <= 0){
        props["width"] =    StringPlus::getDouble(cin, "                               Box width (m) >> ");
        cout << "invalid width!" << endl;
    }
	props["height"] =	StringPlus::getDouble(cin, "                              Box height (m) >> ");
    while (props["height"] <= 0){
        props["height"] =    StringPlus::getDouble(cin, "                               Box height (m) >> ");
        cout << "invalid height!" << endl;
    }
    props["mass"] = props["width"] * props["height"];
    props["initDist"] = StringPlus::getDouble(cin, "                               Initial Distance (m) >> ");  // at start of slide
    props["initVel"] = StringPlus::getDouble(cin, "                               Initial Velocity (m/s) >> ");   // starts from rest
    props["initAccel"] = StringPlus::getDouble(cin, "                               Initial Accel (m/s^2) >> "); // no push
    props["mu"] = StringPlus::getDouble(cin, "                               Coefficient of friction >> ");
    currVel = props["initVel"];
    currDist = props["initDist"];
	// add more stuff . . .

}

void SlideBox::move(double deltaT)
{
    float TrackLength = theTrack->getLength();
	if (theTrack != nullptr && theTrack->getLength() > 0) {
		// change distance, velocity, and acceleration according to equations of motion
        float angle = (theTrack->getAngle(currDist)) * M_PI/180;
        currAccel = props["initAccel"] + (props["mass"] * GRAVITY * sin(-angle) - props["mu"] * props["mass"] * GRAVITY * cos(angle)) / props["mass"];
        currVel += currAccel * deltaT;//v = v0 + at
        currDist += deltaT * currVel;

	}
}

void SlideBox::paint()
{
	// use transformations to paint the box at it's current position and angle
    //need x and y dir dist and velocity
    bool filled = true;
    float angle = theTrack->getAngle(currDist);
    Point2D temp;
    temp = theTrack->getCoords(currDist);
    glTranslatef(temp.x, temp.y, 0);
    glRotatef(angle, 0,0,1);
    glBegin(GL_QUADS);
    DrawingUtilNG::drawRectangle(0, 0, props["width"], props["height"], true);
    glEnd();
}

std::ostream& operator<<(std::ostream& os, const SlideBox& aBox)
{
	auto oldPrecision = os.precision();
	os.precision(3);

	std::string spacer;
	if (&os == &std::cout) 
		spacer = ", "; // if outputting to console, use commas and keep on same line
	else
		spacer = "\n"; // if outputting to file, put each property on separate line
	
	// print properties in prescribed order
	std::vector<std::string> printOrder =
	{ "width", "height", "mu", "mass", "initDist", "initVel", "initAccel" };

	for (int i = 0; i < aBox.props.size(); i++) {
		if (aBox.props.find(printOrder[i]) != aBox.props.end()) { // if property is in map

			if (i > 0) os << spacer;
			os << printOrder[i] << "=" << aBox.props.at(printOrder[i]);// [] doesn't work here
		}
	}

	// print properties in alphabetical order (directly from map)
	//for (auto& item : aBox.props) {
	//  if (i>0) os << spacer;
	//	os << item.first << "=" << item.second;
	//}

	os.precision(oldPrecision);
	return os;
}
