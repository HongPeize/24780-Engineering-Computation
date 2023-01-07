#include <string>
#include "DrawingUtilNG.h"
#include "StringPlus.h"
#include "GraphicFont.h"
#include "ButtonCollection.h"

using namespace std;

void ButtonCollection::add(int locX, int locY, int wid, int hei, int val, std::string text,
	GraphicFont* aFont, std::string description,
	Button::AnchorMode horz, Button::AnchorMode vert)
{
	theButtons.push_back(Button(locX, locY, wid, hei, val, text, aFont, description));
	theButtons.back().setAnchor(horz, vert);
}

void ButtonCollection::remove(int val)
{
	int wantedIndex = getIndex(val);
	if (wantedIndex >= 0)
		theButtons.erase(theButtons.begin() + wantedIndex);
}

void ButtonCollection::disableButton(int val)
{
	int wantedIndex = getIndex(val);
	if (wantedIndex >= 0)
		theButtons.at(wantedIndex).disable();
}

void ButtonCollection::enableButton(int val)
{
	int wantedIndex = getIndex(val);
	if (wantedIndex >= 0)
		theButtons.at(wantedIndex).enable();
}

int ButtonCollection::checkClick(int locX, int locY)
{
	int buttonValue;
	for (auto& currButton : theButtons) {
		buttonValue = currButton.getVal(locX, locY);
		if (buttonValue != FSKEY_NULL)
			return buttonValue;
	}
	return FSKEY_NULL;
}

void ButtonCollection::checkHover(int locX, int locY)
{
	for (auto& currButton : theButtons) {
		currButton.paintHover(locX, locY);
	}
}

void ButtonCollection::paint()
{
	//glLoadIdentity();
	//glColor3ub(255, 255, 255);
	//DrawingUtilNG::drawRectangle(800, 0, 300, 800, true);

	for (auto& currButton : theButtons) {
		currButton.paint();
	}
}

int ButtonCollection::getIndex(int val)
{
	int i = 0;
	for (auto& currButton : theButtons) {
		if (currButton.getVal() == val)
			return i;  // possible exit from function
		i++;
	}
	return -1;
}

// ===============================================================================

Button::Button(int locX, int locY, int wid, int hei, int val, std::string text,
	GraphicFont* aFont, std::string description)
{
	x = locX; y = locY; xSize = wid; ySize = hei;
	value = val; label = text;
	theFont = aFont;
	hover = description;
}

int Button::getVal(int locX, int locY)
{
	if (enabled && x <= locX && locX <= x + xSize && y <= locY && locY <= y + ySize)
		return value;
	else
		return FSKEY_NULL;

}

void Button::paintHover(int locX, int locY)
{
	if (hover.length() > 0 && x <= locX && locX <= x + xSize && y <= locY && locY <= y + ySize) {
		string message = "";

		if (!enabled) {
			glColor3ub(155, 155, 0);
			message += "DISABLED: ";
		}
		else
			glColor3ub(255, 255, 0);

		message += hover;
		message = StringPlus::wrapLongLine(message, 20);
		vector<string> messageLines = StringPlus::split(message, "\n");

		DrawingUtilNG::drawRectangle(x + 5, y + ySize + 5, 100, 10 + messageLines.size() * 10, true);
		glColor3ub(0, 0, 0);
		DrawingUtilNG::drawRectangle(x + 5, y + ySize + 5, 100, 10 + messageLines.size() * 10, false);

		int yAdjust = ySize + 20;
		for (auto aLine : messageLines) {
			theFont->drawText(aLine, x + 7, y + yAdjust, .1);
			yAdjust += 10;
		}
	}

}

void Button::paint()
{
	//int x = this->x, y=this->y; // these will now be local to this function
	int wid, hei;
	FsGetWindowSize(wid, hei);

	//if (horzAnchor == RIGHT)  // haven't got this to work yet
	//	x = wid - this->x;

	//if (vertAnchor == BOTTOM)
	//	y = hei - this->y;

	// top light
	glColor3ub(230, 230, 230);
	DrawingUtilNG::drawRectangle(x, y, xSize, ySize, true);

	// bottom shadow
	glColor3ub(110, 110, 110);
	glBegin(GL_QUADS);
	glVertex2i(x, y + ySize);
	glVertex2i(x + ySize / 2, y + ySize / 2);
	glVertex2i(x + xSize, y + ySize / 2);
	glVertex2i(x + xSize, y + ySize);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex2i(x + xSize, y);
	glVertex2i(x + xSize, y + ySize);
	glVertex2i(x + xSize - ySize / 2, y + ySize / 2);
	glEnd();

	// flat
	glColor3ub(210, 210, 210);
	int border = 3;
	DrawingUtilNG::drawRectangle(x + border, y + border, xSize - border * 2, ySize - border * 2, true);

	if (enabled)
		theFont->setColorRGB(0, 0, 0);
	else
		theFont->setColorRGB(.4, .4, .4);

	int letterHei = theFont->getLetterHeight();
	theFont->drawText(label, x + xSize / 2, y + ySize / 2, (float)(ySize - 8) / letterHei, 0, true);

}

void Button::setAnchor(AnchorMode horz, AnchorMode vert)
{
	horzAnchor = horz; 
	vertAnchor = vert; 

	// change x and y from current position into relative from window frame
	int wid, hei;
	FsGetWindowSize(wid, hei);
	
	//if (horzAnchor == RIGHT) 
	//	x = wid - x;
	//
	//if (vertAnchor == BOTTOM)
	//	y = hei - y;

}