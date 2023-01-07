#pragma once
/*
Nestor Gomez
October 18, 2019

Font generator using graphical representation of letters in a PNG file.

Use with my compliments. If you'd like to add a font, I've developed
tools to help you do that. If you develop an additional font, share
with me so that this library grows.

*/
#pragma warning(disable:4996)

#include <vector>
#include "fssimplewindow.h"
#include "yspng.h"
#include "DrawingUtilNG.h"
#include <math.h>

class GraphicFont
{
protected:
	// the location of each letter in the image is stored as:
	// x1 = pixel of left-most position
	// x2 = pixel of right-most position
	// y = pixel of bottom-most position
	struct coords {
		int x1, x2, y;
	};

	int firstLetter = ' ';
	double imageWid, imageHei;  // need them to be type double
	int letterHei;

//	YsRawPngDecoder fontImage;
	std::string dataFileName;
	std::string imageFileName;

	double red, green, blue, alpha;

	GLuint textureID;

	std::vector<coords> fontCoords;

	void drawLetter(char aLetter, double& locX, double& locY,
		double scale, double theta);

	void drawLetter3D(char aLetter,
		DrawingUtilNG::vertexF& v0, DrawingUtilNG::vertexF& upUnitVector, 
		DrawingUtilNG::vertexF& rightUnitVector, double scale);

public:
	GraphicFont() { dataFileName = ""; imageFileName = ""; }

	// function is called after filenames are settled by child classes
	void init();

	int getLetterHeight() { return letterHei; }

	// sets the color (RGV) that the text will be drawn in, 
	// but does NOT set the current color in OpenGL
	void setColorRGB(double r, double g, double b, double a = 1.) {
		red = r; green = g; blue = b; alpha = a;
	}

	// sets the color (HSV) that the text will be drawn in, 
	// but does NOT set the current color in OpenGL
	void setColorHSV(double h, double s, double v, double a = 1.) {
		DrawingUtilNG::hsv2rgb(h, s, v, red, green, blue);
		alpha = a;
	}

	void setFade(double a) { alpha = a; }

	// draws text on screen at location given (lower left of text),
	// at given scale (use negative to mirror image letters),
	// at theta angle given (in degrees CCW, zero is to right),
	// using color set in setColor() function
	void drawText(const std::string& aString, double locX, double locY,
		double scale = 1., double theta = 0., bool centered = false);

	double getWordWidth(const std::string& aString, double scale = 1.);

	// draws text on screen in a circle, centered at location given,
	// with given radius, at given scale (use negative to mirror image letters),
	// starting at theta angle given (in degrees CCW, zero is to right),
	// using color set in setColor() function
	// adjustRadius indicates how many letter heights to adjust radius every
	// revolution (to create spirals), with zero making perfect circle.
	void drawTextCircle(const std::string& aString, double centerX, double centerY,
		double radius, double scale = 1., double theta = 180., double adjustRadius = 0.);

	// draws text on screen at location v0 (lower left of text),
	// using vUp and vRight to define 3D plane,
	// at given scale (use negative to mirror image letters),
	// at theta angle given (in degrees CCW, zero is to right),
	// using color set in setColor() function
	void drawText3D(const std::string& aString,
		DrawingUtilNG::vertexF v0, DrawingUtilNG::vertexF vUp, DrawingUtilNG::vertexF vRight,
		double scale = 1., double theta = 0.); 

	// coming soon ???
	void drawText3DCircle(const std::string& aString,
		DrawingUtilNG::vertexF v0, DrawingUtilNG::vertexF vUp, DrawingUtilNG::vertexF vRight,
		double radius, double scale = 1., double theta = 180., double adjustRadius = 0.)
	{ };

};

class ImpactFont : public GraphicFont {
public:
	ImpactFont() {
		dataFileName = "ImpactFont01.txt";
		imageFileName = "ImpactFont01.png";
		init();
	}
};

class GaramondFont : public GraphicFont {
public:
	GaramondFont() {
		dataFileName = "GaramondFont01.txt";
		imageFileName = "GaramondFont01.png";
		init();
	}
};

class JokermanFont : public GraphicFont {
public:
	JokermanFont() {
		dataFileName = "JokermanFont01.txt";
		imageFileName = "JokermanFont01.png";
		init();
	}
};

class ComicSansFont : public GraphicFont {
public:
	ComicSansFont() {
		dataFileName = "ComicSansFont01.txt";
		imageFileName = "ComicSansFont01.png";
		init();
	}
};

class TimesNewRomanFont : public GraphicFont {
public:
	TimesNewRomanFont() {
		dataFileName = "TimesNewRomanFont01.txt";
		imageFileName = "TimesNewRomanFont01.png";
		init();
	}
};

class OldEnglishFont : public GraphicFont {
public:
	OldEnglishFont() {
		dataFileName = "OldEnglishFont01.txt";
		imageFileName = "OldEnglishFont01.png";
		init();
	}
};
class CourierNewFont : public GraphicFont {
public:
	CourierNewFont() {
		dataFileName = "CourierNewFont01.txt";
		imageFileName = "CourierNewFont01.png";
		init();
	}
};
 
class ArialFont : public GraphicFont {
public:
	ArialFont() {
		dataFileName = "ArialFont01.txt";
		imageFileName = "ArialFont01.png";
		init();
	}
};

