//
//  sound_manager.h
//  individual project
//
//  Created by James Hong on 24/10/2022.
//

#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include "yssimplesound.h"
#include "fssimplewindow.h"
using namespace std;

class sound_track{
public:
    void play_song(string song_name, YsSoundPlayer &player, YsSoundPlayer::SoundData &myWav);
};
