#include "DrawingUtilNG.h"
#include "fssimplewindow.h"
#include "Track2D.h"


void Track2D::paint(bool closed, bool filled, bool showPoints, float colorOverride)
{
	if (thePoints.size() >= 2) {
		// draw the spline points (copy some code from Shape2D ?)
		// now draw thePoints (if asked)
        double red, green, blue;
        if (colorOverride > -1.f) // use override color
            DrawingUtilNG::hsv2rgb(colorOverride, 1.f, 1.f, red, green, blue);
        else                    // use shape's color
            DrawingUtilNG::hsv2rgb(colorHue, 1.f, 1.f, red, green, blue);

        glColor3d(red, green, blue);
        glBegin(GL_LINES);
        glVertex2f(thePoints.front().x, thePoints.front().y);
        for (auto currPnt : thePoints) {
            glVertex2f(currPnt.x, currPnt.y);
            glVertex2f(currPnt.x, currPnt.y);
        }
        glEnd();
		if (showPoints) {
			// (copy some code from Shape2D ?)
            float pntSize;
            if (thePoints.size() <= 1)
                pntSize = 4.f;
            else
                // set pntSize to 10% of the average line segment length
                pntSize = 0.1 * perimeter() / thePoints.size();

            for (int i = 1; i <= thePoints.size(); i++) {
                Shape2D::paintPoint(i, pntSize);
            }
		}
	}
}

Point2D Track2D::getCoords(float givenLength)
{
	// use getBackIndex() function to get index and fraction on splinePoints
	// use Line2D::scale() to get coords
    int backIndex = 0;
    float fraction = 0;
    getBackIndex(givenLength, backIndex, fraction);
    //return splinePoints[backIndex];

    return Line2D::scale(splinePoints[backIndex], splinePoints[backIndex+1], fraction);
}

float Track2D::getAngle(float givenLength)
{
	// use getBackIndex() function to get index and fraction on splinePoints
	// use Line2D::getAngle() to get coords
    int backIndex = 0;
    float fraction = 0;
    getBackIndex(givenLength, backIndex, fraction);
    return Line2D::getAngle(splinePoints[backIndex], splinePoints[backIndex+1]);
}

bool Track2D::addPoint(int index, float ratio)
{
	if (0. >= ratio || ratio >= 1.0 || index < 2 || index >= thePoints.size())
		return false;
	else {
		// insert a point on the spline some splinePoints back from
		int pointsBack = splineSubdivisions * (1.0 - ratio);
		int i = 0;
		auto targetPnt = thePoints.at(index - 1);
		double tolerance = 1e-5;
		while (i < splinePoints.size() && (abs(splinePoints.at(i).x - targetPnt.x) > tolerance
			|| abs(splinePoints.at(i).y - targetPnt.y) > tolerance) ) {
			i+= splineSubdivisions;
		}
		if (pointsBack < i && i <= splinePoints.size()) {
			Shape2D::addPoint(splinePoints.at(i - pointsBack), index);
			//recalcShape(); // needed?
			return true;
		}
		else
			return false;
	}
	return false;
}

void Track2D::getBackIndex(float givenLength, int& backIndex, float& fraction)
{
	if (splinePoints.size() > 1) {
		float lengthAtBackPoint = 0;
		float lengthAtForwardPoint = Line2D::getLength(splinePoints[0], splinePoints[1]);
		lengthAtBackPoint = 0;
		backIndex = 0;
		while (lengthAtForwardPoint < givenLength && backIndex < splinePoints.size()-1) {
			lengthAtBackPoint = lengthAtForwardPoint;
			lengthAtForwardPoint += Line2D::getLength(splinePoints[backIndex], splinePoints[backIndex + 1]);
			backIndex++;
		}
		fraction = (givenLength - lengthAtBackPoint) / (lengthAtForwardPoint - lengthAtBackPoint);
	}
	else {
		backIndex = -1;
		fraction = -1;
	}
}

void Track2D::recalcShape()
{
    // call recalcShape of parent class Shape2D
    Shape2D::recalcShape();
	
	// adjust perimeter
    if (thePoints.size() > 1)
        perim -= Line2D::getLength(thePoints.back(), thePoints.front());
	// call recalcSpine
    recalcSpline();
}

void Track2D::recalcSpline()
{
	splinePoints.clear();

	// now get the distances
	if (thePoints.size() > 2) {

		if (thePoints.size() >= 4) {

			splinePoints.push_back(thePoints.at(1));
			// first and last guide points are for sloping the first part of curve
			for (int i = 1; i < thePoints.size() - 2; i++) {
				// generate spline points
				segmentPoints(i);
			}

			// now get the overall length of the spline
			length = 0;
			for (int i = 1; i < splinePoints.size(); i++) 
				length += Line2D::getLength(splinePoints[i], splinePoints[i - 1]);
		}
	}
}

void Track2D::segmentPoints(int segIndex)
{
	float c = splineTension; // spline tension (0.0 means no spline at all)

	auto prev = thePoints[segIndex - 1];
	auto curr = thePoints[segIndex];
	auto next = thePoints[segIndex + 1];
	auto nextNext = thePoints[segIndex + 2];


	float xa = -c * prev.x + (2. - c) * curr.x
		+ (c - 2.) * next.x + c * nextNext.x;
	float xb = 2. * c * prev.x + (c - 3.) * curr.x
		+ (3. - 2. * c) * next.x - c * nextNext.x;
	float xc = -c * prev.x + c * next.x;
	float xd = curr.x;

	float ya = -c * prev.y + (2. - c) * curr.y
		+ (c - 2.) * next.y + c * nextNext.y;
	float yb = 2. * c * prev.y + (c - 3.) * curr.y
		+ (3. - 2. * c) * next.y - c * nextNext.y;
	float yc = -c * prev.y + c * next.y;
	float yd = curr.y;

	// add the spline points

	float t, x, y;
	for (int k = 1; k <= splineSubdivisions; k++) {
		t = float(k) / splineSubdivisions;  // parameter
		x = xa * t * t * t + xb * t * t + xc * t + xd;
		y = ya * t * t * t + yb * t * t + yc * t + yd;

		splinePoints.push_back({ x, y });
	}

}
