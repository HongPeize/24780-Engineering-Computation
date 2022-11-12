//
//  sound_manager.cpp
//  individual project
//
//  Created by James Hong on 24/10/2022.
//

#include "sound_manager.h"

using namespace std;

void sound_track::play_song(string song_name, YsSoundPlayer &player, YsSoundPlayer::SoundData &myWav){

//    YsSoundPlayer player1;
//    YsSoundPlayer::SoundData myWav1;

    int playStyle = 1; //play once
    if (YSOK == myWav.LoadWav(song_name.c_str())) {
        //myWav1.LoadWav(song_name.c_str());
        
        // start the player after opening window
        player.Start();
        
        if (playStyle == 1) {
            player.PlayOneShot(myWav);
            cout << "\n\n\t\t\tDone starting OneShot" << endl;
        }
        else {
            player.PlayBackground(myWav);
            cout << "\n\n\t\t\tDone starting Background" << endl;
        }
        // common courtesy to close player, although destructor of player
        // will end player when variable passes "out of scope" at end of main()
        player.End();
        //return 0;
    }
    else {
        cout << "Failed to read " << song_name << endl;
    }
}
