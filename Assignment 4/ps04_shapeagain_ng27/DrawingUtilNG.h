#pragma once
#include <string>

namespace DrawingUtilNG {

	//converts a color model from HSV (degrees, 0.-1., 0.-1.) to RGB (3 values 0.-1.)
	bool hsv2rgb(double H, double S, double V,
		double& red, double& green, double& blue);

	// takes over the screen and allows graphical text input
	bool buildStringFromFsInkey(int key, std::string& currString);

};
