#include <stdio.h>
#include <algorithm>    // std::max
//#include "GL\glut.h"

#include "fssimplewindow.h"

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