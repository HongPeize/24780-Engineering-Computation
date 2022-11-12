/*
			o        	Nestor Gomez
		   /         	Carnegie Mellon University
		  /          	EngrCompu, 24-780B
		 /           	Prob Set 4. Due Tues. Sept. 27, 2022
		/
	   /             	The Line2D class does not define a line.
	  /              	The class is a collection of functions
	 /					(a library) used to make inferences about
	o                	line segments defined by two endpoints

*/
#pragma once

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

	// returns the intersection of the 2 line segments defined by start and end points given.
	// The true intersection differs from the mathematical intersection in that the two line segments
	// (not just their infinite linear extensions) must cross. If there is no true intersection
	// (i.e., the lines are parallel or the segments don’t cross), the function returns {-INFINITY, -INFINITY}.
	static Point2D getTrueIntersection(Point2D lineAstart, Point2D lineAend,
		Point2D lineBstart, Point2D lineBend);

	// returns the angle of the given line segment, from startPnt to endPnt.
	// The angle returned is in degrees (0-360), measured CCW from zero (the X-axis).
	// Makes use of atan2() function, so function is very short
	static float getAngle(Point2D startPnt, Point2D endPnt);

};