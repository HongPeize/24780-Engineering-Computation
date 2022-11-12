#include <stdio.h>
#include <algorithm>    // std::max
//#include "GL\glut.h"
 
#include "fssimplewindow.h"
#include <math.h>
#include "DrawingUtilNG.h"


using namespace DrawingUtilNG;

bool DrawingUtilNG::hsv2rgb(double H, double S, double V, double& red, double& green, double& blue)
{
	// using formula from:
	// https://www.rapidtables.com/convert/color/hsv-to-rgb.html

	// adjust H to be 0 <= H <= 360
	H = fabs(fmod(H, 360.));  // note that H=360 is the same as H=0

	double C = V * S;
	double X = C * (1 - fabs(fmod(H / 60., 2) - 1));
	double m = V - C;
	double Rprime, Gprime, Bprime;

	if (H < 0.) {  // unlikely due to adjustment above
		return false;  //  <<< possible exit from function
	}
	else if (H < 60.) {
		Rprime = C;
		Gprime = X;
		Bprime = 0.;
	}
	else if (H < 120.) {
		Rprime = X;
		Gprime = C;
		Bprime = 0.;
	}
	else if (H < 180.) {
		Rprime = 0.;
		Gprime = C;
		Bprime = X;
	}
	else if (H < 240.) {
		Rprime = 0.;
		Gprime = X;
		Bprime = C;
	}
	else if (H < 300.) {
		Rprime = X;
		Gprime = 0.;
		Bprime = C;
	}
	else if (H < 360.) {
		Rprime = C;
		Gprime = 0.;
		Bprime = X;
	}
	else
		return false;  //  <<< possible exit from function

	red = Rprime + m;
	green = Gprime + m;
	blue = Bprime + m;

	return true;
}

bool DrawingUtilNG::buildStringFromFsInkey(int key, std::string& currString)
{
	bool shiftIsOn = FsGetKeyState(FSKEY_SHIFT);

	if (FSKEY_A <= key && key <= FSKEY_Z) {
		int adjustLetter = shiftIsOn ? 0 : 32;
		currString += char(int('A') + key - FSKEY_A + adjustLetter);
	}
	else if (FSKEY_0 <= key && key <= FSKEY_9) {
		if (shiftIsOn) {
			std::string shiftOnNumerals = ")!@#$%^&*(";
			currString += shiftOnNumerals.substr(key - FSKEY_0, 1);
		}
		else
			currString += char(int('0') + key - FSKEY_0);
	}
	else {
		// note that since switch jumps to proper case, 
		// having large number of cases doesn't slow down program
		switch (key) {
		case FSKEY_BS: // remove last character on string
			currString = currString.substr(0, currString.length() - 1);
			break;
		case FSKEY_SPACE:currString += " ";
			break;
		case FSKEY_TAB:currString += "\t";
			break;
		case FSKEY_DOT:
			if (shiftIsOn)
				currString += ">";
			else
				currString += ".";
			break;
		case FSKEY_ENTER: // allows soft line break
			if (shiftIsOn)
				currString += "\n";
			break;
		case FSKEY_COMMA:
			if (shiftIsOn)
				currString += "<";
			else
				currString += ",";
			break;
		case FSKEY_MINUS:
			if (shiftIsOn)
				currString += "_";
			else
				currString += "-";
			break;
		case FSKEY_PLUS:
			if (shiftIsOn)
				currString += "+";
			else
				currString += "=";
			break;
		case FSKEY_LBRACKET:
			if (shiftIsOn)
				currString += "{";
			else
				currString += "[";
			break;
		case FSKEY_RBRACKET:
			if (shiftIsOn)
				currString += "}";
			else
				currString += "]";
			break;
		case FSKEY_BACKSLASH:
			if (shiftIsOn)
				currString += "|";
			else
				currString += "\\"; // backslash
			break;
		case FSKEY_SEMICOLON:
			if (shiftIsOn)
				currString += ":";
			else
				currString += ";";
			break;
		case FSKEY_SINGLEQUOTE:
			if (shiftIsOn)
				currString += "\""; // double quote
			else
				currString += "'";
			break;
		case FSKEY_SLASH:
			if (shiftIsOn)
				currString += "?";
			else
				currString += "/";
			break;
		case FSKEY_TILDA:
			if (shiftIsOn)
				currString += "~";
			else
				currString += "`";
			break;

		}
	}
	return true; // may use this later ???
}

void DrawingUtilNG::drawCircle(double centerX, double centerY,
	double sizeX, double sizeY, bool filled)
{
	float x, y, angle;
	float radianConvert = atan(1.) / 45.;
	float radius = (fabs(sizeX) + fabs(sizeY)) / 2.;

	// adapt the number of segments based on radius size
	int stepSize = 1;
	if (radius < 10)
		stepSize = 3;
	else if (radius < 200)
		stepSize = round((3. - 1.) / (10. - 200.) * (radius - 200.) + 1.);

	stepSize *= 6;  // always want stepSize to be a factor of 360

	if (filled)
		glBegin(GL_POLYGON);
	else
		glBegin(GL_LINE_LOOP);

	for (int i = 0; i < 360; i += stepSize) {
		angle = i * radianConvert;
		x = cos(angle) * sizeX/2. + centerX;
		y = sin(angle) * sizeY/2. + centerY;
		glVertex2d(x, y);
	}
	glEnd();
}

void DrawingUtilNG::drawRectangle(double x, double y, int sizeX, int sizeY, bool filled)
{
	if (filled)
		glBegin(GL_POLYGON);
	else
		glBegin(GL_LINE_LOOP);

	glVertex2i(x, y);
	glVertex2i(x + sizeX, y);
	glVertex2i(x + sizeX, y + sizeY);
	glVertex2i(x, y + sizeY);

	glEnd();
}

void DrawingUtilNG::drawStar(double centerX, double centerY,
	double outerSize, double innerSize, int numbPoints, double startAngle, bool filled)
{
	float radianConvert = atan(1.) / 45.;
	double stepSize = 360. / 2. / numbPoints;

	if (filled) {
		// GL_POLYGON cannot do concave shapes, so must draw series of quads (rhombuses)
		// BTW, quad strip don't work because they would share the "wrong edge"
		double currAngle, longX, longY;
		double currShortX, currShortY, prevShortX, prevShortY;

		currAngle = (startAngle - stepSize) * radianConvert;
		prevShortX = cos(currAngle) * innerSize + centerX;
		prevShortY = -sin(currAngle) * innerSize + centerY;

		for (int i = 0; i < numbPoints; i++) {
			currAngle += stepSize * radianConvert;
			longX = cos(currAngle) * outerSize + centerX;
			longY = -sin(currAngle) * outerSize + centerY;
			currAngle += stepSize * radianConvert;
			currShortX = cos(currAngle) * innerSize + centerX;
			currShortY = -sin(currAngle) * innerSize + centerY;

			glBegin(GL_QUADS);
			glVertex2d(centerX, centerY);
			glVertex2d(prevShortX, prevShortY);
			glVertex2d(longX, longY);
			glVertex2d(currShortX, currShortY);
			glEnd();

			prevShortX = currShortX;
			prevShortY = currShortY;
		}
	}
	else {
		double x, y, currRadius, currAngle;
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < (numbPoints * 2); i++) {
			currAngle = (startAngle + i * stepSize) * radianConvert;

			// if i is even , use outerSize 
			// (remainder of i div 2 is zero which means false, 
			// which means use second choice on trinary operator)
			currRadius = i % 2 ? innerSize : outerSize;

			x = cos(currAngle) * currRadius + centerX;
			y = -sin(currAngle) * currRadius + centerY;
			glVertex2d(x, y);
		}
		glEnd();
	}
}

void DrawingUtilNG::drawStarGram(double centerX, double centerY, double size,
	int numbPoints, int numbSkip, double startAngle, bool filled)
{
	int i;
	float radianConvert = atan(1.) / 45.;
	double stepSize = 360. / numbPoints;

	if (numbSkip >= numbPoints / 2)
		numbSkip = numbPoints / 2 - 1;

	if (filled) {
		double x0, y0, x1, y1;
		double currAngle = startAngle * radianConvert;

		x0 = cos(currAngle) * size + centerX;
		y0 = -sin(currAngle) * size + centerY;

		for (i = 0; i < numbPoints / 2; i++) {
			currAngle += stepSize * radianConvert * (numbSkip + 1);
			x1 = cos(currAngle) * size + centerX;
			y1 = -sin(currAngle) * size + centerY;
			glBegin(GL_TRIANGLES);
			glVertex2d(centerX, centerY);
			glVertex2d(x0, y0);
			glVertex2d(x1, y1);

			glEnd();
			x0 = x1; y0 = y1;
		}
		if (!(numbPoints - numbSkip + 1) % 2) {// if even number of points
			currAngle -= stepSize * radianConvert;
			x0 = cos(currAngle) * size + centerX;
			y0 = -sin(currAngle) * size + centerY;
		}

		for (; i < numbPoints; i++) {
			currAngle += stepSize * radianConvert * (numbSkip + 1);
			x1 = cos(currAngle) * size + centerX;
			y1 = -sin(currAngle) * size + centerY;
			glBegin(GL_TRIANGLES);
			glVertex2d(centerX, centerY);
			glVertex2d(x0, y0);
			glVertex2d(x1, y1);

			glEnd();
			x0 = x1; y0 = y1;
		}
	}
	else {
		int i;
		double x, y;
		double currAngle = startAngle * radianConvert;

		x = cos(currAngle) * size + centerX;
		y = -sin(currAngle) * size + centerY;
		glBegin(GL_LINE_LOOP);
		glVertex2d(x, y);

		for (i = 0; i < numbPoints / 2; i++) {
			currAngle += stepSize * radianConvert * (numbSkip + 1);

			x = cos(currAngle) * size + centerX;
			y = -sin(currAngle) * size + centerY;
			glVertex2d(x, y);

		}
		if (!(numbPoints - numbSkip + 1) % 2) {// if even number of points
			glEnd();
			currAngle -= stepSize * radianConvert;
			x = cos(currAngle) * size + centerX;
			y = -sin(currAngle) * size + centerY;
			glBegin(GL_LINE_LOOP);
			glVertex2d(x, y);

		}
		for (; i < numbPoints; i++) {
			currAngle += stepSize * radianConvert * (numbSkip + 1);

			x = cos(currAngle) * size + centerX;
			y = -sin(currAngle) * size + centerY;
			glVertex2d(x, y);

		}
		glEnd();

	}
}

