#pragma once
#include <string>
#include <vector>
#include "fssimplewindow.h"

//#include "GraphicFont.h"
class GraphicFont;

class Button {
protected:
	int x = -1, y = -1;
	int xSize = -1, ySize = -1;
	int value = FSKEY_NULL;
	std::string label = "Button";
	std::string hover = "I do something";

	bool enabled = true;

	GraphicFont* theFont = nullptr;

public:
	Button() {};
	Button(int locX, int locY, int wid, int hei, int val, std::string text, 
		GraphicFont *aFont, std::string description);

	void disable() { enabled = false; };
	void enable() { enabled = true; };
	int getVal(int locX, int locY);
	int getVal() { return value; }
	void addHover(std::string newHover) { hover = newHover; }
	void paint();
	void paintHover(int locX, int locY);
};

class ButtonCollection {
protected:
	std::vector<Button> theButtons;
	
public:
	void add(int locX, int locY, int wid, int hei, int val, std::string text, 
		GraphicFont *aFont, std::string description = "");

	void remove(int val);
	void disableButton(int val);
	void enableButton(int val);

	int checkClick(int locX, int locY);
	void checkHover(int locX, int locY);

	void paint();

private:
	int getIndex(int val);
};