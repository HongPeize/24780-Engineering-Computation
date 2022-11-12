#pragma once
#include <fstream>
#include <vector>
#include "Line2D.h"

class Shape2D {
private:
	std::vector<Point2D> thePoints; // stores the vertices that define the shape
	
public:
	
	// default constructor for the class. Initializes member variables only.
	Shape2D();
	
	// additional constructor for the class. Takes a pre-created ifstream and uses it to read coordinate
	// information for the shape. Note that the method�s parameter cannot be a string filename
	// because the file may already be in the process of being read. The constructor needs to
	// instantiate any constituent objects and/or data structures.
	Shape2D(std::ifstream& input);

	// adds a coordinate point such that the new point becomes the index-th point . For example,
	// an index value of 3 will insert a point between the existing 2nd and 3rd points such that the
	// new point becomes the new 3rd point. An index of 1 will insert the new point at the start
	// of the shape and an index greater than the number of points will insert the new point as
	// the last point. Function returns false only if the new point cannot be added for any reason.
	bool addPoint(Point2D newPoint, int index);

	// creates a coordinate point with the given coordinates and inserts it into the path such that
	// the new point becomes the index-th point. Otherwise, similar to above.
	bool addPoint(float newX, float newY, int index);

	// creates a coordinate point between vertices index-1 and index and inserts it into the line
	// segment at the given ratio (between 0.0 & 1.0). The new point becomes the index-th point.
	// Returns false if it cannot insert point (e.g., index is too large or too small, ratio value is
	// inappropriate. Ratios close to zero will insert the new vertex near index-1
	bool addPoint(int index, float ratio);

	// removes the indicated point from the shape. Function returns false only if the point
	// cannot be removed for any reason.
	bool removePoint(int index);

	// draws the shape on the graphics screen using OpenGL.
	// Ignore default parameter for now (we�ll get to them in PS04)
	void paint(bool closed = true, bool filled = false);

	// calculates and returns the length of the perimeter of the shape.
	float perimeter();

	// used to output all the coordinates of a shape. This can be tricky, so we�ll discuss in lecture.
	friend std::ostream& operator<<(std::ostream& os, const Shape2D& aShape);
};