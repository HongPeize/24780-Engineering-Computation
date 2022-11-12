//
//  idp.cpp
//  individual project
//
//  Created by James Hong on 23/10/2022.
//

#include <iostream>
#include <string>
#include "Object_in.h"
#include "sound_manager.h"
#include "fssimplewindow.h"
#include "ysglfontdata.h"

void paint_cover(int winWid, int winHei, int choice){
    if (choice==1){
        YsRawPngDecoder pngTemp;
        pngTemp.Decode("cover.png");
        
        double scale1 = 0.62;
        int xSize = pngTemp.wid * scale1; // need for later
        int ySize = pngTemp.hei * scale1;
        
        GLuint textureId01; // this will be used as texture identifier for the second PNG (DON'T LOSE IT)
        
        glGenTextures(1, &textureId01); // Reserve texture identifier for other PNG
        glBindTexture(GL_TEXTURE_2D, textureId01); // Making the texture identifier current (or bring it to the deck)
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pngTemp.wid, pngTemp.hei, 0, GL_RGBA, GL_UNSIGNED_BYTE, pngTemp.rgba);
        
        int wid, hei;
        FsGetWindowSize(wid, hei); // nice little function
        
        // in order for textures to show, you must create a projection
        glViewport(0, 0, wid, hei);
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glColor4d(1.0, 1.0, 1.0, 1.0); // this color will "tint" the image
        
        // enable texture mapping
        glEnable(GL_TEXTURE_2D);
        
        // bind a texture to OpenGL primitives
        glBindTexture(GL_TEXTURE_2D, textureId01); // imageSample (a bird)
        
        
        //left side trees
        glBegin(GL_QUADS);
        
        // For each vertex, assign texture coordinate before vertex coordinate.
        glTexCoord2d(0.0, 0.0); // these are "percentage" of the image
        glVertex2i(winWid, winHei); // these are actual pixel coordinates on screen
        
        glTexCoord2d(1.0, 0.0);
        glVertex2i((winWid + xSize), winHei);
        
        glTexCoord2d(1.0, 1.0);
        glVertex2i((winWid + xSize), (winHei + ySize)); // kept xSize and ySize for this purpose
        
        glTexCoord2d(0.0, 1.0);
        glVertex2i(winWid, (winHei + ySize));
        
        glEnd();
    }
    else if (choice==2){
        YsRawPngDecoder pngTemp;
        pngTemp.Decode("Overspeed.png");
        
        double scale2 = 1.5;
        int xSize = pngTemp.wid * scale2; // need for later
        int ySize = pngTemp.hei * scale2;
        
        GLuint textureId02; // this will be used as texture identifier for the second PNG (DON'T LOSE IT)
        
        glGenTextures(1, &textureId02); // Reserve texture identifier for other PNG
        glBindTexture(GL_TEXTURE_2D, textureId02); // Making the texture identifier current (or bring it to the deck)
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pngTemp.wid, pngTemp.hei, 0, GL_RGBA, GL_UNSIGNED_BYTE, pngTemp.rgba);
        
        int wid, hei;
        FsGetWindowSize(wid, hei); // nice little function
        
        // in order for textures to show, you must create a projection
        glViewport(0, 0, wid, hei);
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glColor4d(1.0, 1.0, 1.0, 1.0); // this color will "tint" the image
        
        // enable texture mapping
        glEnable(GL_TEXTURE_2D);
        
        // bind a texture to OpenGL primitives
        glBindTexture(GL_TEXTURE_2D, textureId02); // imageSample (a bird)
        
        
        //left side trees
        glBegin(GL_QUADS);
        
        // For each vertex, assign texture coordinate before vertex coordinate.
        glTexCoord2d(0.0, 0.0); // these are "percentage" of the image
        glVertex2i(winWid, winHei); // these are actual pixel coordinates on screen
        
        glTexCoord2d(1.0, 0.0);
        glVertex2i((winWid + xSize), winHei);
        
        glTexCoord2d(1.0, 1.0);
        glVertex2i((winWid + xSize), (winHei + ySize)); // kept xSize and ySize for this purpose
        
        glTexCoord2d(0.0, 1.0);
        glVertex2i(winWid, (winHei + ySize));
        
        glEnd();
    }
    else if (choice==3){
        YsRawPngDecoder pngTemp;
        pngTemp.Decode("drive_safely.png");
        
        double scale2 = 1.5;
        int xSize = pngTemp.wid * scale2; // need for later
        int ySize = pngTemp.hei * scale2;
        
        GLuint textureId02; // this will be used as texture identifier for the second PNG (DON'T LOSE IT)
        
        glGenTextures(1, &textureId02); // Reserve texture identifier for other PNG
        glBindTexture(GL_TEXTURE_2D, textureId02); // Making the texture identifier current (or bring it to the deck)
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pngTemp.wid, pngTemp.hei, 0, GL_RGBA, GL_UNSIGNED_BYTE, pngTemp.rgba);
        
        int wid, hei;
        FsGetWindowSize(wid, hei); // nice little function
        
        // in order for textures to show, you must create a projection
        glViewport(0, 0, wid, hei);
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glColor4d(1.0, 1.0, 1.0, 1.0); // this color will "tint" the image
        
        // enable texture mapping
        glEnable(GL_TEXTURE_2D);
        
        // bind a texture to OpenGL primitives
        glBindTexture(GL_TEXTURE_2D, textureId02); // imageSample (a bird)
        
        
        //left side trees
        glBegin(GL_QUADS);
        
        // For each vertex, assign texture coordinate before vertex coordinate.
        glTexCoord2d(0.0, 0.0); // these are "percentage" of the image
        glVertex2i(winWid, winHei); // these are actual pixel coordinates on screen
        
        glTexCoord2d(1.0, 0.0);
        glVertex2i((winWid + xSize), winHei);
        
        glTexCoord2d(1.0, 1.0);
        glVertex2i((winWid + xSize), (winHei + ySize)); // kept xSize and ySize for this purpose
        
        glTexCoord2d(0.0, 1.0);
        glVertex2i(winWid, (winHei + ySize));
        
        glEnd();
    }
}

int main() {
    int scene = 1;
    int winWidth = 800, winHeight = 600;
    string song1 = "running_up_that_hill.wav";
    string song2 = "Accel.wav";
    string song3 = "car_accident.wav";
    string song4 = "road_safety.wav";
    string song5 = "drive_overspeed.wav";

    YsSoundPlayer player1;
    YsSoundPlayer::SoundData myWav1;
    YsSoundPlayer player2;
    YsSoundPlayer::SoundData myWav2;
    YsSoundPlayer player3;
    YsSoundPlayer::SoundData myWav3;
    int i = 0;
    int v = 20;
    sound_track aSong;
    road aRoad;
    tree Trees;
    car aCar;
    trafficlight aLight;
    people aMan;
    speed_limit aSign;
    FsOpenWindow(16, 16, winWidth, winHeight, 1, "Individual Project (PH 2022)");
    bool a=true, b=true, c=true, d=true;
    
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    int key = FSKEY_NULL;
    while (key != FSKEY_ESC) {
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        FsPollDevice();
        key = FsInkey();

        //scene 1
        if (i<=100){
            if (a==true){
                aSong.play_song(song4, player1, myWav1);
                a=false;
            }
            paint_cover(2, 80, scene);
        }

        if (i>100 && i<=360){
            if (b==true){
                aSong.play_song(song1, player1, myWav1);
                b=false;
            }
            aRoad.move();
            Trees.move();
            aRoad.paint();
            Trees.paint();

            aCar.paint(i);
            if (i>135 && i<=180){
                if (Trees.tree_step >0){Trees.tree_step -= 0.12;}
                if (aRoad.road_step >0){aRoad.road_step -= 0.007;}
                if (aLight.light_step >0){aLight.light_step -= 0.3;}
            }

            if (i > 144){
                aRoad.move_cross();
                aRoad.paint_cross();
                aRoad.move_strip_horz();
                aRoad.paint_strip_horz();
                if (i <=310){
                    aLight.move_yellow();
                    aLight.paint_yellow();
                }
                if (i <= 190){
                    glColor3ub(255, 0, 0);
                    glRasterPos2i(winWidth*0.22, winHeight*0.5);  // sets position
                    YsGlDrawFontBitmap20x32("When see the yellow light,");
                    glRasterPos2i(winWidth*0.22, winHeight*0.58);  // sets position
                    YsGlDrawFontBitmap20x32("please slow down.");
                }
            }
            if (i<=250 && i > 180){
                aRoad.active = false;
                aRoad.cross_active = false;
                Trees.active = false;
                aLight.active = false;
                aLight.paint_red();
                if (i > 195){
                    glColor3ub(255, 0, 0);
                    glRasterPos2i(winWidth*0.25, winHeight*0.5);  // sets position
                    YsGlDrawFontBitmap20x32("Stop at the red light.");
                }
            }

            if (i<=290 && i>250){
                aLight.paint_green();
                glColor3ub(255, 0, 0);
                glRasterPos2i(winWidth*0.08, winHeight*0.5);  // sets position
                YsGlDrawFontBitmap20x32("When green light, you can turn right,");
                glRasterPos2i(winWidth*0.08, winHeight*0.6);  // sets position
                YsGlDrawFontBitmap20x32("turn left or go forward.");
                aRoad.paint_arrow();
            }

            if (i<=317 && i >290){
                Trees.tree_step = 10.0;
                aRoad.road_step = 0.5;
                aLight.light_step = 20;
                
                aRoad.paint_other_half_cross();
                
                aRoad.active = true;
                aRoad.cross_active = true;
                aLight.active = true;
                Trees.active = true;
                if (i <= 310){aLight.paint_green();}
                aCar.paint(i);
            }
            if (i>317 && i <=327){
                aRoad.active = false;
                aRoad.cross_active = false;
                aLight.active = false;
                Trees.active = false;
                aRoad.paint_other_half_cross();

                aCar.paint(i); //do rotation
            }
            if (i <= 360 && i>327){
                aRoad.paint_other_half_cross();
                aCar.move();
                aCar.paint(i);
            }
         }
        
        //scene 2
        
        if (i<=600 && i>360){
            //cover page
            if(i<=420 && i>360){
                if (d == true){
                    aSong.play_song(song5, player2, myWav2);
                    d = false;
                }
                scene = 2;
                paint_cover(0, 0, scene);
                glColor3ub(255, 0, 0);
                glRasterPos2i(winWidth*0.3, winHeight*0.4);  // sets position
                YsGlDrawFontBitmap20x32("Don't Drive Overspeed!");
            }
            aCar.locX1 = 300;
            string speed = to_string(v);
            //road move until hit people
            if(i>420){
                if (c == true){
                    aSong.play_song(song2, player2, myWav2);
                    c = false;
                }
                aRoad.active = true; Trees.active = true;
                aRoad.accel();
                Trees.accel();
                aRoad.paint();
                Trees.paint();
                aCar.paint(i);
                //show speed limit sign
                aSign.paint();//show speed info
                if (i<=520){
                    glColor3ub(255, 0, 0);
                    glRasterPos2i(winWidth*0.25, winHeight*0.2);  // sets position
                    YsGlDrawFontBitmap20x32(speed.c_str());
                    glRasterPos2i(winWidth*0.3, winHeight*0.2);  // sets position
                    YsGlDrawFontBitmap20x32(" mph");
                    glRasterPos2i(winWidth*0.1, winHeight*0.5);  // sets position
                    YsGlDrawFontBitmap20x32("Do you think you're a racer?");
                    v++;
                }
            }
            //show speed info
            if(i>520){
                aRoad.zebra_crossing_move();
                aMan.move();
                aRoad.paint_zebra_crossing();
                aMan.paint();
                aSign.paint();//show speed info

                if (i<=539 && i>535){
                    glColor3ub(255, 0, 0);
                    DrawingUtilNG::drawStar(530, 420, 30.0, 10.0, 10, 36, true);
                }
                if (i==550){aMan.active = false; aRoad.active = false; Trees.active = false;}
                glColor3ub(255, 0, 0);
                glRasterPos2i(winWidth*0.25, winHeight*0.2);  // sets position
                YsGlDrawFontBitmap20x32(speed.c_str());
                glRasterPos2i(winWidth*0.3, winHeight*0.2);  // sets position
                YsGlDrawFontBitmap20x32(" mph");
                if (v<140){v++;}
                if (i<=575 && i>560){
                    glRasterPos2i(winWidth*0.25, winHeight*0.5);  // sets position
                    YsGlDrawFontBitmap20x32("No, you're a murderer!");
                }
            }
            if (i>575){
                glRasterPos2i(winWidth*0.25, winHeight*0.5);  // sets position
                YsGlDrawFontBitmap20x32("Drive Safely!!");
                scene = 3;
            }
        }
        
        if (i<=680 && i>600){
            paint_cover(-35, 50, scene);
        }
        if (i>680){
            glRasterPos2i(winWidth*0.05, winHeight*0.25);  // sets position
            YsGlDrawFontBitmap20x32("Thank you for watching.");
            glRasterPos2i(winWidth*0.05, winHeight*0.35);  // sets position
            YsGlDrawFontBitmap20x32("Image source:");
            glRasterPos2i(winWidth*0.05, winHeight*0.45);  // sets position
            YsGlDrawFontBitmap16x24("1. Road Safety: Learning Junction. Mar 2018");
            glRasterPos2i(winWidth*0.05, winHeight*0.55);  // sets position
            YsGlDrawFontBitmap16x24("2. Drive overspeed: AutoJosh, Jan 2022");
            glRasterPos2i(winWidth*0.05, winHeight*0.65);  // sets position
            YsGlDrawFontBitmap16x24("3. Drive safely: The Frontier Post, March 2013");
            glRasterPos2i(winWidth*0.05, winHeight*0.75);  // sets position
            YsGlDrawFontBitmap20x32("Song:");
            glRasterPos2i(winWidth*0.05, winHeight*0.85);  // sets position
            YsGlDrawFontBitmap16x24("Running up that hill - Kate Bush");
        }
        
        if (i>=850){
            key = FSKEY_ESC;
        }
        cout << "Time: " << i << endl;
        FsSwapBuffers();
        FsSleep(10);
        i++;
    }
    return 0;
}
