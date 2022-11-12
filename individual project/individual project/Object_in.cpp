//
//  Object_in.cpp
//  individual project
//
//  Created by James Hong on 24/10/2022.
//

#include "Object_in.h"

void tree::move(){
    if (active) {
        locY1 += tree_step; locY2 += tree_step;locY3 += tree_step;locY4 += tree_step;locY5 += tree_step;locY6 += tree_step;
        locY7 += tree_step; locY8 += tree_step;locY9 += tree_step;locY10 += tree_step;locY11 += tree_step;locY12 += tree_step;
        if (locY1 > bound){
            locY1 = -80;}
        if (locY2 > bound){
            locY2 = -80;}
        if (locY3 > bound){
            locY3 = -80;}
        if (locY4 > bound){
            locY4 = -80;}
        if (locY5 > bound){
            locY5 = -80;}
        if (locY6 > bound){
            locY6 = -80;}
        if (locY7 > bound){
            locY7 = -80;}
        if (locY8 > bound){
            locY8 = -80;}
        if (locY9 > bound){
            locY9 = -80;}
        if (locY10 > bound){
            locY10 = -80;}
        if (locY11 > bound){
            locY11 = -80;}
        if (locY12 > bound){
            locY12 = -80;}
    }
}

void tree::paint(){
    
    YsRawPngDecoder pngTemp;
    pngTemp.Decode("Tree.png");

    double scale1 = 0.11;
    int xSize = pngTemp.wid * scale1; // need for later
    int ySize = pngTemp.hei * scale1;

    GLuint textureId01; // this will be used as texture identifier for the second PNG (DON'T LOSE IT)

    glGenTextures(1, &textureId01); // Reserve texture identifier for other PNG
    glBindTexture(GL_TEXTURE_2D, textureId01); // Making the texture identifier current (or bring it to the deck)

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pngTemp.wid, pngTemp.hei, 0, GL_RGBA, GL_UNSIGNED_BYTE, pngTemp.rgba);

    int wid, hei;
    FsGetWindowSize(wid, hei); // nice little function

    // in order for textures to show, you must create a projection
    glViewport(0, 0, wid, hei);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor4d(1.0, 1.0, 1.0, 1.0); // this color will "tint" the image

    // enable texture mapping
    glEnable(GL_TEXTURE_2D);

    // bind a texture to OpenGL primitives
    glBindTexture(GL_TEXTURE_2D, textureId01); // imageSample (a bird)

    
    //left side trees
    glBegin(GL_QUADS);

    // For each vertex, assign texture coordinate before vertex coordinate.
    glTexCoord2d(0.0, 0.0); // these are "percentage" of the image
    glVertex2i(locX1, locY1); // these are actual pixel coordinates on screen

    glTexCoord2d(1.0, 0.0);
    glVertex2i(locX1 + xSize, locY1);

    glTexCoord2d(1.0, 1.0);
    glVertex2i(locX1 + xSize, locY1 + ySize); // kept xSize and ySize for this purpose

    glTexCoord2d(0.0, 1.0);
    glVertex2i(locX1, locY1 + ySize);

    glEnd();
    
    glBegin(GL_QUADS);

    glTexCoord2d(0.0, 0.0); // these are "percentage" of the image
    glVertex2i(locX2, locY2); // these are actual pixel coordinates on screen

    glTexCoord2d(1.0, 0.0);
    glVertex2i(locX2 + xSize, locY2);

    glTexCoord2d(1.0, 1.0);
    glVertex2i(locX2 + xSize, locY2 + ySize); // kept xSize and ySize for this purpose

    glTexCoord2d(0.0, 1.0);
    glVertex2i(locX2, locY2 + ySize);

    glEnd();

    glBegin(GL_QUADS);

    glTexCoord2d(0.0, 0.0); // these are "percentage" of the image
    glVertex2i(locX3, locY3); // these are actual pixel coordinates on screen

    glTexCoord2d(1.0, 0.0);
    glVertex2i(locX3 + xSize, locY3);

    glTexCoord2d(1.0, 1.0);
    glVertex2i(locX3 + xSize, locY3 + ySize); // kept xSize and ySize for this purpose

    glTexCoord2d(0.0, 1.0);
    glVertex2i(locX3, locY3 + ySize);

    glEnd();

    glBegin(GL_QUADS);

    glTexCoord2d(0.0, 0.0); // these are "percentage" of the image
    glVertex2i(locX4, locY4); // these are actual pixel coordinates on screen

    glTexCoord2d(1.0, 0.0);
    glVertex2i(locX4 + xSize, locY4);

    glTexCoord2d(1.0, 1.0);
    glVertex2i(locX4 + xSize, locY4 + ySize); // kept xSize and ySize for this purpose

    glTexCoord2d(0.0, 1.0);
    glVertex2i(locX4, locY4 + ySize);

    glEnd();

    glBegin(GL_QUADS);

    glTexCoord2d(0.0, 0.0); // these are "percentage" of the image
    glVertex2i(locX5, locY5); // these are actual pixel coordinates on screen

    glTexCoord2d(1.0, 0.0);
    glVertex2i(locX5 + xSize, locY5);

    glTexCoord2d(1.0, 1.0);
    glVertex2i(locX5 + xSize, locY5 + ySize); // kept xSize and ySize for this purpose

    glTexCoord2d(0.0, 1.0);
    glVertex2i(locX5, locY5 + ySize);

    glEnd();
    
    glBegin(GL_QUADS);

    glTexCoord2d(0.0, 0.0); // these are "percentage" of the image
    glVertex2i(locX6, locY6); // these are actual pixel coordinates on screen

    glTexCoord2d(1.0, 0.0);
    glVertex2i(locX6 + xSize, locY6);

    glTexCoord2d(1.0, 1.0);
    glVertex2i(locX6 + xSize, locY6 + ySize); // kept xSize and ySize for this purpose

    glTexCoord2d(0.0, 1.0);
    glVertex2i(locX6, locY6 + ySize);

    glEnd();
    
    
    
    // right side trees
    glBegin(GL_QUADS);

    // For each vertex, assign texture coordinate before vertex coordinate.
    glTexCoord2d(0.0, 0.0); // these are "percentage" of the image
    glVertex2i(locX7, locY7); // these are actual pixel coordinates on screen

    glTexCoord2d(1.0, 0.0);
    glVertex2i(locX7 + xSize, locY7);

    glTexCoord2d(1.0, 1.0);
    glVertex2i(locX7 + xSize, locY7 + ySize); // kept xSize and ySize for this purpose

    glTexCoord2d(0.0, 1.0);
    glVertex2i(locX7, locY7 + ySize);

    glEnd();
    
    glBegin(GL_QUADS);

    glTexCoord2d(0.0, 0.0); // these are "percentage" of the image
    glVertex2i(locX8, locY8); // these are actual pixel coordinates on screen

    glTexCoord2d(1.0, 0.0);
    glVertex2i(locX8 + xSize, locY8);

    glTexCoord2d(1.0, 1.0);
    glVertex2i(locX8 + xSize, locY8 + ySize); // kept xSize and ySize for this purpose

    glTexCoord2d(0.0, 1.0);
    glVertex2i(locX8, locY8 + ySize);

    glEnd();

    glBegin(GL_QUADS);

    glTexCoord2d(0.0, 0.0); // these are "percentage" of the image
    glVertex2i(locX9, locY9); // these are actual pixel coordinates on screen

    glTexCoord2d(1.0, 0.0);
    glVertex2i(locX9 + xSize, locY9);

    glTexCoord2d(1.0, 1.0);
    glVertex2i(locX9 + xSize, locY9 + ySize); // kept xSize and ySize for this purpose

    glTexCoord2d(0.0, 1.0);
    glVertex2i(locX9, locY9 + ySize);

    glEnd();

    glBegin(GL_QUADS);

    glTexCoord2d(0.0, 0.0); // these are "percentage" of the image
    glVertex2i(locX10, locY10); // these are actual pixel coordinates on screen

    glTexCoord2d(1.0, 0.0);
    glVertex2i(locX10 + xSize, locY10);

    glTexCoord2d(1.0, 1.0);
    glVertex2i(locX10 + xSize, locY10 + ySize); // kept xSize and ySize for this purpose

    glTexCoord2d(0.0, 1.0);
    glVertex2i(locX10, locY10 + ySize);

    glEnd();

    glBegin(GL_QUADS);

    glTexCoord2d(0.0, 0.0); // these are "percentage" of the image
    glVertex2i(locX11, locY11); // these are actual pixel coordinates on screen

    glTexCoord2d(1.0, 0.0);
    glVertex2i(locX11 + xSize, locY11);

    glTexCoord2d(1.0, 1.0);
    glVertex2i(locX11 + xSize, locY11 + ySize); // kept xSize and ySize for this purpose

    glTexCoord2d(0.0, 1.0);
    glVertex2i(locX11, locY11 + ySize);

    glEnd();
    
    glBegin(GL_QUADS);

    glTexCoord2d(0.0, 0.0); // these are "percentage" of the image
    glVertex2i(locX12, locY12); // these are actual pixel coordinates on screen

    glTexCoord2d(1.0, 0.0);
    glVertex2i(locX12 + xSize, locY12);

    glTexCoord2d(1.0, 1.0);
    glVertex2i(locX12 + xSize, locY12 + ySize); // kept xSize and ySize for this purpose

    glTexCoord2d(0.0, 1.0);
    glVertex2i(locX12, locY12 + ySize);

    glEnd();
}

void tree::accel(){
    if (active) {
        locY1 += tree_step; locY2 += tree_step;locY3 += tree_step;locY4 += tree_step;locY5 += tree_step;locY6 += tree_step;
        locY7 += tree_step; locY8 += tree_step;locY9 += tree_step;locY10 += tree_step;locY11 += tree_step;locY12 += tree_step;
        if (locY1 > bound){
            locY1 = -80;}
        if (locY2 > bound){
            locY2 = -80;}
        if (locY3 > bound){
            locY3 = -80;}
        if (locY4 > bound){
            locY4 = -80;}
        if (locY5 > bound){
            locY5 = -80;}
        if (locY6 > bound){
            locY6 = -80;}
        if (locY7 > bound){
            locY7 = -80;}
        if (locY8 > bound){
            locY8 = -80;}
        if (locY9 > bound){
            locY9 = -80;}
        if (locY10 > bound){
            locY10 = -80;}
        if (locY11 > bound){
            locY11 = -80;}
        if (locY12 > bound){
            locY12 = -80;}
        tree_step+=0.1*2;
    }
}

void road::paint(){
    
    glColor3ub(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2d((locX1-0.7)*SCALE, (locY1-2.5)*SCALE);
    glVertex2d((locX1+0.7)*SCALE, (locY1-2.5)*SCALE);
    glVertex2d((locX1+0.7)*SCALE, (locY1+2.5)*SCALE);
    glVertex2d((locX1-0.7)*SCALE, (locY1+2.5)*SCALE);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex2d((locX2-0.7)*SCALE, (locY2-2.5)*SCALE);
    glVertex2d((locX2+0.7)*SCALE, (locY2-2.5)*SCALE);
    glVertex2d((locX2+0.7)*SCALE, (locY2+2.5)*SCALE);
    glVertex2d((locX2-0.7)*SCALE, (locY2+2.5)*SCALE);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d((locX3-0.7)*SCALE, (locY3-2.5)*SCALE);
    glVertex2d((locX3+0.7)*SCALE, (locY3-2.5)*SCALE);
    glVertex2d((locX3+0.7)*SCALE, (locY3+2.5)*SCALE);
    glVertex2d((locX3-0.7)*SCALE, (locY3+2.5)*SCALE);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d((locX4-0.7)*SCALE, (locY4-2.5)*SCALE);
    glVertex2d((locX4+0.7)*SCALE, (locY4-2.5)*SCALE);
    glVertex2d((locX4+0.7)*SCALE, (locY4+2.5)*SCALE);
    glVertex2d((locX4-0.7)*SCALE, (locY4+2.5)*SCALE);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d((locX5-0.7)*SCALE, (locY5-2.5)*SCALE);
    glVertex2d((locX5+0.7)*SCALE, (locY5-2.5)*SCALE);
    glVertex2d((locX5+0.7)*SCALE, (locY5+2.5)*SCALE);
    glVertex2d((locX5-0.7)*SCALE, (locY5+2.5)*SCALE);
    glEnd();

    glBegin(GL_QUADS); //left
    glVertex2d((locX6-0.2)*SCALE, (locY6-25)*SCALE);
    glVertex2d((locX6+0.2)*SCALE, (locY6-25)*SCALE);
    glVertex2d((locX6+0.2)*SCALE, (locY6+25)*SCALE);
    glVertex2d((locX6-0.2)*SCALE, (locY6+25)*SCALE);
    glEnd();
    
    glBegin(GL_QUADS); //right
    glVertex2d((locX7-0.2)*SCALE, (locY7-25)*SCALE);
    glVertex2d((locX7+0.2)*SCALE, (locY7-25)*SCALE);
    glVertex2d((locX7+0.2)*SCALE, (locY7+25)*SCALE);
    glVertex2d((locX7-0.2)*SCALE, (locY7+25)*SCALE);
    glEnd();
}

void road::paint_cross(){
    glColor3ub(255, 255, 255);
    glBegin(GL_QUADS); //right
    glVertex2d(0*SCALE, -20*SCALE);
    glVertex2d((0+40)*SCALE, -20*SCALE);
    glVertex2d((Cross_locX+40)*SCALE, Cross_locY*SCALE);
    glVertex2d(Cross_locX*SCALE, Cross_locY*SCALE);
    glEnd();
    
    glColor3ub(0, 0, 0);
    glBegin(GL_QUADS); //right
    glVertex2d((locX7-0.2)*SCALE, (Cross_locY-0.5)*SCALE);
    glVertex2d((locX7+15)*SCALE, (Cross_locY-0.5)*SCALE);
    glVertex2d((locX7+15)*SCALE, (Cross_locY)*SCALE);
    glVertex2d((locX7-0.2)*SCALE, (Cross_locY)*SCALE);
    glEnd();

    glBegin(GL_QUADS); //left
    glVertex2d(Cross_locX, (Cross_locY-0.5)*SCALE);
    glVertex2d((locX6+0.2)*SCALE, (Cross_locY-0.5)*SCALE);
    glVertex2d((locX6+0.2)*SCALE, (Cross_locY)*SCALE);
    glVertex2d(Cross_locX, (Cross_locY)*SCALE);
    glEnd();
}

void road::paint_other_half_cross(){
    float road_width = 17.0;
    static float side_Y = -0.5;
    static float tree1_x = 35, tree_y = -25*SCALE/2, tree2_x = 685;
    glColor3ub(0, 0, 0);
    glBegin(GL_QUADS); //right
    glVertex2d((locX7-0.2)*SCALE, (Cross_locY-0.5-road_width)*SCALE);
    glVertex2d((locX7+15)*SCALE, (Cross_locY-0.5-road_width)*SCALE);
    glVertex2d((locX7+15)*SCALE, (Cross_locY-road_width)*SCALE);
    glVertex2d((locX7-0.2)*SCALE, (Cross_locY-road_width)*SCALE);
    glEnd();
    
    glBegin(GL_QUADS); //left
    glVertex2d(Cross_locX, (Cross_locY-0.5-road_width)*SCALE);
    glVertex2d((locX6+0.2)*SCALE, (Cross_locY-0.5-road_width)*SCALE);
    glVertex2d((locX6+0.2)*SCALE, (Cross_locY-road_width)*SCALE);
    glVertex2d(Cross_locX, (Cross_locY-road_width)*SCALE);
    glEnd();
    
    glBegin(GL_QUADS); //left
    glVertex2d((locX6-0.2)*SCALE, (side_Y-25)*SCALE);
    glVertex2d((locX6+0.2)*SCALE, (side_Y-25)*SCALE);
    glVertex2d((locX6+0.2)*SCALE, (side_Y-5.5)*SCALE);
    glVertex2d((locX6-0.2)*SCALE, (side_Y-5.5)*SCALE);
    glEnd();
    
    glBegin(GL_QUADS); //right
    glVertex2d((locX7-0.2)*SCALE, (side_Y-25)*SCALE);
    glVertex2d((locX7+0.2)*SCALE, (side_Y-25)*SCALE);
    glVertex2d((locX7+0.2)*SCALE, (side_Y-5.5)*SCALE);
    glVertex2d((locX7-0.2)*SCALE, (side_Y-5.5)*SCALE);
    glEnd();
    
    YsRawPngDecoder pngTemp;
    pngTemp.Decode("Tree.png");

    double scale1 = 0.11;
    int xSize = pngTemp.wid * scale1; // need for later
    int ySize = pngTemp.hei * scale1;

    GLuint textureId01; // this will be used as texture identifier for the second PNG (DON'T LOSE IT)

    glGenTextures(1, &textureId01); // Reserve texture identifier for other PNG
    glBindTexture(GL_TEXTURE_2D, textureId01); // Making the texture identifier current (or bring it to the deck)

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pngTemp.wid, pngTemp.hei, 0, GL_RGBA, GL_UNSIGNED_BYTE, pngTemp.rgba);

    int wid, hei;
    FsGetWindowSize(wid, hei); // nice little function

    // in order for textures to show, you must create a projection
    glViewport(0, 0, wid, hei);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor4d(1.0, 1.0, 1.0, 1.0); // this color will "tint" the image

    // enable texture mapping
    glEnable(GL_TEXTURE_2D);

    // bind a texture to OpenGL primitives
    glBindTexture(GL_TEXTURE_2D, textureId01); // imageSample (a bird)

    
    //left side trees
    glBegin(GL_QUADS);

    // For each vertex, assign texture coordinate before vertex coordinate.
    glTexCoord2d(0.0, 0.0); // these are "percentage" of the image
    glVertex2i(tree1_x, tree_y); // these are actual pixel coordinates on screen

    glTexCoord2d(1.0, 0.0);
    glVertex2i(tree1_x + xSize, tree_y);

    glTexCoord2d(1.0, 1.0);
    glVertex2i(tree1_x + xSize, tree_y + ySize); // kept xSize and ySize for this purpose

    glTexCoord2d(0.0, 1.0);
    glVertex2i(tree1_x, tree_y + ySize);

    glEnd();
    
    glBegin(GL_QUADS);

    // For each vertex, assign texture coordinate before vertex coordinate.
    glTexCoord2d(0.0, 0.0); // these are "percentage" of the image
    glVertex2i(tree2_x, tree_y); // these are actual pixel coordinates on screen

    glTexCoord2d(1.0, 0.0);
    glVertex2i(tree2_x + xSize, tree_y);

    glTexCoord2d(1.0, 1.0);
    glVertex2i(tree2_x + xSize, tree_y + ySize); // kept xSize and ySize for this purpose

    glTexCoord2d(0.0, 1.0);
    glVertex2i(tree2_x, tree_y + ySize);

    glEnd();
    
    glColor3ub(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2d((locX1-0.7)*SCALE, (side_Y-10)*SCALE);
    glVertex2d((locX1+0.7)*SCALE, (side_Y-10)*SCALE);
    glVertex2d((locX1+0.7)*SCALE, (side_Y+5-10)*SCALE);
    glVertex2d((locX1-0.7)*SCALE, (side_Y+5-10)*SCALE);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex2d((locX2-0.7)*SCALE, (side_Y-10)*SCALE);
    glVertex2d((locX2+0.7)*SCALE, (side_Y-10)*SCALE);
    glVertex2d((locX2+0.7)*SCALE, (side_Y+5-10)*SCALE);
    glVertex2d((locX2-0.7)*SCALE, (side_Y+5-10)*SCALE);
    glEnd();
    
    if(cross_active){
        side_Y+=road_step;
        tree_y+=SCALE/2;
    }
}

void road::move_cross(){if(cross_active)Cross_locY+=road_step;}

void road::move(){
    if (active) {
        locY1 += road_step;locY2 += road_step;locY3 += road_step;locY4 += road_step;locY5 += road_step;
        if (locY1 > bound){
            locY1 = -2.5;}
        if (locY2 > bound){
            locY2 = -2.5;}
        if (locY3 > bound){
            locY3 = -2.5;}
        if (locY4 > bound){
            locY4 = -2.5;}
        if (locY5 > bound){
            locY5 = -2.5;}
    }
}

void road::paint_strip_horz(){
    glColor3ub(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2d((horz_locX)*SCALE, (horz_locY)*SCALE);
    glVertex2d((horz_locX+5)*SCALE, (horz_locY)*SCALE);
    glVertex2d((horz_locX+5)*SCALE, (horz_locY+1.4)*SCALE);
    glVertex2d((horz_locX)*SCALE, (horz_locY+1.4)*SCALE);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d((horz_locX+10)*SCALE, (horz_locY)*SCALE);
    glVertex2d((horz_locX+5+10)*SCALE, (horz_locY)*SCALE);
    glVertex2d((horz_locX+5+10)*SCALE, (horz_locY+1.4)*SCALE);
    glVertex2d((horz_locX+10)*SCALE, (horz_locY+1.4)*SCALE);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2d((horz_locX+20)*SCALE, (horz_locY)*SCALE);
    glVertex2d((horz_locX+5+20)*SCALE, (horz_locY)*SCALE);
    glVertex2d((horz_locX+5+20)*SCALE, (horz_locY+1.4)*SCALE);
    glVertex2d((horz_locX+20)*SCALE, (horz_locY+1.4)*SCALE);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex2d((horz_locX+31)*SCALE, (horz_locY)*SCALE);
    glVertex2d((horz_locX+5+31)*SCALE, (horz_locY)*SCALE);
    glVertex2d((horz_locX+5+31)*SCALE, (horz_locY+1.4)*SCALE);
    glVertex2d((horz_locX+31)*SCALE, (horz_locY+1.4)*SCALE);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex2d((horz_locX+40)*SCALE, (horz_locY)*SCALE);
    glVertex2d((horz_locX+5+40)*SCALE, (horz_locY)*SCALE);
    glVertex2d((horz_locX+5+40)*SCALE, (horz_locY+1.4)*SCALE);
    glVertex2d((horz_locX+40)*SCALE, (horz_locY+1.4)*SCALE);
    glEnd();
}

void road::paint_zebra_crossing(){
    glColor3ub(244, 187, 68);
    glBegin(GL_QUADS);
    glVertex2d((zebra_locX-0.5-2.5)*SCALE, (zebra_locY-2.5)*SCALE);
    glVertex2d((zebra_locX+0.5-2.5)*SCALE, (zebra_locY-2.5)*SCALE);
    glVertex2d((zebra_locX+0.5-2.5)*SCALE, (zebra_locY+2.5)*SCALE);
    glVertex2d((zebra_locX-0.5-2.5)*SCALE, (zebra_locY+2.5)*SCALE);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex2d((zebra_locX-0.5+3-2.5)*SCALE, (zebra_locY-2.5)*SCALE);
    glVertex2d((zebra_locX+0.5+3-2.5)*SCALE, (zebra_locY-2.5)*SCALE);
    glVertex2d((zebra_locX+0.5+3-2.5)*SCALE, (zebra_locY+2.5)*SCALE);
    glVertex2d((zebra_locX-0.5+3-2.5)*SCALE, (zebra_locY+2.5)*SCALE);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex2d((zebra_locX-0.5+6-2.5)*SCALE, (zebra_locY-2.5)*SCALE);
    glVertex2d((zebra_locX+0.5+6-2.5)*SCALE, (zebra_locY-2.5)*SCALE);
    glVertex2d((zebra_locX+0.5+6-2.5)*SCALE, (zebra_locY+2.5)*SCALE);
    glVertex2d((zebra_locX-0.5+6-2.5)*SCALE, (zebra_locY+2.5)*SCALE);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex2d((zebra_locX-0.5+9-2.5)*SCALE, (zebra_locY-2.5)*SCALE);
    glVertex2d((zebra_locX+0.5+9-2.5)*SCALE, (zebra_locY-2.5)*SCALE);
    glVertex2d((zebra_locX+0.5+9-2.5)*SCALE, (zebra_locY+2.5)*SCALE);
    glVertex2d((zebra_locX-0.5+9-2.5)*SCALE, (zebra_locY+2.5)*SCALE);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex2d((zebra_locX-0.5+12-2.5)*SCALE, (zebra_locY-2.5)*SCALE);
    glVertex2d((zebra_locX+0.5+12-2.5)*SCALE, (zebra_locY-2.5)*SCALE);
    glVertex2d((zebra_locX+0.5+12-2.5)*SCALE, (zebra_locY+2.5)*SCALE);
    glVertex2d((zebra_locX-0.5+12-2.5)*SCALE, (zebra_locY+2.5)*SCALE);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex2d((zebra_locX-0.5+15-2.5)*SCALE, (zebra_locY-2.5)*SCALE);
    glVertex2d((zebra_locX+0.5+15-2.5)*SCALE, (zebra_locY-2.5)*SCALE);
    glVertex2d((zebra_locX+0.5+15-2.5)*SCALE, (zebra_locY+2.5)*SCALE);
    glVertex2d((zebra_locX-0.5+15-2.5)*SCALE, (zebra_locY+2.5)*SCALE);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex2d((zebra_locX-0.5+18-2.5)*SCALE, (zebra_locY-2.5)*SCALE);
    glVertex2d((zebra_locX+0.5+18-2.5)*SCALE, (zebra_locY-2.5)*SCALE);
    glVertex2d((zebra_locX+0.5+18-2.5)*SCALE, (zebra_locY+2.5)*SCALE);
    glVertex2d((zebra_locX-0.5+18-2.5)*SCALE, (zebra_locY+2.5)*SCALE);
    glEnd();
    
    glBegin(GL_QUADS);
    glVertex2d((zebra_locX-0.5+21-2.5)*SCALE, (zebra_locY-2.5)*SCALE);
    glVertex2d((zebra_locX+0.5+21-2.5)*SCALE, (zebra_locY-2.5)*SCALE);
    glVertex2d((zebra_locX+0.5+21-2.5)*SCALE, (zebra_locY+2.5)*SCALE);
    glVertex2d((zebra_locX-0.5+21-2.5)*SCALE, (zebra_locY+2.5)*SCALE);
    glEnd();
}


void road::paint_arrow(){
    glColor3ub(255, 0, 0);
    glBegin(GL_LINES);
    glVertex2i(400, 170);
     glVertex2i(500, 170);
    glEnd();
    
    glBegin(GL_LINES);
    glVertex2i(500, 170);
    glVertex2i(490, 160);
    glEnd();
    
    glBegin(GL_LINES);
    glVertex2i(500, 170);
    glVertex2i(490, 180);
    glEnd();
    
    glBegin(GL_LINES);
    glVertex2i(400, 170);
    glVertex2i(300, 170);
    glEnd();
    
    glBegin(GL_LINES);
    glVertex2i(300, 170);
    glVertex2i(310, 160);
    glEnd();
    
    glBegin(GL_LINES);
    glVertex2i(300, 170);
    glVertex2i(310, 180);
    glEnd();
    
    glBegin(GL_LINES);
    glVertex2i(400, 170);
    glVertex2i(400, 70);
    glEnd();
    
    glBegin(GL_LINES);
    glVertex2i(400, 70);
    glVertex2i(390, 80);
    glEnd();
    
    glBegin(GL_LINES);
    glVertex2i(400, 70);
    glVertex2i(410, 80);
    glEnd();
}

void road::accel(){
    if (active) {
        locY1 += road_step;locY2 += road_step;locY3 += road_step;locY4 += road_step;locY5 += road_step;
        if (locY1 > bound){
            locY1 = -2.5;}
        if (locY2 > bound){
            locY2 = -2.5;}
        if (locY3 > bound){
            locY3 = -2.5;}
        if (locY4 > bound){
            locY4 = -2.5;}
        if (locY5 > bound){
            locY5 = -2.5;}
        road_step+=0.004*2;
    }
}

void car::paint(int time){
    static float angle = 45.0; //deg
    float rad = angle*PI/180;
    YsRawPngDecoder pngTemp;
    pngTemp.Decode("Car.png");
    
    double scale1 = 0.5;
    int xSize = pngTemp.wid * scale1; // need for later
    int ySize = pngTemp.hei * scale1;
    
    GLuint textureId01; // this will be used as texture identifier for the second PNG (DON'T LOSE IT)
    
    glGenTextures(1, &textureId01); // Reserve texture identifier for other PNG
    glBindTexture(GL_TEXTURE_2D, textureId01); // Making the texture identifier current (or bring it to the deck)
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pngTemp.wid, pngTemp.hei, 0, GL_RGBA, GL_UNSIGNED_BYTE, pngTemp.rgba);
    
    int wid, hei;
    FsGetWindowSize(wid, hei); // nice little function
    
    // in order for textures to show, you must create a projection
    glViewport(0, 0, wid, hei);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor4d(1.0, 1.0, 1.0, 1.0); // this color will "tint" the image
    
    // enable texture mapping
    glEnable(GL_TEXTURE_2D);
    
    // bind a texture to OpenGL primitives
    glBindTexture(GL_TEXTURE_2D, textureId01); // imageSample (a bird)
    
    if (time<420){
        glBegin(GL_QUADS);
        
        glTexCoord2d(0.0, 0.0);
        glVertex2d(locX1*CAR_SCALE + xSize * cos(rad), locY1*CAR_SCALE - ySize * sin(rad));
        
        glTexCoord2d(1.0, 0.0);
        glVertex2d(locX1*CAR_SCALE + xSize * cos(rad + PI/2), locY1*CAR_SCALE - ySize * sin(rad + PI/2));
        
        glTexCoord2d(1.0, 1.0);
        glVertex2d(locX1*CAR_SCALE + xSize * cos(rad + PI), locY1*CAR_SCALE - ySize * sin(rad + PI));
        
        glTexCoord2d(0.0, 1.0);
        glVertex2d(locX1*CAR_SCALE + xSize * cos(rad - PI/2), locY1*CAR_SCALE - ySize * sin(rad - PI/2));
        glEnd();
        glDisable(GL_BLEND);
    }
    
    if (time>=317){
        if (angle >-45){angle -= 5;}
    }
    
    if (time>=420){
        int xSize1 = xSize*1.5, ySize1 = ySize*1.5;
        glBegin(GL_QUADS);
        
        // For each vertex, assign texture coordinate before vertex coordinate.
        glTexCoord2d(0.0, 0.0); // these are "percentage" of the image
        glVertex2i((locX1-30)*CAR_SCALE, locY1*CAR_SCALE); // these are actual pixel coordinates on screen
        
        glTexCoord2d(1.0, 0.0);
        glVertex2i(((locX1-30)*CAR_SCALE + xSize1), locY1*CAR_SCALE);
        
        glTexCoord2d(1.0, 1.0);
        glVertex2i(((locX1-30)*CAR_SCALE + xSize1), (locY1*CAR_SCALE + ySize1)); // kept xSize and ySize for this purpose
        
        glTexCoord2d(0.0, 1.0);
        glVertex2i((locX1-30)*CAR_SCALE, (locY1*CAR_SCALE + ySize1));
        
        glEnd();
    }
}

    
void trafficlight::paint_red(){
    YsRawPngDecoder pngTemp;
    pngTemp.Decode("red_light.png");
    
    double scale1 = 0.8;
    int xSize = pngTemp.wid * scale1; // need for later
    int ySize = pngTemp.hei * scale1;
    
    GLuint textureId01; // this will be used as texture identifier for the second PNG (DON'T LOSE IT)
    
    glGenTextures(1, &textureId01); // Reserve texture identifier for other PNG
    glBindTexture(GL_TEXTURE_2D, textureId01); // Making the texture identifier current (or bring it to the deck)
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pngTemp.wid, pngTemp.hei, 0, GL_RGBA, GL_UNSIGNED_BYTE, pngTemp.rgba);
    
    int wid, hei;
    FsGetWindowSize(wid, hei); // nice little function
    
    // in order for textures to show, you must create a projection
    glViewport(0, 0, wid, hei);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor4d(1.0, 1.0, 1.0, 1.0); // this color will "tint" the image
    
    // enable texture mapping
    glEnable(GL_TEXTURE_2D);
    
    // bind a texture to OpenGL primitives
    glBindTexture(GL_TEXTURE_2D, textureId01); // imageSample (a bird)
    
    
    //left side trees
    glBegin(GL_QUADS);
    
    // For each vertex, assign texture coordinate before vertex coordinate.
    glTexCoord2d(0.0, 0.0); // these are "percentage" of the image
    glVertex2i(locX*LIGHT_SCALE, locY_yellow*LIGHT_SCALE); // these are actual pixel coordinates on screen
    
    glTexCoord2d(1.0, 0.0);
    glVertex2i((locX + xSize)*LIGHT_SCALE, locY_yellow*LIGHT_SCALE);
    
    glTexCoord2d(1.0, 1.0);
    glVertex2i((locX + xSize)*LIGHT_SCALE, (locY_yellow + ySize)*LIGHT_SCALE); // kept xSize and ySize for this purpose
    
    glTexCoord2d(0.0, 1.0);
    glVertex2i(locX*LIGHT_SCALE, (locY_yellow + ySize)*LIGHT_SCALE);
    
    glEnd();
}

void trafficlight::paint_yellow(){
    YsRawPngDecoder pngTemp;
    pngTemp.Decode("yellow_light.png");
    
    double scale1 = 0.8;
    int xSize = pngTemp.wid * scale1; // need for later
    int ySize = pngTemp.hei * scale1;
    
    GLuint textureId01; // this will be used as texture identifier for the second PNG (DON'T LOSE IT)
    
    glGenTextures(1, &textureId01); // Reserve texture identifier for other PNG
    glBindTexture(GL_TEXTURE_2D, textureId01); // Making the texture identifier current (or bring it to the deck)
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pngTemp.wid, pngTemp.hei, 0, GL_RGBA, GL_UNSIGNED_BYTE, pngTemp.rgba);
    
    int wid, hei;
    FsGetWindowSize(wid, hei); // nice little function
    
    // in order for textures to show, you must create a projection
    glViewport(0, 0, wid, hei);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor4d(1.0, 1.0, 1.0, 1.0); // this color will "tint" the image
    
    // enable texture mapping
    glEnable(GL_TEXTURE_2D);
    
    // bind a texture to OpenGL primitives
    glBindTexture(GL_TEXTURE_2D, textureId01); // imageSample (a bird)
    
    
    //left side trees
    glBegin(GL_QUADS);
    
    // For each vertex, assign texture coordinate before vertex coordinate.
    glTexCoord2d(0.0, 0.0); // these are "percentage" of the image
    glVertex2i(locX*LIGHT_SCALE, locY_yellow*LIGHT_SCALE); // these are actual pixel coordinates on screen
    
    glTexCoord2d(1.0, 0.0);
    glVertex2i((locX + xSize)*LIGHT_SCALE, locY_yellow*LIGHT_SCALE);
    
    glTexCoord2d(1.0, 1.0);
    glVertex2i((locX + xSize)*LIGHT_SCALE, (locY_yellow + ySize)*LIGHT_SCALE); // kept xSize and ySize for this purpose
    
    glTexCoord2d(0.0, 1.0);
    glVertex2i(locX*LIGHT_SCALE, (locY_yellow + ySize)*LIGHT_SCALE);
    
    glEnd();
}

void trafficlight::paint_green(){
    YsRawPngDecoder pngTemp;
    pngTemp.Decode("green_light.png");
    
    double scale1 = 0.8;
    int xSize = pngTemp.wid * scale1; // need for later
    int ySize = pngTemp.hei * scale1;
    
    GLuint textureId01; // this will be used as texture identifier for the second PNG (DON'T LOSE IT)
    
    glGenTextures(1, &textureId01); // Reserve texture identifier for other PNG
    glBindTexture(GL_TEXTURE_2D, textureId01); // Making the texture identifier current (or bring it to the deck)
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pngTemp.wid, pngTemp.hei, 0, GL_RGBA, GL_UNSIGNED_BYTE, pngTemp.rgba);
    
    int wid, hei;
    FsGetWindowSize(wid, hei); // nice little function
    
    // in order for textures to show, you must create a projection
    glViewport(0, 0, wid, hei);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor4d(1.0, 1.0, 1.0, 1.0); // this color will "tint" the image
    
    // enable texture mapping
    glEnable(GL_TEXTURE_2D);
    
    // bind a texture to OpenGL primitives
    glBindTexture(GL_TEXTURE_2D, textureId01); // imageSample (a bird)
    
    
    //left side trees
    glBegin(GL_QUADS);
    
    // For each vertex, assign texture coordinate before vertex coordinate.
    glTexCoord2d(0.0, 0.0); // these are "percentage" of the image
    glVertex2i(locX*LIGHT_SCALE, locY_yellow*LIGHT_SCALE); // these are actual pixel coordinates on screen
    
    glTexCoord2d(1.0, 0.0);
    glVertex2i((locX + xSize)*LIGHT_SCALE, locY_yellow*LIGHT_SCALE);
    
    glTexCoord2d(1.0, 1.0);
    glVertex2i((locX + xSize)*LIGHT_SCALE, (locY_yellow + ySize)*LIGHT_SCALE); // kept xSize and ySize for this purpose
    
    glTexCoord2d(0.0, 1.0);
    glVertex2i(locX*LIGHT_SCALE, (locY_yellow + ySize)*LIGHT_SCALE);
    
    glEnd();
}

void trafficlight::move_yellow(){if (active){locY_yellow+=light_step;}}

void people::paint(){
    static float angle = -135.0; //deg
    float rad = angle*PI/180;
    
    YsRawPngDecoder pngTemp;
    pngTemp.Decode("matchstick.png");
    if (locX<520){
        pngTemp.Flip();
    }
    double scale1 = 0.25;
    int xSize = pngTemp.wid * scale1; // need for later
    int ySize = pngTemp.hei * scale1;
    
    double scale2 = 0.17;
    static float xSize1 = pngTemp.wid * scale2; // need for later
    static float ySize1 = pngTemp.hei * scale2;
    
    GLuint textureId01; // this will be used as texture identifier for the second PNG (DON'T LOSE IT)
    
    glGenTextures(1, &textureId01); // Reserve texture identifier for other PNG
    glBindTexture(GL_TEXTURE_2D, textureId01); // Making the texture identifier current (or bring it to the deck)
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pngTemp.wid, pngTemp.hei, 0, GL_RGBA, GL_UNSIGNED_BYTE, pngTemp.rgba);
    
    int wid, hei;
    FsGetWindowSize(wid, hei); // nice little function
    
    // in order for textures to show, you must create a projection
    glViewport(0, 0, wid, hei);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor4d(1.0, 1.0, 1.0, 1.0); // this color will "tint" the image
    
    // enable texture mapping
    glEnable(GL_TEXTURE_2D);
    
    // bind a texture to OpenGL primitives
    glBindTexture(GL_TEXTURE_2D, textureId01); // imageSample (a bird)
    
    if (locX >= 530){
        glBegin(GL_QUADS);
        // For each vertex, assign texture coordinate before vertex coordinate.
        glTexCoord2d(0.0, 0.0); // these are "percentage" of the image
        glVertex2i(locX, locY); // these are actual pixel coordinates on screen
        
        glTexCoord2d(1.0, 0.0);
        glVertex2i((locX + xSize), locY);
        
        glTexCoord2d(1.0, 1.0);
        glVertex2i((locX + xSize), (locY + ySize)); // kept xSize and ySize for this purpose
        
        glTexCoord2d(0.0, 1.0);
        glVertex2i(locX, (locY + ySize));
        
        glEnd();
    }else{ //collision
        glBegin(GL_QUADS);
        
        glTexCoord2d(0.0, 0.0);
        glVertex2d(locX + xSize1 * cos(rad) + 30, locY - ySize1 * sin(rad)+ 30);
        
        glTexCoord2d(1.0, 0.0);
        glVertex2d(locX + xSize1 * cos(rad + PI/2) + 30, locY - ySize1 * sin(rad + PI/2)+ 30);
        
        glTexCoord2d(1.0, 1.0);
        glVertex2d(locX + xSize1 * cos(rad + PI) + 30, locY - ySize1 * sin(rad + PI)+ 30);
        
        glTexCoord2d(0.0, 1.0);
        glVertex2d(locX + xSize1 * cos(rad - PI/2) + 30, locY - ySize1 * sin(rad - PI/2)+ 30);
        glEnd();
        if (active){
            xSize1*=2; ySize1*=2;
            angle+=45;
        }
    }
    glDisable(GL_BLEND);
}

void speed_limit::paint(){
    YsRawPngDecoder pngTemp;
    pngTemp.Decode("speed_limit.png");
    
    double scale1 = 0.1;
    int xSize = pngTemp.wid * scale1; // need for later
    int ySize = pngTemp.hei * scale1;
    
    GLuint textureId01; // this will be used as texture identifier for the second PNG (DON'T LOSE IT)
    
    glGenTextures(1, &textureId01); // Reserve texture identifier for other PNG
    glBindTexture(GL_TEXTURE_2D, textureId01); // Making the texture identifier current (or bring it to the deck)
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pngTemp.wid, pngTemp.hei, 0, GL_RGBA, GL_UNSIGNED_BYTE, pngTemp.rgba);
    
    int wid, hei;
    FsGetWindowSize(wid, hei); // nice little function
    
    // in order for textures to show, you must create a projection
    glViewport(0, 0, wid, hei);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor4d(1.0, 1.0, 1.0, 1.0); // this color will "tint" the image
    
    // enable texture mapping
    glEnable(GL_TEXTURE_2D);
    
    // bind a texture to OpenGL primitives
    glBindTexture(GL_TEXTURE_2D, textureId01); // imageSample (a bird)
    
    
    //left side trees
    glBegin(GL_QUADS);
    
    // For each vertex, assign texture coordinate before vertex coordinate.
    glTexCoord2d(0.0, 0.0); // these are "percentage" of the image
    glVertex2i(locX, locY); // these are actual pixel coordinates on screen
    
    glTexCoord2d(1.0, 0.0);
    glVertex2i((locX + xSize), locY);
    
    glTexCoord2d(1.0, 1.0);
    glVertex2i((locX + xSize), (locY + ySize)); // kept xSize and ySize for this purpose
    
    glTexCoord2d(0.0, 1.0);
    glVertex2i(locX, (locY + ySize));
    
    glEnd();
}
