//
//  Object_in.h
//  individual project
//
//  Created by James Hong on 24/10/2022.
//

#pragma once
#include <stdio.h>
#include <iostream>
#include "DrawingUtilNG.h"
#include "fssimplewindow.h"
#include <math.h>
#include "yspng.h"
#define SCALE 20
#define CAR_SCALE 1.8
#define LIGHT_SCALE 0.5

#define PI 3.1415926
#define DEG2RAD 3.14159/180.0
using namespace std;

class tree{
private:
    int bound = 640;
    int locX1 = 35, locY1 = 18+10;
    int locX2 = 35, locY2 = 138+10;
    int locX3 = 35, locY3 = 258+10;
    int locX4 = 35, locY4 = 378+10;
    int locX5 = 35, locY5 = 498+10;
    int locX6 = 35, locY6 = 618+10;
    int locX7 = 685, locY7 = 18+10;
    int locX8 = 685, locY8 = 138+10;
    int locX9 = 685, locY9 = 258+10;
    int locX10 = 685, locY10 = 378+10;
    int locX11 = 685, locY11 = 498+10;
    int locX12 = 685, locY12 = 618+10;
    
public:
    float tree_step = 10.0;
    bool active = true;
    void paint();
    void move();
    void accel();
};

class road{
public:
    float bound = 37.0;
    float locX1 = 20.0, locY1 = 0.0;
    float locX2 = 20, locY2 = 8;
    float locX3 = 20, locY3 = 16;
    float locX4 = 20, locY4 = 24;
    float locX5 = 20, locY5 = 32;
    float locX6 = 8, locY6 = 15; // left roadside
    float locX7 = 32, locY7 = 15; // right roadside
    float Cross_locX = 0, Cross_locY = -0.5; // right roadside
    float horz_locX = -1.8, horz_locY = -10; // horizontal strip
    float zebra_locX = 12, zebra_locY = -2.5; // zebra

    float road_step = 0.5;
    bool active = true;
    bool cross_active = true;
    void paint();
    void move();
    void paint_cross();
    void move_cross();
    void paint_strip_horz();
    void move_strip_horz(){if (cross_active)horz_locY+=road_step;};
    void paint_arrow();
    void paint_other_half_cross();
    void paint_zebra_crossing();
    void zebra_crossing_move(){if(active)zebra_locY+=road_step;};
    void accel();
};

class car{
public:
    bool active = true;
    float locX1 = 300.0, locY1 = 220.0;
    void paint(int time);
    void move(){locX1+=8;};
};

class trafficlight{
private:
    float locX = 1170.0, locY_yellow = -260, locY_green = 90.0;
    
public:
    bool active = true;
    float light_step = 20;
    void paint_red();
    void paint_yellow();
    void paint_green();
    void move_red();
    void move_yellow();
};

class people{
public:
    bool active = true;
    float locX = 610.0, locY= -110;
    void paint();
    void move(){if (active)locX-=5;locY+=20*1.4;}
};

class speed_limit{
public:
    float locX = 490.0, locY= 30;
    void paint();
};
