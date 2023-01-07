//
//  QuadraticFit.h
//  assignment10
//
//  Created by James Hong on 2022-11-23.
//

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <sstream>
#include "Shape2D.h"
#include "fssimplewindow.h"
#include "DrawingUtilNG.h"
#include "ysglfontdata.h"

using namespace std;

class QF: public Shape2D{
private:
    double sumX = 0;
    double sumX2 = 0;
    double sumX3 = 0;
    double sumX4 = 0;
    double sumY = 0;
    double sumXY = 0;
    double sumX2Y = 0;
    double a1 = 0;
    double a2 = 0;

public:
    pair<double, double> fit();
    void paintFit(int wid, int hei, bool showpoints, int panX, int panY, float Zoom_scale);
    void showMenu();
    void re_initialize();
};
