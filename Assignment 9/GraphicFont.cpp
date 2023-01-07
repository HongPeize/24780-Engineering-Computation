
#include <string>
#include <iostream>
#include <fstream>
#include "fssimplewindow.h"
#include "DrawingUtilNG.h"
#include "GraphicFont.h"

using namespace std;
using namespace DrawingUtilNG;

void GraphicFont::drawText(const string& aString, double locX, double locY, 
	double scale, double theta, bool centered)
{
	glColor4d(red, green, blue, alpha);
	// enable texture mapping
	glEnable(GL_TEXTURE_2D);

	// bind a texture to OpenGL primitives
	glBindTexture(GL_TEXTURE_2D, textureID);

	// turn on blending so that transparency can be applied
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (centered) {
		float width = getWordWidth(aString, scale);
		// rotating a vector from center of text to bottom of text box
		// about a vector normal to x-y plane 
		auto rotatedOrigin = rotateVector({ -width / 2.f, -letterHei * float(scale) / 2.f, 0 },
			{ 0, 0, 1 }, theta);
		locX += rotatedOrigin.x;
		locY -= rotatedOrigin.y;
	}
	// draw the letters
	for (int i = 0; i < aString.length(); i++) {
		drawLetter(aString[i], locX, locY, scale, theta);
	}

	// turn off blending 
	glDisable(GL_BLEND);
	// turn off texture 
	glDisable(GL_TEXTURE_2D);

}

double GraphicFont::getWordWidth(const std::string& aString, double scale)
{
	double sumWidth = 0;
	int index;
	for (int i = 0; i < aString.length(); i++) {
		index = aString[i] - firstLetter;
		sumWidth += (fontCoords[index].x2 - fontCoords[index].x1);
	}
	return sumWidth * scale;
}

void GraphicFont::drawTextCircle(const std::string& aString, double centerX, double centerY,
	double radius, double scale, double theta, double adjustRadius)
{
	double angleConvert = atan(1.) / 45.;
	double locX, locY, prevTheta;
	int letterIndex;
	double letterHalfWidth;
	double prevLetterHalfWidth = 0;
	double deltaAngleSign = scale / fabs(scale);

	glColor4d(red, green, blue, alpha);
	// enable texture mapping
	glEnable(GL_TEXTURE_2D);

	// bind a texture to OpenGL primitives
	glBindTexture(GL_TEXTURE_2D, textureID);

	// turn on blending so that transparency can be applied
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// draw the letters
	for (int i = 0; i < aString.length(); i++) {
		// need to figure out location and angle 
		letterIndex = aString[i] - firstLetter;
		if (letterIndex < fontCoords.size()) {

			letterHalfWidth = double(fontCoords[letterIndex].x2 - fontCoords[letterIndex].x1) / 2. * scale;
			if (i > 0) {

				// adjust theta for this letter
				prevTheta = theta;
				theta -= (atan(letterHalfWidth / radius) + atan(prevLetterHalfWidth / radius))
					/ angleConvert;

				// adjust radius for this letter
				radius += (prevTheta - theta) / 360. * adjustRadius * letterHei * scale;
			}

			// determine coordinates for this letter
			locX = centerX + radius * cos(theta * angleConvert)
				- letterHalfWidth * cos((90. - theta) * angleConvert);
			locY = centerY - radius * sin(theta * angleConvert)
				- letterHalfWidth * sin((90 - theta) * angleConvert);


			drawLetter(aString[i], locX, locY, scale, theta - 90.);
			
			// store last letter halfwidth
			prevLetterHalfWidth = letterHalfWidth;
		}
	}

	// turn off blending 
	glDisable(GL_BLEND);
	// turn off texture 
	glDisable(GL_TEXTURE_2D);


}

void GraphicFont::drawText3D(const std::string& aString,
	vertexF v0, vertexF vUp, vertexF vRight, double scale, double theta)
{
	double locX = 0, locY = 0;

	glColor4d(red, green, blue, alpha);
	// enable texture mapping
	glEnable(GL_TEXTURE_2D);

	// bind a texture to OpenGL primitives
	glBindTexture(GL_TEXTURE_2D, textureID);

	// turn on blending so that transparency can be applied
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// set up for first letter
	
	// note that since all 3D drawing is in world coordinates, I do not
	// have to worry about "y is downwards" issue of screen coordinates

	vertexF upUnitVector = getUnitVector(v0, vUp);
	vertexF rightUnitVector = getUnitVector(v0, vRight);

	// need to rotate unit vectors by theta angle (in the plane)
	// get vector normal to plane and then use Rodrigues' Rotation Formula
	vertexF unitCross = crossProduct(rightUnitVector, upUnitVector);

	upUnitVector = rotateVector(upUnitVector, unitCross, theta);
	rightUnitVector = rotateVector(rightUnitVector, unitCross, theta);

	// draw the letters
	for (int i = 0; i < aString.length(); i++) {
		drawLetter3D(aString[i], v0, upUnitVector, rightUnitVector, scale);
	}

	// turn off blending 
	glDisable(GL_BLEND);
	// turn off texture 
	glDisable(GL_TEXTURE_2D);

}

void GraphicFont::init()
{
	YsRawPngDecoder fontImage;

	// set default color to white
	red = 1.0; green = 1.0; blue = 1.0;

	glGenTextures(1, &textureID);
	fontImage.Decode(imageFileName.c_str());

	imageWid = fontImage.wid;
	imageHei = fontImage.hei;

	glBindTexture(GL_TEXTURE_2D, textureID);  // Making the texture identifier current (or bring it to the deck)

	// set up parameters for the current texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D
	(GL_TEXTURE_2D,
		0,    // Level of detail
		GL_RGBA,       // the "A" in RGBA will include the transparency
		fontImage.wid,
		fontImage.hei,
		0,    // Border width, but not supported and needs to be 0.
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		fontImage.rgba);

	// read the font geometric data
	ifstream inFile(dataFileName);
	if (inFile.is_open()) { // may not have found file
		int x1, x2, y;
		unsigned char tempChar;
		string tempStr;
		inFile >> letterHei;
		getline(inFile, tempStr); // read and discard rest of line

		while (!inFile.eof()) {
			inFile >> tempChar >> x1 >> x2 >> y;
			fontCoords.push_back({ x1, x2, y });
		}
		inFile.close();
	}
	else
		cout << "Font data file " << dataFileName << " is unavailable. " << endl;
}

void GraphicFont::drawLetter(char aLetter, double& locX, double& locY, double scale, double theta)
{
	int index = aLetter - firstLetter;
	double cosTheta = cos(theta * atan(1.) / 45.);
	double sinTheta = sin(theta * atan(1.) / 45.);

	if (index < fontCoords.size()) {
		double minX = fontCoords[index].x1 / imageWid;
		double maxX = fontCoords[index].x2 / imageWid;
		double minY = (fontCoords[index].y - letterHei) / imageHei;
		double maxY = fontCoords[index].y / imageHei;

		int drawHeight = letterHei * fabs(scale);
		int drawWidth = (fontCoords[index].x2 - fontCoords[index].x1) * scale;

		// think of rectangle as vertices A, B, C, D (defined counter-clockwise)
		// A is at lower left, B is at lower right, C is at upper right, D is at upper left
		double Ax = locX, Ay = locY;
		double Bx = Ax + drawWidth * cosTheta, By = Ay - drawWidth * sinTheta;
		double Cx = Bx - drawHeight * sinTheta, Cy = By - drawHeight * cosTheta;
		double Dx = Ax - drawHeight * sinTheta, Dy = Ay - drawHeight * cosTheta;

		glBegin(GL_QUADS);
		glTexCoord2d(minX, maxY);   // these are "percentage" of the image
		glVertex2d(Ax, Ay);        // these are actual pixel coordinates on screen

		glTexCoord2d(maxX, maxY);
		glVertex2d(Bx, By);

		glTexCoord2d(maxX, minY);
		glVertex2d(Cx, Cy);

		glTexCoord2d(minX, minY);
		glVertex2d(Dx, Dy);
		glEnd();

		// reset for next letter
		locX = Bx;
		locY = By;
	}
	else {
		cout << "Do not have information for letter: " << aLetter << endl;
	}
}

void GraphicFont::drawLetter3D(char aLetter,
	vertexF& v0, vertexF& upUnitVector, vertexF& rightUnitVector, double scale)
{
	int index = aLetter - firstLetter;
	if (index < fontCoords.size()) {
		double minX = fontCoords[index].x1 / imageWid;
		double maxX = fontCoords[index].x2 / imageWid;
		double minY = (fontCoords[index].y - letterHei) / imageHei;
		double maxY = fontCoords[index].y / imageHei;

		float drawHeight = letterHei * fabs(scale);
		float drawWidth = (fontCoords[index].x2 - fontCoords[index].x1) * scale;

		// think of quad as vertices A, B, C, D (defined clockwise)
		// A is at lower left, B is at lower right, C is at upper right, D is at upper left
		vertexF rectA = v0;
		vertexF rectB, rectC, rectD;

		rectB.x = rectA.x + drawWidth * rightUnitVector.x;
		rectB.y = rectA.y + drawWidth * rightUnitVector.y;
		rectB.z = rectA.z + drawWidth * rightUnitVector.z;

		rectC.x = rectB.x + drawHeight * upUnitVector.x;
		rectC.y = rectB.y + drawHeight * upUnitVector.y;
		rectC.z = rectB.z + drawHeight * upUnitVector.z;

		rectD.x = rectA.x + drawHeight * upUnitVector.x;
		rectD.y = rectA.y + drawHeight * upUnitVector.y;
		rectD.z = rectA.z + drawHeight * upUnitVector.z;

		glBegin(GL_QUADS);
		glTexCoord2d(minX, maxY);   // these are "percentage" of the image
		glVertex3f(rectA.x, rectA.y, rectA.z);        // these are actual pixel coordinates on screen

		glTexCoord2d(maxX, maxY);
		glVertex3f(rectB.x, rectB.y, rectB.z);

		glTexCoord2d(maxX, minY);
		glVertex3f(rectC.x, rectC.y, rectC.z);

		glTexCoord2d(minX, minY);
		glVertex3f(rectD.x, rectD.y, rectD.z);
		glEnd();

		// reset vertices for next letter
		v0 = rectB;

		// no need to reset upUnitVector and rightUnitVector
	}
	else {
		cout << "Do not have information for letter: " << aLetter << endl;
	}

}
