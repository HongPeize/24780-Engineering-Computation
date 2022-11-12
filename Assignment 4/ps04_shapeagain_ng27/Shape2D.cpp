#include <iostream>
#include <math.h>
#include "fssimplewindow.h"
#include "DrawingUtilNG.h"
#include "Shape2D.h"

using namespace std;

Shape2D::Shape2D()
{
	// nothing here yet
}

Shape2D::Shape2D(std::ifstream& input)
{
	// these will temporarily hold the values read from the file
	float newX, newY;

	// these are used to avoid duplicate points, initialized to values that
	// essentially mean "no point at all" (the negative of largest possible float number)
	float oldX = -INFINITY, oldY = -INFINITY;

	while (!input.eof()) {  // continue reading until the whole file has been read

		// the ifstream variable "input" can be used just like "cin".
		// it is like magic in that it does all the "translating" and advancing
		// down the line and down the file, using tabs, spaces, and newline
		// characters as separators.
		input >> newX >> newY;

		// we want to avoid the consecutive points being exactly the same
		if (newX != oldX || newY != oldY)
			thePoints.push_back({ newX, newY }); // define Point2D on the fly & add to vector

		// reset old coords in preparation for reading next coords
		oldX = newX; oldY = newY;
	}
	recalcShape();
}

bool Shape2D::addPoint(Point2D newPoint, int index)
{
	if (index < 1)
		return false;
	else {
		int insertionLoc;
		if (index > thePoints.size()) {
			thePoints.push_back(newPoint);
			insertionLoc = thePoints.size() - 1;
		}
		else {
			thePoints.insert(thePoints.begin() + index - 1, newPoint);
			insertionLoc = index - 1;
		}

		// check self-intersects and remove new point if needed
		if (selfIntersects()) {
			thePoints.erase(thePoints.begin() + insertionLoc);
			return false;
		}
		else {
			recalcShape(); // new point requires recalc
			return true;
		}

	}
}

bool Shape2D::addPoint(int index, float ratio)
{
	if (0. <= ratio || ratio >= 1.0 || index < 2 || index >= thePoints.size())
		return false;
	else {
		// insert a point between index-2 and index-1
		// the coords of new point are based on similar triangles
		// coords = prevPoint + ratio * (difference from nextPoint to newPoint)
		float newX = thePoints[index - 2].x
			+ ratio * (thePoints[index - 1].x - thePoints[index - 2].x);
		float newY = thePoints[index - 2].y
			+ ratio * (thePoints[index - 1].y - thePoints[index - 2].y);
		thePoints.insert(thePoints.begin() + index - 1, { newX, newY });
	}

	// note that this method of point addition can never create self-intersect
	// also, perimeter and bounds are not changed so no need for recalc
}

bool Shape2D::removePoint(int index)
{
	if (index < 1 || index > thePoints.size())
		return false;
	else {
		Point2D oldPnt = thePoints.at(index - 1); // hold it just in case
		thePoints.erase(thePoints.begin() + index - 1);

		// check self-intersects and replace point if needed
		if (selfIntersects()) {
			thePoints.insert(thePoints.begin() + index - 1, oldPnt);
			return false;
		}
		else {
			recalcShape(); // removal requires recalc
			return true;
		}
	}
}

void Shape2D::paint(bool closed, bool filled, bool showPoints, float colorOverride)
{
	if (thePoints.size() >= 2) {
		//Point2D prevPoint = thePoints.front();

		double R, G, B;

		if (colorOverride == -1)
			colorOverride = colorHue;

		DrawingUtilNG::hsv2rgb(colorOverride, 1., 1., R, G, B);

		glColor3d(R, G, B);

		glBegin(GL_LINES);
		glVertex2f(thePoints.front().x, thePoints.front().y);

		for (auto currPnt : thePoints) {
			glVertex2f(currPnt.x, currPnt.y); // end of line
			glVertex2f(currPnt.x, currPnt.y); // start of line
		}
		if (closed)
			glVertex2f(thePoints.front().x, thePoints.front().y);
		glEnd();

		if (showPoints) {
			float pntSize;
			if (thePoints.size() <= 1)
				pntSize = 4.f;
			else
				// set pntSize to 10% of the average line segment length
				pntSize = 0.1 * perimeter() / thePoints.size();

			for (auto currPnt : thePoints) {
				glTranslatef(currPnt.x, currPnt.y, 0.f);

				glBegin(GL_QUADS);
				glVertex2f(pntSize, 0);
				glVertex2f(0, pntSize);
				glVertex2f(-pntSize, 0);
				glVertex2f(0, -pntSize);
				glEnd();

				glTranslatef(-currPnt.x, -currPnt.y, 0.f);
			}
		}
	}
}

Point2D Shape2D::getPoint(int index)
{
	if (0 < index && index <= thePoints.size())
		return thePoints.at(index - 1);
	else
		return { -INFINITY, -INFINITY };
}

bool Shape2D::movePoint(Point2D newCoords, int index)
{
	if (0 < index && index <= thePoints.size()) {
		Point2D oldPnt = thePoints.at(index - 1); // hold it just in case

		thePoints.at(index - 1) = newCoords;

		// check self-intersects and restore old point if needed
		if (selfIntersects()) {
			thePoints.at(index - 1) = oldPnt;
			return false;
		}
		else {
			recalcShape(); // new point requires recalc
			return true;
		}
	}
	else
		return false;
}

bool Shape2D::movePointDelta(Point2D deltaCoords, int index)
{
	if (0 < index && index <= thePoints.size()) {
		Point2D oldPnt = thePoints.at(index - 1);

		return	movePoint({ oldPnt.x + deltaCoords.x,oldPnt.y + deltaCoords.y }, index);
	}
	else
		return false;
}

int Shape2D::getIndex(Point2D givenCoord, float dist)
{
	// do quick bounds check
	if (givenCoord.x < (lowerBound.x - dist) || givenCoord.x >(upperBound.x + dist)
		|| givenCoord.y < (lowerBound.y - dist) || givenCoord.y >(upperBound.y + dist))
		return -1;

	else {  // go through all points to see if there's a match
		Point2D currPoint;
		for (int i = 0; i < thePoints.size(); i++) {
			if (isInSquare(givenCoord, thePoints.at(i), dist))
				return i + 1;
		}
		return -1;
	}
}

bool Shape2D::isInSquare(Point2D testPoint, Point2D targetPoint, float dist)
{
	// using what I learned from spaceships and targets
	return abs(testPoint.x - targetPoint.x) <= dist && abs(testPoint.y - targetPoint.y) <= dist;

	// this works too, but is more complicated
	//return !(testPoint.x < (targetPoint.x - dist) || testPoint.x >(targetPoint.x + dist)
	//	|| testPoint.y < (targetPoint.y - dist) || testPoint.y >(targetPoint.y + dist));
}

bool Shape2D::selfIntersects()
{
	if (thePoints.size() < 4) // even a triangle cannot self-intersect
		return false;
	else {
		Point2D intersectionPnt;
		Point2D aheadPnt, rearPnt = thePoints.back(); // begin with "extra segment" (from last pnt to first pnt)

		// this won't work since I need two indices
		//for (auto currPnt : thePoints) {

		for (int i = 0; i < thePoints.size() - 1; i++) {
			aheadPnt = thePoints[i];

			// Check intersection between line segment from rearPnt to aheadPnt ("steady" segment)
			//   and every other segment that follows it. 
			// DO NOT check adjacent segments since their true intersection is always
			//   the point they share (but that's not self-intersecting)
			for (int j = i + 1; j < thePoints.size() - 1; j++) {

				// don't want to check "extra segment" and last segment
				if (i == 0 && j >= thePoints.size() - 2) 
					intersectionPnt = { -INFINITY, -INFINITY };  // no intersection
				else
					intersectionPnt = Line2D::getTrueIntersection(rearPnt, aheadPnt,
						thePoints[j], thePoints[j + 1]);

				if (intersectionPnt.x != -INFINITY)
					return true;
			}

			rearPnt = aheadPnt; // advance the "steady" segment
		}

		return false;  // if went through whole loop then there are no intersects
	}
}

void Shape2D::recalcShape()
{
	perim = 0.;
	if (thePoints.size() > 0) {
		Point2D prevPnt = thePoints.back();

		// initialize bounds
		lowerBound = upperBound = prevPnt; // yes, this is allowed :-)

		for (auto currPnt : thePoints) {

			// check bounds 
			// (using the else is a tiny bit more efficient, noting that if
			// a coord is less than lowerBound and CANNOT be greater than upperBound)
			if (currPnt.x < lowerBound.x)
				lowerBound.x = currPnt.x;
			else if (currPnt.x > upperBound.x)  // 
				upperBound.x = currPnt.x;

			if (currPnt.y < lowerBound.y)
				lowerBound.y = currPnt.y;
			else if (currPnt.y > upperBound.y)
				upperBound.y = currPnt.y;

			// augment perimeter
			perim += Line2D::getLength(prevPnt, currPnt);
			prevPnt = currPnt;
		}
	}
	if (thePoints.size() < 3)
		perim = 0.f;   // perimeter is not valid 
}

std::ostream& operator<<(std::ostream& os, const Shape2D& aShape)
{
	for (auto currPnt : aShape.thePoints) {
		os << currPnt.x << "\t" << currPnt.y << endl;
	}
	return os;
}
