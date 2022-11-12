/*			_____
		   /     \
		  /       \				Nestor Gomez
	,----<         >----.		Carnegie Mellon University
   /                     \		EngrCompu, 24-780B
  /                       \		Prob Set 3. Due Tues. Sept. 20, 2022
  \                       /
   \                     /
	>                   <		A shape as a sequence of coordinate vertices/points
   /                     \		(xi, yi) that define a non-self-intersecting closed
  /                       \		loop with straight line segments from vertex to
  \                       /		vertex. Makes use of Line2D "library"
   \                     /
	`----<         >----'
		  \       /
		   \_____/
*/

#pragma once
#include <vector>
#include <fstream>

#include "Line2D.h"

class Shape2D {
protected:
	std::vector<Point2D> thePoints; // stores the vertices that define the shape

	float colorHue = 0;  // stores overall color of shape

	// derived parameters
	Point2D lowerBound = { -INFINITY, -INFINITY };
	Point2D upperBound = { -INFINITY, -INFINITY };
	float perim = 0.f;
	float area = 0.f;  // leave blank for now


public:
	// default constructor for the class. Initializes member variables only.
	Shape2D();

	// additional constructor for the class. Takes a pre-created ifstream and uses it to read coordinate
	// information for the shape. Note that the method’s parameter cannot be a string filename
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
	// the new point becomes the index-th point. Otherwise similar to above.
	bool addPoint(float newX, float newY, int index) {
		return addPoint({ newX, newY }, index);
	}

	// creates a coordinate point between vertices index-1 and index and inserts it into the line
	// segment at the given ratio (between 0.0 & 1.0). The new point becomes the index-th point.
	// Returns false if it cannot insert point (e.g., index is too large or too small, ratio value is
	// inappropriate. Ratios close to zero will insert the new vertex near index-1
	bool addPoint(int index, float ratio);

	// removes the indicated point from the shape. Function returns false only if the point
	// cannot be removed for any reason.
	bool removePoint(int index);

	// draws the shape on the graphics screen using OpenGL. Does not draw segment from
	// last point to first point if default parameter closed is set to false. Ignore second default
	// parameter for now. Shape is drawn in its own color unless colorOveride (not -1) is given
	void paint(bool closed = true, bool filled = false, 
		bool showPoints = false, float colorOverride = -1.f);

	// used to output all the coordinates of a shape to an output stream (file or cout)
	friend std::ostream& operator<<(std::ostream& os, const Shape2D& aShape);

	// returns overall width and height of shape
	float getWidth() { if (lowerBound.x > -INFINITY) return (upperBound.x - lowerBound.x); }
	float getHeight() { if (lowerBound.x > -INFINITY) return (upperBound.y - lowerBound.y); }

	// returns the bounding box of the shape
	Point2D getLowerBound() { return lowerBound; }
	Point2D getUpperBound() { return upperBound; }

	// for PS04, simply returns the pre-calculated length of the perimeter of the shape.
	float perimeter() { return perim; };

	// get coordinates of a point. The first point has index 1.
	// Returns {-INFINITY, -INFINITY} if index is invalid.
	Point2D getPoint(int index);

	// moves a point to new coordinates. The first point has index 1.
	// Returns false if index is invalid.
	bool movePoint(Point2D newCoords, int index);

	// changes the coordinates of a point by the given delta. The first point has index 1.
	// Returns false if index is invalid.
	bool movePointDelta(Point2D deltaCoords, int index);

	// returns the index of the first vertex (first vertex has index 1) that is near the givenCoord.
	// Uses distance as bounding square instead of radius to reduce calculations.
	int getIndex(Point2D givenCoord, float dist = 0.1);

	// change the color hue by adding some degrees.
	void changeColor(float changDeg) {
		colorHue = fmod(colorHue + changDeg, 360.f);
	}

private:
	// determines if any of the edges of the shape intersects with any other edge
	// makes use of Line2D::getTrueIntersection()
	bool selfIntersects();

	// calculates and stores shape-level derived properties so they don't all have to be
	// generated on the fly. (adapt old perimeter function to include upper and lower bound)
	void recalcShape();

	bool isInSquare(Point2D testPoint, Point2D targetPoint, float dist);

};