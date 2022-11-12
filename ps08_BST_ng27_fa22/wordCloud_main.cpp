/*
Nestor Gomez
24-780B Engineering Computation
PS08 - Binary Search Tree (pointer implementation)
Due Tues, Nov. 15, 2022

This source file contains main() function for testing and for generating 
primitive wordcloud.

*/

//#pragma warning(disable:4996)
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <math.h>
#include <ctype.h>
#include <string>

#include "fssimplewindow.h"
#include "GraphicFont.h"
#include "DrawingUtilNG.h"
#include "StringPlus.h"

#include "BST.h"

using namespace std;

void readFile(const string fileName, BST<string, TreeNode<string>>& tree);
void printMenu();
int randBetween(int low, int high);
void setRandomCoords(int* xCoords, int* yCoords,   // call by reference on array
	int size, int minX, int maxX, int minY, int maxY);
void setRandomColors(int* colors, int size);

int main(void)
{
	// seed random generator
	srand(time(NULL));

	BST<string, TreeNode<string>> myTree;
	stringstream fullStream;

	readFile("Gettysburg.txt", myTree);
	//readFile("GettysburgShort.txt", myTree);
	fullStream.str("");
	myTree.printInOrder(fullStream);
	cout << fullStream.str();

	cout << endl << string(60, '=') << endl << endl; // long line of ========

	//myTree.deleteItem("the"); // this is a node with single child

	//myTree.deleteItem("that"); // this is a node with two children

	//myTree.deleteItem("equal"); // this is the root node (special case)

	fullStream.str("");
	myTree.printInOrder(fullStream);
	cout << fullStream.str();

	cout << endl << "The root of tree is '" << myTree.root()->theItem << "'" << endl;
	int i = 1;

	cout << "The word 'nation' appears " << myTree.retrieveItemCount("nation") << " times." << endl;
	cout << "The word 'superman' appears " << myTree.retrieveItemCount("superman") << " times." << endl;

	// testing of BST ends here. The rest of the code is for implementing wordcloud

	using namespace DrawingUtilNG;
	int scrnWid = 1100, scrnHei = 800;
	// must "open window" before declaring fonts
	FsOpenWindow(16, 16, scrnWid, scrnHei, 1, "Word Cloud");

	int key = FSKEY_NULL;

	// select a font by uncommenting only one line
	//ImpactFont myFont;
	//GaramondFont myFont;
	//JokermanFont myFont;
	//ComicSansFont myFont;
	TimesNewRomanFont myFont;
	//OldEnglishFont myFont;
	//CourierNewFont myFont;
	//ArialFont myFont;

	int maxNodeCount = myTree.count();
	int currCount;
	string currString;
	TreeNode<string> currNode;
	float baseScale = 0.2;

	// generate random screen locations and colors (storing random so we can use over and over)
	int* randX = new int[maxNodeCount];
	int* randY = new int[maxNodeCount];
	int* randC = new int[maxNodeCount];

	setRandomCoords(randX, randY, maxNodeCount,
		scrnWid * 0.1, scrnWid * 0.9,
		scrnHei * 0.1, scrnHei * 0.9);
	setRandomColors(randC, maxNodeCount);

	bool rainbowColors = true;

	// tree of unwanted words
	BST<string, TreeNode<string>> unwantedTree;
	unwantedTree.insertItem("it");
	unwantedTree.insertItem("the");
	unwantedTree.insertItem("that");
	unwantedTree.insertItem("and");
	unwantedTree.insertItem("a");
	unwantedTree.insertItem("to");
	unwantedTree.insertItem("of");
	bool showAll = false;
	bool showCount = false;
	int lowerLimit = 1;

	printMenu();

	// make copy of tree as ordered vector
	fullStream.str("");
	myTree.printInOrder(fullStream);
	vector<string> allData = StringPlus::split(fullStream.str(), " {}\n");

	while (FSKEY_ESC != key)
	{
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		// draw black rectangle
		glColor3d(0.0, 0.0, 0.0);
		drawRectangle(0, 0, scrnWid, scrnHei, true);

		// draw words

		for (int i = 0; i < allData.size(); i += 2) {
			currString = allData.at(i);
			currCount = stoi(allData.at(i + 1)); // convert from string to integer

			if (rainbowColors)
				myFont.setColorHSV(randC[i / 2], 1, 1, .6);
			else
				myFont.setColorHSV(280, 1, 1, .6); // purple


			if (currCount > lowerLimit && (showAll || unwantedTree.retrieveItemCount(currString) == 0)) {
				myFont.drawText(currString, randX[i / 2], randY[i / 2],
					baseScale * currCount, 0, true);
				if (showCount) {
					float width = myFont.getWordWidth(currString, baseScale * currCount);
					myFont.drawText("(" + to_string(currCount) + ")", randX[i / 2] + width/2., randY[i / 2],
						baseScale, 0, false);
				}
			}
		}

		FsPollDevice();
		switch (key = FsInkey()) {
		case FSKEY_UP: // zooming in
			baseScale *= 1.1;
			break;
		case FSKEY_DOWN: // zooming out
			baseScale /= 1.1;
			break;

		case FSKEY_C: // toggle unwanted words on or off
			showCount = !showCount;
			break;
		case FSKEY_U: // toggle unwanted words on or off
			showAll = !showAll;
			break;
		case FSKEY_A: // toggle single-use words on or off
			if (lowerLimit == 1)
				lowerLimit = 0;
			else
				lowerLimit = 1;
			break;
		case FSKEY_R: // toggle rainbow colors on or off
			rainbowColors = !rainbowColors;
			break;

		case FSKEY_SPACE: // Re-order
			setRandomCoords(randX, randY, maxNodeCount,
				scrnWid * 0.1, scrnWid * 0.9,
				scrnHei * 0.1, scrnHei * 0.9);
			setRandomColors(randC, maxNodeCount);
			break;
		}

		FsSwapBuffers();
		FsSleep(30);

	}

	// just to be nice and polite
	delete[]randX;
	delete[]randY;
	delete[]randC;
}

void readFile(string fileName, BST<string, TreeNode<string>>& tree)
{
	string tempStr;
	string delim = " .,;:!?-=+/\\\"\'[]()|\t\n\r";  // did I miss any ?

	ifstream inFile(fileName);
	if (inFile.is_open()) { // may not have found file

		while (!inFile.eof()) {
			// read whole line
			getline(inFile, tempStr);

			// split line into words
			vector<string> tokens = StringPlus::split(tempStr, delim);

			// insert each of the words into BST (faster to do it "backwards" when popping)
			while (!tokens.empty()) {
				tree.insertItem(StringPlus::lowerCase(tokens.back()));
				tokens.pop_back();
			}
		}
		inFile.close();
	}
}

void printMenu()
{
	cout << endl << endl << "Instructions: " << endl;
	cout << "    Arrow UP to zoom in." << endl;
	cout << "    Arrow DOWN to zoom out." << endl;
	cout << "    'U' to toggle display of \"common\" words." << endl;
	cout << "    'A' to toggle display of single-use words." << endl;
	cout << "    'C' to toggle display of word count." << endl;
	cout << "    'R' to toggle rainbow colors mode." << endl;
	cout << "  SPACE to regenerate graphics." << endl;
	cout << endl;
}

int randBetween(int low, int high) {
	return low + ((double)rand() / RAND_MAX * (high - low));
}

void setRandomCoords(int* xCoords, int* yCoords,   // call by reference
	int size, int minX, int maxX, int minY, int maxY) {
	for (int i = 0; i < size; i++) {
		xCoords[i] = randBetween(minX, maxX);
		yCoords[i] = randBetween(minY, maxY);
	}
}

void setRandomColors(int* colors, int size) {
	for (int i = 0; i < size; i++) {
		colors[i] = randBetween(0, 35) * 10; // 0 to 350 by tens
	}
}
