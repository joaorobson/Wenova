/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 * 
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/** 
 * @file Music.cpp
 * Implements class Music methods.  
 */

#include "Music.h"
#include "Resources.h"
#include "Config.h"

//Create the object "music" null
Music::Music() {
    music = nullptr;
}

//Create the object "music" complete
Music::Music(string file) {
    this->open(file);
}

//Play the music
void Music::play(int times) {
    int mix_play_music = Mix_PlayMusic(music.get(), times);
    if(mix_play_music) {
        printf("Play music: %s\n", Mix_GetError());
        exit(-1);
    }
}

//Stop the music
void Music::stop() {
    int mix_fade_out_music = Mix_FadeOutMusic(0);
    if(not mix_fade_out_music) {
        printf("Stop music: %s\n", Mix_GetError());
        exit(-1);
    }
}

//Open the object music
void Music::open(string file) {
    music = Resources::get_music(RES_FOLDER + file);
}

//Check if the music is open
bool Music::is_open() {
    return music != nullptr;
}
