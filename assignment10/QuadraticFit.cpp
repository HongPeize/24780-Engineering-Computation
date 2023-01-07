//
//  QuadraticFit.cpp
//  assignment10
//
//  Created by James Hong on 2022-11-23.
//

#include "QuadraticFit.h"


pair<double, double> QF::fit(){
    pair <double, double> a1_a2;
    re_initialize();
    for (int i = 0; i < thePoints.size(); i++){
        sumX += thePoints[i].x;
    }
    
    for (int i = 0; i < thePoints.size(); i++){
        sumX2 += pow(thePoints[i].x,2);
    }
    
    for (int i = 0; i < thePoints.size(); i++){
        sumX3 += pow(thePoints[i].x,3);
    }
    
    for (int i = 0; i < thePoints.size(); i++){
        sumX4 += pow(thePoints[i].x,4);
    }
    
    for (int i = 0; i < thePoints.size(); i++){
        sumY += thePoints[i].y;
    }
    
    for (int i = 0; i < thePoints.size(); i++){
        sumXY += thePoints[i].x * thePoints[i].y;
    }
    
    for (int i = 0; i < thePoints.size(); i++){
        sumX2Y += pow(thePoints[i].x, 2) * thePoints[i].y;
    }
    a2 = (sumY * sumX2 - sumXY * sumX)/(sumX2 * sumX2 - sumX3 * sumX);
    a1 = (sumY * sumX2 - sumX2 * sumX2 * a2)/(sumX * sumX2);
    a1_a2 = make_pair(a1,a2);
    return a1_a2;
    
}

void QF::paintFit(){
    //int scale = hei/upperBound.y;
    
    //int sizeX = 4, sizeY = 4;
    glColor3ub(255,0,0);
    if (thePoints.size()>=2){
        glBegin(GL_LINES);
        glVertex2f(0, 0);
        for (float i = 0; i < upperBound.x; i+=0.01){
            float y = a1 * i + a2 * pow(i,2);
            glVertex2f(i,y);
            glVertex2f(i,y);
        }
        glEnd();
    }
    
    glLoadIdentity();
    stringstream live;
    live<< fixed; live << "y="; live << a1; live << "x+"; live << a2; live<<"x^2";
    string equation = live.str();

    glColor3ub(0,0,0);
    glRasterPos2i(10,25);
    YsGlDrawFontBitmap16x24(equation.c_str());
}

void QF::paintpoint(){
    glLoadIdentity();
    glColor3ub(0,255,0);
    float pntSize;
    if (thePoints.size() <= 1)
        pntSize = 4.f;
    else
        // set pntSize to 10% of the average line segment length
        pntSize = 0.1 * perimeter() / thePoints.size();
    
    for (int i = 1; i <= thePoints.size(); i++) {
        paintPoint(i, 0.2);
    }
}

void QF::showMenu(){
    cout << "\n\n";
    cout << "Use these keys on the screen:" << endl;
    cout << " Arws : pan in all directions (also Ctrl+LeftButtonDrag)" << endl;
    cout << "  +/- : zoom in and out (also Shft+LeftButtonDrag)" << endl;
    cout << "    R : Reset View" << endl;        // PS04
    cout << endl;

    cout << "    L : Load track from file" << endl;
    cout << "    S : show point" << endl;            // PS04
    cout << endl;

    cout << "  ESC : exit program" << endl;
}

void QF::re_initialize(){
    sumY = 0;
    sumX = 0;
    sumX2 = 0;
    sumX3 = 0;
    sumX4 = 0;
    sumXY = 0;
    sumX2Y = 0;
}

bool QF::removeData(float xVal) {
    for (int i = 0; i <= thePoints.size(); i++) {
        if (thePoints[i].x == xVal) {
            thePoints.erase(thePoints.begin() + i);
            return true;
        }
    }
    return false;
}

bool QF::addData(float xVal, float yVal) {
    for (int i = 0; i <= thePoints.size(); i++) {
        if (thePoints[i].x == xVal && thePoints[i].y == yVal) {
            return false;
        } else if (xVal > thePoints[i].x && xVal < thePoints[i + 1].x) {
            thePoints.insert(thePoints.begin() + i + 1, {xVal, yVal});
        }
    }
    return true;
}
