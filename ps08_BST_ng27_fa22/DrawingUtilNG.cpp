#include <stdio.h>
#include <algorithm>    // std::max
#include <string>
//#include "GL\glut.h"
#include <vector>
#include "fssimplewindow.h"
#include <math.h>
#include "DrawingUtilNG.h" // this one HAS to be before #include "GraphicFont.h"
#include "GraphicFont.h"



using namespace DrawingUtilNG;

double DrawingUtilNG::getDistance(double x0, double y0, double x1, double y1)
{
	return sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
}

float DrawingUtilNG::getDistance(vertexF v1, vertexF v2)
{
	return vectorLength({ v2.x - v1.x, v2.y - v1.y, v2.z - v1.z });
}

float DrawingUtilNG::vectorLength(vertexF v0)
{
	return sqrt(v0.x * v0.x + v0.y * v0.y + v0.z * v0.z);
}

vertexF DrawingUtilNG::getUnitVector(vertexF v0)
{
	return getUnitVector({ 0., 0., 0. }, v0);
}

vertexF DrawingUtilNG::getUnitVector(vertexF v1, vertexF v2)
{
	vertexF vector = { (v2.x - v1.x) , (v2.y - v1.y) , (v2.z - v1.z) };

	float length = vectorLength(vector);

	vector = { vector.x / length, vector.y / length, vector.z / length };

	return vector;
}

vertexF DrawingUtilNG::vectorSum(vertexF v1, vertexF v2)
{
	return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

vertexF DrawingUtilNG::vectorSum(vertexF v1, vertexF v2, vertexF v3)
{
	return { v1.x + v2.x + v3.x, v1.y + v2.y + v3.y, v1.z + v2.z + v3.z };
}

vertexF DrawingUtilNG::scalarProduct(vertexF v0, float scalar)
{
	return { v0.x * scalar, v0.y * scalar, v0.z * scalar };
}

float DrawingUtilNG::dotProduct(vertexF v1, vertexF v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

vertexF DrawingUtilNG::crossProduct(vertexF v1, vertexF v2)
{
	return {
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	};
}

vertexF DrawingUtilNG::rotateVector(vertexF v, vertexF k, float theta)
{
	double cosTheta = cos(theta * atan(1.) / 45.);
	double sinTheta = sin(theta * atan(1.) / 45.);

	// make sure k is a unit vector
	k = getUnitVector(k);

	// using Rodrigues' Rotation Formula
	vertexF firstTerm = scalarProduct(v, cosTheta);
	vertexF secondTerm = scalarProduct(crossProduct(k, v), sinTheta);
	vertexF thirdTerm = scalarProduct(k, dotProduct(k, v) * (1 - cosTheta));

	return vectorSum(firstTerm, secondTerm, thirdTerm);
}

void DrawingUtilNG::drawCircle(double centerX, double centerY,
	double sizeX, double sizeY, bool filled, double outerSizeX, double outerSizeY)
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

	if (outerSizeX < 0 || outerSizeY < 0) {
		if (filled)
			glBegin(GL_POLYGON);
		else
			glBegin(GL_LINE_LOOP);

		for (int i = 0; i < 360; i += stepSize) {
			angle = i * radianConvert;
			x = cos(angle) * sizeX / 2. + centerX;
			y = sin(angle) * sizeY / 2. + centerY;
			glVertex2d(x, y);
		}
		glEnd();
	}
	else {
		double prevX, prevY;

		//// easier to do with transformations
		//glTranslated(centerX, centerY, 0);
		//glRotated(0, 0, -stepSize / 2.);

		glBegin(GL_QUAD_STRIP);  // order of vertices is a bit different than for QUADS

		for (int i = 0; i <= 360; i += stepSize) {
			angle = i * radianConvert;
			x = cos(angle) * sizeX / 2. + centerX;
			y = sin(angle) * sizeY / 2. + centerY;
			glVertex2d(x, y);
			x = cos(angle) * outerSizeX / 2. + centerX;
			y = sin(angle) * outerSizeY / 2. + centerY;
			glVertex2d(x, y);
		}

		glEnd();

		//glTranslated(-centerX, -centerY, 0);

	}

}

void DrawingUtilNG::drawRectangle(double x, double y,
	int sizeX, int sizeY, bool filled, double outerSizeX, double outerSizeY)
{
	if (outerSizeX < 0 || outerSizeY < 0) {
		if (filled)
			glBegin(GL_QUADS);
		else
			glBegin(GL_LINE_LOOP);

		glVertex2i(x, y);
		glVertex2i(x + sizeX, y);
		glVertex2i(x + sizeX, y + sizeY);
		glVertex2i(x, y + sizeY);

		glEnd();
	}

	else {
		// draw four rectangles to create hole 
		// (as a human, I think of y going up and let +/- take care of itself)

		// from top left corner of hole, right to outerSizeX, up to outerSizeY
		drawRectangle(x, y + sizeY, (outerSizeX + sizeX) / 2., (outerSizeY - sizeY) / 2., true);

		// from bot right corner of hole, left to outerSizeX, down to outerSizeY
		drawRectangle(x + sizeX, y, -(outerSizeX + sizeX) / 2., -(outerSizeY - sizeY) / 2., true);

		// from top right corner of hole, right to outerSizeX, down to outerSizeY
		drawRectangle(x + sizeX, y + sizeY, (outerSizeX - sizeX) / 2., -(outerSizeY + sizeY) / 2., true);

		// from bot left corner of hole, left to outerSizeX, up to outerSizeY
		drawRectangle(x, y, -(outerSizeX - sizeX) / 2., (outerSizeY + sizeY) / 2., true);

	}
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

//// drawStar test
//int currStarAngle = 0;
//DrawingUtilNG::drawStarGram(550, 180, 100, 9, 1, 90, true);
//DrawingUtilNG::drawStar(400, 400, 100, 100, 8, 90, true);
//glColor3ub(0, 255, 255);
//DrawingUtilNG::drawStarGram(550, 180, 70, 9, 1, 90, false);
//DrawingUtilNG::drawStar(400, 400, 95, 40, 8, 0, false);


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

/*
void DrawingUtilNG::writeHelvetica(std::string outString, int locX, int locY, int size)
{
	void *fontCode;
	switch (size) {
	case 10: fontCode = GLUT_BITMAP_HELVETICA_10;
		break;
	case 12: fontCode = GLUT_BITMAP_HELVETICA_12;
		break;
	case 18: fontCode = GLUT_BITMAP_HELVETICA_18;
		break;
	default: fontCode = GLUT_BITMAP_HELVETICA_10;
		break;
	}

	glRasterPos2i(locX, locY);
	for (int i = 0; i < outString.length(); i++) {
		glutBitmapCharacter(fontCode,
			outString.substr(i, 1).c_str()[0]);
	}
}
void DrawingUtilNG::writeTimesRoman(std::string outString, int locX, int locY, int size)
{
	void *fontCode;
	switch (size) {
	case 10: fontCode = GLUT_BITMAP_TIMES_ROMAN_10;
		break;
	case 24: fontCode = GLUT_BITMAP_TIMES_ROMAN_24;
		break;
	default: fontCode = GLUT_BITMAP_TIMES_ROMAN_10;
		break;
	}

	glutInitWindowPosition(45, 76);
	glRasterPos2i(locX, locY);
	for (int i = 0; i < outString.length(); i++) {
		glutBitmapCharacter(fontCode,
			outString.substr(i, 1).c_str()[0]);
	}
}
*/
void DrawingUtilNG::coverAndFade(int x1, int y1, int x2, int y2, int totalT, int currT,
	int r, int g, int b)
{
	if (currT > totalT)
		currT = totalT;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	int temp = currT / totalT * 255;
	glColor4ub(r, g, b, currT / (double)totalT * 255);
	//glColor4ub(0, 0, 0, 180);
	drawRectangle(x1, y1, x2, y2, true);

	glDisable(GL_BLEND);

}

void DrawingUtilNG::drawCube(vertexF v1, vertexF v2, bool sixColors)
{
	drawCube(v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, sixColors);
}

void DrawingUtilNG::drawCube(double x1, double y1, double z1,
	double x2, double y2, double z2, bool sixColors, GraphicFont* aFont)
{
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1, 1);

	glBegin(GL_QUADS);

	if (sixColors)
		glColor3ub(0, 0, 255);  // blue face
	glVertex3d(x1, y1, z1);
	glVertex3d(x2, y1, z1);
	glVertex3d(x2, y2, z1);
	glVertex3d(x1, y2, z1);

	if (sixColors)
		glColor3ub(0, 255, 0);  // green
	glVertex3d(x1, y1, z2);
	glVertex3d(x2, y1, z2);
	glVertex3d(x2, y2, z2);
	glVertex3d(x1, y2, z2);

	if (sixColors)
		glColor3ub(0, 255, 255); // cyan
	glVertex3d(x1, y1, z1);
	glVertex3d(x2, y1, z1);
	glVertex3d(x2, y1, z2);
	glVertex3d(x1, y1, z2);

	if (sixColors)
		glColor3ub(255, 0, 0);  // red
	glVertex3d(x1, y2, z1);
	glVertex3d(x2, y2, z1);
	glVertex3d(x2, y2, z2);
	glVertex3d(x1, y2, z2);

	if (sixColors)
		glColor3ub(255, 0, 255); // magenta
	glVertex3d(x1, y1, z1);
	glVertex3d(x1, y2, z1);
	glVertex3d(x1, y2, z2);
	glVertex3d(x1, y1, z2);

	if (sixColors)
		glColor3ub(255, 255, 0);  // yellow
	glVertex3d(x2, y1, z1);
	glVertex3d(x2, y2, z1);
	glVertex3d(x2, y2, z2);
	glVertex3d(x2, y1, z2);

	glEnd();

	glDisable(GL_POLYGON_OFFSET_FILL);

	//font tester (needs GraphicFont.h)
	if (aFont != NULL) {
		aFont->setColorHSV(30, 1, 1);
		//aFont->drawText3D("  ONE is the loneliest number",
		aFont->drawText3D(" 1ne",
			{ (float)x2, (float)y1, (float)z2 }, { (float)x2, (float)y2, (float)z2 }, { (float)x2, (float)y1, (float)z1 }, .15, 10.);

		aFont->drawText3D(" 2wo",
			{ (float)x2, (float)y1, (float)z1 }, { (float)x2, (float)y2, (float)z1 }, { (float)x1, (float)y1, (float)z1 }, .15, 10.);

		aFont->drawText3D(" 6ix",
			{ (float)x1, (float)y1, (float)z1 }, { (float)x1, (float)y2, (float)z1 }, { (float)x1, (float)y1, (float)z2 }, .15, 10.);

		aFont->drawText3D(" 5ive",
			{ (float)x1, (float)y1, (float)z2 }, { (float)x1, (float)y2, (float)z2 }, { (float)x2, (float)y1, (float)z2 }, .15, 10.);

		aFont->drawText3D(" 3ee",
			{ (float)x1, (float)y2, (float)z1 }, { (float)x2, (float)y2, (float)z1 }, { (float)x1, (float)y2, (float)z2 }, .15, 10.);

		aFont->drawText3D(" 4r",
			{ (float)x2, (float)y1, (float)z2 }, { (float)x2, (float)y1, (float)z1 }, { (float)x1, (float)y1, (float)z2 }, .15, 10.);

	}
}

void DrawingUtilNG::drawSphere(vertexF center, float radius)
{
	drawSphere(center.x, center.y, center.z, center.x, center.y + radius, center.z);
}

void DrawingUtilNG::drawSphere(vertexF center, vertexF northPole)
{
	drawSphere(center.x, center.y, center.z, northPole.x, northPole.y, northPole.z);
}

void DrawingUtilNG::drawSphere(float centerX, float centerY, float centerZ, float radius)
{
	drawSphere(centerX, centerY, centerZ, centerX, centerY + radius, centerZ);
}

void DrawingUtilNG::drawSphere(float centerX, float centerY, float centerZ, float northX, float northY, float northZ)
{
	// See http://www.songho.ca/opengl/gl_sphere.html (although for me, y is up)
	// for now, let's just assume north is straight up (baby steps)
	// later, I'll figure out glRotated();

	// Drawing an icosahedron (sphere made up of 20 equilateral triangles)
	// Need coordinates of 12 points:
	//    - north pole and south pole (obvious coords)
	//    - 5 points on northern hemisphere (at atan(1/2) latitude)
	//    - 5 points on southern hemisphere (at -atan(1/2) latitude)

	// constants
	const float PI = atanf(1.f) * 4.f;
	const float H_ANGLE = PI * 2.f / 5.f;    // 72 degree = 360 / 5
	const float V_ANGLE = atanf(1.0f / 2.f);  // elevation = 26.565 degree

	std::vector<vertexF> vertices(12);

	float radius = getDistance({ centerX, centerY, centerZ }, { northX, northY, northZ });
	float elevY = radius * sinf(V_ANGLE);  // elevation of 5 points above equator
	float elevRadius = radius * cosf(V_ANGLE); // horz distance from axis to 5 points

	vertices[0] = { 0., radius, 0. };
	vertices[11] = { 0., -radius, 0. };

	float currHorzAngle1 = -PI / 2.;   // start at 90 deg. (why?)
	for (int i = 1; i <= 5; i++) {
		// northern hemisphere
		vertices[i] = { elevRadius * cosf(currHorzAngle1), elevY , elevRadius * sinf(currHorzAngle1) };
		currHorzAngle1 += H_ANGLE / 2.;
		// northern hemisphere
		vertices[i + 5] = { elevRadius * cosf(currHorzAngle1), -elevY , elevRadius * sinf(currHorzAngle1) };
		currHorzAngle1 += H_ANGLE / 2.;
	}

	//glDrawElements(GL_TRIANGLES, 12, )
	//glBegin(GL_TRIANGLES);
	//for (int i = 1; i <= 5; i++) {
	//// north cap
	//drawVertex(vertices[0]);
	//drawVertex(vertices[i]);
	//drawVertex(vertices[(i % 5) + 1]);

	////	// south cap
	//drawVertex(vertices[11]);
	//drawVertex(vertices[i + 5]);
	//drawVertex(vertices[(i % 5) + 6]);

	//// north strip
	//drawVertex(vertices[i]);
	//drawVertex(vertices[((i - 1) % 5) + 6]);
	//drawVertex(vertices[(i % 5) + 1]);

	//// south strip
	//drawVertex(vertices[i + 5]);
	//drawVertex(vertices[(i % 5) + 1]);
	//drawVertex(vertices[(i % 5) + 6]);

	//}
	//glEnd();

	//glColor3ub(255, 255, 255);
	//for (int i = 1; i <= 5; i++) {
	//	// north cap
	//	glBegin(GL_LINE_STRIP);
	//	drawVertex(vertices[0]);
	//	drawVertex(vertices[i]);
	//	drawVertex(vertices[(i % 5) + 1]);
	//	glEnd();

	//	// south cap
	//	glBegin(GL_LINE_STRIP);
	//	drawVertex(vertices[11]);
	//	drawVertex(vertices[i + 5]);
	//	drawVertex(vertices[(i % 5) + 6]);
	//	glEnd();

	//	// north strip
	//	glBegin(GL_LINE_STRIP);
	//	drawVertex(vertices[i]);
	//	drawVertex(vertices[((i - 1) % 5) + 6]);
	//	drawVertex(vertices[(i % 5) + 1]);
	//	glEnd();

	//	// south strip
	//	glBegin(GL_LINE_STRIP);
	//	drawVertex(vertices[i + 5]);
	//	drawVertex(vertices[(i % 5) + 1]);
	//	drawVertex(vertices[(i % 5) + 6]);
	//	glEnd();

	//}

	// single triangle strip per loop
	for (int i = 1; i <= 1; i++) {
		glBegin(GL_TRIANGLE_STRIP);
		drawVertex(vertices[0]);
		drawVertex(vertices[i]);
		drawVertex(vertices[(i % 5) + 1]);
		drawVertex(vertices[i + 5]);
		drawVertex(vertices[(i % 5) + 6]);
		drawVertex(vertices[11]);

		glEnd();
	}

	// single line strip per loop (can probably remove some)
	glColor3ub(200, 200, 200);
	for (int i = 1; i <= 5; i++) {
		glBegin(GL_LINE_STRIP);
		drawVertex(vertices[i]);
		drawVertex(vertices[0]);
		drawVertex(vertices[(i % 5) + 1]);
		drawVertex(vertices[i]);
		drawVertex(vertices[i + 5]);
		drawVertex(vertices[(i % 5) + 1]);
		drawVertex(vertices[(i % 5) + 6]);
		drawVertex(vertices[i + 5]);
		drawVertex(vertices[11]);
		drawVertex(vertices[i + 5]);

		glEnd();
	}
}

void DrawingUtilNG::drawVertex(vertexF v)
{
	glVertex3f(v.x, v.y, v.z);
}

bool DrawingUtilNG::buildStringFromFsInkey(int key, std::string& currString)
{
	bool shiftIsOn = FsGetKeyState(FSKEY_SHIFT);;

	// get key input and update the given string

	if (FSKEY_A <= key && key <= FSKEY_Z) {
		int adjustLetter = shiftIsOn ? 0 : int('a') - int('A');
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
	else if (FSKEY_TEN0 <= key && key <= FSKEY_TEN9) { // for the number keypad (on some computers)
		currString += char(int('0') + key - FSKEY_TEN0);
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
				currString += "|";  // pipe
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
				currString += "'"; // single quote
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
				currString += "`"; // inverse single quote
			break;
		case FSKEY_TENDOT:
			currString += ".";
			break;
		case FSKEY_TENSLASH:
			currString += "/";
			break;
		case FSKEY_TENSTAR:
			currString += "*";
			break;
		case FSKEY_TENMINUS:
			currString += "-";
			break;
		case FSKEY_TENPLUS:
			currString += "+";
			break;

		}
	}
	return true; // may use this later ???
}

std::string DrawingUtilNG::getStringFromScreen(const std::string& prompt1,
	const std::string& prompt2, const std::string& prompt3)
{
	int key;
	int xloc = 140, yloc = 200, vspace = 40;
	std::string inputString = ""; // probably don't need this initialization
	ArialFont arial;
	double fscale = 0.3;
	FsPollDevice();
	key = FsInkey();
	while (key != FSKEY_ESC && key != FSKEY_ENTER) {
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		// ask for input from the graphics window 
		// (using GraphicFont or ysgfontdata, comment/uncomment as needed)
		yloc = 100;
		//glColor3f(0, 0, 0);
		arial.setColorRGB(0., 0., 0.);
		if (prompt1.length() > 0) {
			//glRasterPos2d(xloc, yloc - 10);
			//YsGlDrawFontBitmap16x20(prompt1.c_str());

			arial.drawText(prompt1, xloc, yloc, fscale);
			yloc += vspace;
			if (prompt2.length() > 0) {
				//glRasterPos2d(xloc, yloc - 10);
				//YsGlDrawFontBitmap16x20(prompt1.c_str());

				arial.drawText(prompt2, xloc, yloc, fscale);
				yloc += vspace;
				if (prompt3.length() > 0) {
					//glRasterPos2d(xloc, yloc - 10);
					//YsGlDrawFontBitmap16x20(prompt3.c_str());

					arial.drawText(prompt3, xloc, yloc, fscale);
					yloc += vspace;
				}
			}
		}
		// input box
		yloc += 15;
		glColor3ub(255, 0, 255);
		DrawingUtilNG::drawRectangle(xloc, yloc - 40, 450, 50, false);

		// build string from keyboard entry, letter by letter
		DrawingUtilNG::buildStringFromFsInkey(key, inputString);

		inputString += "_"; // add an underscore as prompt

		//glRasterPos2i(xloc+10, yloc);  // sets position
		//YsGlDrawFontBitmap16x24(inputString.c_str());

		arial.setColorRGB(1., 0., 1.);
		arial.drawText(inputString, 150, yloc, fscale);

		inputString = inputString.substr(0, inputString.length() - 1); // remove underscore

		FsSwapBuffers();
		FsSleep(25);

		FsPollDevice();
		key = FsInkey();
	}

	if (key == FSKEY_ENTER) {
		return inputString;
	}
	else
		return "";

}

/*
*/
