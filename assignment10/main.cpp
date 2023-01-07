////
////  main.cpp
////  assignment10
////
////  Created by James Hong on 2022-11-22.
////
//
//#include <iostream>
//#include "QuadraticFit.h"
//#include "fssimplewindow.h"
//#include "DrawingUtilNG.h"
//
//int main() {
//    ifstream myFile;
//    string Name;
//    bool showPoints = false;
//    pair<double, double> Coefficient;
//    QF QuadFit;
//
//    QuadFit.showMenu();
//
//    int winWidth = 800, winHeight = 600;
//    int panX = 0;
//    int panY = 0;
//    float scale = 1.0;
//    FsOpenWindow(16, 16, winWidth, winHeight, 1, "PS10 (PH 2022)");
//    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
//    int key = FSKEY_NULL;
//
//    while (key != FSKEY_ESC) {
//        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
//        glLoadIdentity();
//        FsPollDevice();
//        key = FsInkey();
//        glColor3ub(255, 0, 0);
//
//        switch (key) {
//            case FSKEY_L:
//                cout << "Name of File: ";
//                cin >> Name;
//                if (Name.length() > 0) {
//
//                    if (Name.find(".txt") == string::npos)
//                        Name += ".txt";
//
//                    myFile.open(Name);
//                    if (myFile.is_open()) {
//                        QuadFit.readFile(myFile);
//                        myFile.close();
//                        cout << "       A new dataset was loaded from file " << Name << endl;
//                        Coefficient = QuadFit.fit();
////                        cout << Coefficient.first << endl;
////                        cout << Coefficient.second << endl;
//                    }
//                    else
//                        cout << "       ERROR: Was not able to open file " << Name << endl;
//                }
//                break;
//            case FSKEY_S:
//                showPoints = !showPoints;
//                break;
//            case FSKEY_RIGHT: panX += 5;
//                break;
//            case FSKEY_LEFT: panX -= 5;
//                break;
//            case FSKEY_UP: panY -= 5;
//                break;
//            case FSKEY_DOWN: panY += 5;
//                break;
//            case FSKEY_PLUS: scale *= 1.05;
//                break;
//            case FSKEY_MINUS: scale /= 1.05;
//                break;
//            case FSKEY_R: panX = 0; panY = 0; scale = 1;
//                break;
//        }
//        glTranslatef(panX, panY, 0);
//        glScalef(scale, scale, 1);
//        QuadFit.paintFit(winWidth, winHeight, showPoints, panX, panY, scale);
//
//        FsSwapBuffers();
//        FsSleep(15);
//    }
//
//    return 0;
//}


#include <iostream>
#include <fstream>
#include "fssimplewindow.h"
#include "DataManager.h"

using namespace std;

int main() {
  // set up track manager
  DataManager theManager(900, 600);

  theManager.showMenu();

  while (theManager.manage()) {
      // actually display graphics
      FsSwapBuffers();

      // prepare for next loop
      FsSleep(25);
  }

  return 0;
}

