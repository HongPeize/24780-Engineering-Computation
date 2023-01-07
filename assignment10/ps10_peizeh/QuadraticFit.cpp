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

void QF::paintFit(int wid, int hei, bool showpoints, int panX, int panY, float Zoom_scale){
    int scale = hei/upperBound.y;
    
    int sizeX = 4, sizeY = 4;
    glColor3ub(255,0,0);
    if (thePoints.size()>=2){
        glBegin(GL_LINES);
        glVertex2f(0.5*wid, hei);
        for (float i = 0; i < upperBound.x; i+=0.01){
            float y = -(a1 * i + a2 * pow(i,2))*scale + hei;
            glVertex2f(i*scale+0.5*wid,y);
            glVertex2f(i*scale+0.5*wid,y);
        }
        glEnd();
    }
    glLoadIdentity();
    glColor3ub(0,255,0);
    if (showpoints){
        for (auto currPnt:thePoints){
            DrawingUtilNG::drawRectangle(currPnt.x*scale + 0.5*wid + panX, -currPnt.y*scale+panY + hei, sizeX*Zoom_scale, sizeY*Zoom_scale, true);
        }
    }
    glLoadIdentity();
    stringstream live;
    live<< fixed; live << "y="; live << a1; live << "x+"; live << a2; live<<"x^2";
    string equation = live.str();

    glColor3ub(0,0,0);
    glRasterPos2i(10,25);
    YsGlDrawFontBitmap16x24(equation.c_str());
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
