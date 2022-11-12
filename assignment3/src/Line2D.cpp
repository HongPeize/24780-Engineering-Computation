#include "Line2D.h"
#include <math.h>
#include <utility>
using namespace std;

// returns the distance from one point to the other.
double Line2D::getLength(Point2D startPoint, Point2D endPoint){
	return sqrt(pow(startPoint.x - endPoint.x, 2) + pow(startPoint.y - endPoint.y, 2));
}
// returns the distance from one point to the other.
double Line2D::getLength(float startX, float startY, float endX, float endY){
	return sqrt(pow(startX - endX, 2) + pow(startY - endY, 2));
}
// returns true if checkpoint is between startPoint and endpoint.
// Uses a tolerance based on distance from startPoint to endPoint.

bool Line2D::isBetween(Point2D startPoint, Point2D endPoint, Point2D checkPoint){
	if (checkPoint.x == (startPoint.x + endPoint.x)/2 && checkPoint.y == (startPoint.y + endPoint.y)/2){
		return true;
	}else{
		return false;
	}
}

// returns the mathematical intersection point of the two lines
// (does NOT use slopes since vertical lines have undefined slopes)
// return { -INFINITY, -INFINITY } if there is no intersection
Point2D Line2D::getIntersection(Point2D lineAstart, Point2D lineAend,
                                Point2D lineBstart, Point2D lineBend){
    
    if ((lineAstart.x == lineAend.x && lineBstart.x == lineBend.x) || (lineAstart.y == lineAend.y && lineBstart.y == lineBend.y)){
        double x = -INFINITY;
        double y = -INFINITY;
        Point2D intersection;
        intersection.x = x;
        intersection.y = y;
        return intersection;
    }else{
        double x = ((lineAstart.x*lineAend.y - lineAstart.y*lineAend.x)*(lineBstart.x - lineBend.x) - (lineAstart.x - lineAend.x)*(lineBstart.x*lineBend.y - lineBstart.y*lineBend.x))/((lineAstart.x-lineAend.x)*(lineBstart.y-lineBend.y) - (lineAstart.y - lineAend.y)*(lineBstart.x - lineBend.x));
        double y = ((lineAstart.x*lineAend.y - lineAstart.y*lineAend.x)*(lineBstart.y - lineBend.y) - (lineAstart.y - lineAend.y)*(lineBstart.x*lineBend.y - lineBstart.y*lineBend.x))/((lineAstart.x-lineAend.x)*(lineBstart.y-lineBend.y) - (lineAstart.y - lineAend.y)*(lineBstart.x - lineBend.x));
        Point2D intersection;
        intersection.x = x;
        intersection.y = y;
        return intersection;}
}
