/*
 
Tools for OpenGL drawing
Nestor Gomez, Carnegie Mellon Univ.
24-780 Engr. Computation
Last updated: Nov. 11, 2022

*/

#pragma once
#include <string>
//#include "GraphicFont.h"
class GraphicFont;   // needed because GraphicFont.h includes DrawingUtilNG.h

namespace DrawingUtilNG {
	// this can be used as a vertex coordinates or a 3-D vector definition
	//     (mathematical/physics vector, not data structure vector)
	struct vertexF {
		float x, y, z;
	};

	double getDistance(double x0, double y0, double x1, double y1);
	float getDistance(vertexF v1, vertexF v2);

	// vector functions, hopefully unambiguously named
	float vectorLength(vertexF v0); 
	vertexF getUnitVector(vertexF v0);
	vertexF getUnitVector(vertexF v1, vertexF v2);
	vertexF vectorSum(vertexF v1, vertexF v2);
	vertexF vectorSum(vertexF v1, vertexF v2, vertexF v3);
	vertexF scalarProduct(vertexF v0, float scalar);
	float dotProduct(vertexF v1, vertexF v2);
	vertexF crossProduct(vertexF v1, vertexF v2);
	
	// rotate vector v by theta degrees about vector k
	// uses Rodrigues' Rotation Formula (see Wikipedia)
	vertexF rotateVector(vertexF v, vertexF k, float theta); 

	// draws common shapes, filled in or not
	// if outerSizes are given (not negative) use sizes to create a hole instead of shape
	//    and outerSize to draw the filled-in part.
	void drawCircle(double centerX, double centerY, double sizeX, double sizeY, bool filled,
		double outerSizeX = -1, double outerSizeY = -1);
	void drawRectangle(double x, double y, double sizeX, double sizeY, bool filled,
		double outerSizeX = -1, double outerSizeY = -1);

	// many-pointed start, given outer and inner size, startAngle assures one
	// point is at that angle (used to animate rotation)
	void drawStar(double centerX, double centerY,
		double outerSize, double innerSize, int numbPoints, double startAngle, bool filled);

	// draws self-connecting star gram. (e.g., pentagram, star-of-david, etc)
	void drawStarGram(double centerX, double centerY,
		double size, int numbPoints, int numbSkip, double startAngle, bool filled);
	
	// takes over the screen and allows graphical text input
	bool buildStringFromFsInkey(int key, std::string& currString);

	std::string getStringFromScreen(const std::string& prompt1 = "",
		const std::string& prompt2 = "", const std::string& prompt3 = "");

	//converts a color model from HSV (degrees, 0.-1., 0.-1.) to RGB (3 values 0.-1.)
	bool hsv2rgb(double H, double S, double V,
		double& red, double& green, double& blue);
	
	//converts a color model from RGB (3 values 0.-1.) to HSV (degrees, 0.-1., 0.-1.)
	bool rgb2hsv(double red, double green, double blue, double &H, double &S, double &V);

	//// quick writing with fancy fonts, but requires GLUT library
	//void writeHelvetica(std::string outString, int locX, int locY, int size);
	//void writeTimesRoman(std::string outString, int locX, int locY, int size);

	// draws a box (colored rgb) that increases opacity based on the ratio of currT/totalT
	void coverAndFade(int x1, int y1, int x2, int y2, int totalT, int currT,
		int r = 0, int g = 0, int b = 0);

	// draw 3D shapes
	
	// draws orthogonal cube, with opposing corners at locations v1 and v2
	// use sixColors to see which face is which
	void drawCube(vertexF v1, vertexF v2, bool sixColors = false);

	// draws orthogonal cube, with opposing corners at locations x1,y1,z1 and x2,y2,z2
	// use sixColors to see which face is which and a font to write on the faces
	void drawCube(double x1, double y1, double z1,
		double x2, double y2, double z2, bool sixColors = false, GraphicFont* aFont = NULL);

	// draws 20-faced sphere (still in development)
	void drawSphere(vertexF center, float radius);
	void drawSphere(vertexF center, vertexF northPole);
	void drawSphere(float centerX, float centerY, float centerZ, 
		float northX, float northY, float northZ);
	void drawSphere(float centerX, float centerY, float centerZ, float radius);

	// just does glVertex on the 3D struct
	void drawVertex(vertexF v);// { glVertex3f(v.x, v.y, v.z); }

};
