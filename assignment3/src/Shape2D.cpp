#include "Line2D.h"
#include "Shape2D.h"
#include "fssimplewindow.h"
using namespace std;

// default constructor for the class. Initializes member variables only.

Shape2D::Shape2D() {};

// additional constructor for the class. Takes a pre-created ifstream and uses it to read coordinate
// information for the shape. Note that the method�s parameter cannot be a string filename
// because the file may already be in the process of being read. The constructor needs to
// instantiate any constituent objects and/or data structures.
Shape2D::Shape2D(std::ifstream& input){
    // these will temporarily hold the values read from the file
    float newX, newY;

    // these are used to avoid duplicate points, initialized to values that
    // essentially mean "no point at all" (the negative of largest possible float number)
    float oldX = -INFINITY, oldY = -INFINITY;

    while (!input.eof()) { // continue reading until the whole file has been read

    // the ifstream variable "input" can be used just like "cin".
    // it is like magic in that it does all the "translating" and advancing
    // down the line and down the file, using tabs, spaces, and newline
    // characters as separators.
        input >> newX >> newY;

        // we want to avoid the consecutive points being exactly the same
        if (newX != oldX || newY != oldY)   // corrected a mistake here
        thePoints.push_back({ newX, newY }); // define Point2D on the fly & add to vector

        // reset old coords in preparation for reading next coords
        oldX = newX; oldY = newY;
    }
}
// adds a coordinate point such that the new point becomes the index-th point . For example,
// an index value of 3 will insert a point between the existing 2nd and 3rd points such that the
// new point becomes the new 3rd point. An index of 1 will insert the new point at the start
// of the shape and an index greater than the number of points will insert the new point as
// the last point. Function returns false only if the new point cannot be added for any reason.
bool Shape2D::addPoint(Point2D newPoint, int index){
    if ((index>0) && (index <= thePoints.size())){
        thePoints.insert(thePoints.begin()+index-1, newPoint);
        return true;
    }else if(index > thePoints.size()){
        thePoints.insert(thePoints.begin()+thePoints.size(), newPoint);
        return true;
    }else{
        return false;
    }
}

// creates a coordinate point with the given coordinates and inserts it into the path such that
// the new point becomes the index-th point. Otherwise, similar to above.
bool Shape2D::addPoint(float newX, float newY, int index){
    Point2D InsertedPoint;
    InsertedPoint.x = newX; InsertedPoint.y = newY; 
    if ((index>0) && (index <= thePoints.size())){
        thePoints.insert(thePoints.begin()+index-1, InsertedPoint);
        return true;
    }else if(index > thePoints.size()){
        thePoints.insert(thePoints.begin()+thePoints.size(), InsertedPoint);
        return true;
    }else{
        return false;
    }
}

// creates a coordinate point between vertices index-1 and index and inserts it into the line
// segment at the given ratio (between 0.0 & 1.0). The new point becomes the index-th point.
// Returns false if it cannot insert point (e.g., index is too large or too small, ratio value is
// inappropriate. Ratios close to zero will insert the new vertex near index-1
bool Shape2D::addPoint(int index, float ratio){
    Point2D RatioPoint;
    if(ratio > 0 && ratio<1){
    RatioPoint.x = (thePoints[index].x + thePoints[index-1].x)*ratio;
    RatioPoint.y = (thePoints[index].y + thePoints[index-1].y)*ratio;
    thePoints.insert(thePoints.begin()+index-1, RatioPoint);
        return true;
    }else{
        return false;
    }
}

// removes the indicated point from the shape. Function returns false only if the point
// cannot be removed for any reason.
bool Shape2D::removePoint(int index){
    if(index>0 && index<=thePoints.size()){
        thePoints.erase(thePoints.begin()+index-1);
        return true;
    }else{
        return false;
    }
}

// draws the shape on the graphics screen using OpenGL.
// Ignore default parameter for now (we‘ll get to them in PS04)

void Shape2D::paint(bool closed, bool filled){

    for (int i = 0; i < thePoints.size()-1; i++){
        glVertex2i(thePoints[i].x, thePoints[i].y);
        glVertex2i(thePoints[i+1].x, thePoints[i+1].y);
    }
    glVertex2i(thePoints[thePoints.size()-1].x, thePoints[thePoints.size()-1].y);
    glVertex2i(thePoints[0].x, thePoints[0].y);
    glEnd();
}

// calculates and returns the length of the perimeter of the shape.
float Shape2D::perimeter(){
    float Perimeter = 0;
    for (int i = 0; i < thePoints.size()-1; i++){
        Perimeter+=sqrt(pow(thePoints[i].x-thePoints[i+1].x,2) + pow(thePoints[i].y-thePoints[i+1].y,2));
    }
    Perimeter += sqrt(pow(thePoints[0].x-thePoints[thePoints.size()-1].x, 2) + pow(thePoints[0].y-thePoints[thePoints.size()-1].y, 2));
    
    return Perimeter;
}

// used to output all the coordinates of a shape. This can be tricky, so we‘ll discuss in lecture.
ostream& operator<<(ostream& os, const Shape2D& aShape){ //overloading operator
    for (int i = 0; i < aShape.thePoints.size(); i++){
        os << aShape.thePoints[i].x << "\t"
        << aShape.thePoints[i].y << endl;
    }
    return os;
};

