#pragma once
#include <math.h>

struct Point2D {
	float x;
	float y;
};

class Line2D {

	public:
	// returns the distance from one point to the other.
		static double getLength(Point2D startPoint, Point2D endPoint);
		// returns the distance from one point to the other.
		static double getLength(float startX, float startY, float endX, float endY);
		// returns true if checkpoint is between startPoint and endpoint.
		// Uses a tolerance based on distance from startPoint to endPoint.
		
		static bool isBetween(Point2D startPoint, Point2D endPoint, Point2D checkPoint);
		
		// returns the mathematical intersection point of the two lines
		// (does NOT use slopes since vertical lines have undefined slopes)
		// return { -INFINITY, -INFINITY } if there is no intersection
		static Point2D getIntersection(Point2D lineAstart, Point2D lineAend,
			Point2D lineBstart, Point2D lineBend);

};