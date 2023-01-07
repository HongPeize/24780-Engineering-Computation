#pragma once
/*
Nestor Gomez
Carnegie Mellon University
Eng. Computation, 24-780-B
Prob Set 9
Due Tues. Nov. 22, 2022
*/


#include "Shape2D.h"

class Track2D : public Shape2D {
public:
//protected:
	std::vector<Point2D> splinePoints;
	int splineSubdivisions = 20;
	float splineTension = 0.8;
	float length = 0;


	Track2D() {};

	Track2D(std::ifstream inFile) : Shape2D(inFile) {};

	// over-ride
	void paint(bool closed = true, bool filled = false,
		bool showPoints = false, float colorOverride = -1.f);

	float getLength() { return length; }

	// measured along spline
	Point2D getCoords(float givenLength); 
	
	// measured from back point to forward point
	float getAngle(float givenLength);

	// over-ride (don't need to over-ride the other version of this function)
	bool isContained(float testX, float testY, bool isInclusive = true) {
		return true;
	}

	// over-ride
	bool addPoint(int index, float ratio);

protected:
	// returns the index of the spline point that is just before the givenLength
	// and the fraction (0.0 to 1.0) that the givenLength overlaps the back point
	// used by 
	void getBackIndex(float givenLength, int &backIndex, float& fraction);
	
	// over-ride
	bool selfIntersects() { return false; };

	// over-ride
	void recalcShape();

	void recalcSpline();
	void segmentPoints(int segIndex);
};
