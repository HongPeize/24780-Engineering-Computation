#pragma once
/*
Nestor Gomez
Carnegie Mellon University
Eng. Computation, 24-780-B
Prob Set 9
Due Tues. Nov. 22, 2022
*/

#include <map>
#include <math.h>

class Track2D;  // needed because Track.h may include SlideBox.h later

class SlideBox {
protected:
	// add whatever else you want
	// don't use (but don't delete) what you don't want 

	std::string label; // needed ?

	// using a map instead of individual member variables allows you to have
	// as many properties of type double as you want (width, height, initDist, etc)
	// see examples of how to use it below
	std::map<std::string, double> props;   

	double currDist, currVel, currAccel;
	bool showParameters = false;  // needed?

	Track2D* theTrack; // pointer so that many slidebox objects can point to same Track

public:
	SlideBox();
	SlideBox(Track2D* aTrack) : SlideBox() { theTrack = aTrack; }

	//void setInitialValues(double initDist, double initVel, double initAccel) {
	//	props["initDist"] = initDist;
	//	props["initVel"] = initVel;
	//	props["initAccel"] = initAccel;
	//}

	//void setStaticValues(double width, double height, double friction, double mass) {
	//	props["width"] = width;
	//	props["height"] = height;
	//	props["mu"] = friction;
	//	props["mass"] = mass;
	//}

	double getProp(std::string wanted) {
		if (props.find(wanted) != props.end())  // if the property exists
			return props.at(wanted);
		else
			return -INFINITY;
	}

	void reset() {
		currDist = props["initDist"];
		currVel = props["initVel"];
		currAccel = props["initAccel"];
	}

	void loadFromConsole();

	// perhaps use it as part of drawing the box ???
	void toggleShowParameters() { showParameters = !showParameters; }

	// moves the box by applying currVel for deltaT (with perhaps currAccel)
	// recalculates currVel by applying currAccel for deltaT
	// recalculates currAccel based on dynamic equilibrium
	void move(double deltaT);

	// draws the box at current location and orientation
	void paint();

	// outputs a single line that describes the static parameters of the slidebox
	// may be useful when asking users to add or delete boxes 
	friend std::ostream& operator<<(std::ostream& os, const SlideBox& aBox);

};
