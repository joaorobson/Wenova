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

/*
 * The constructor.
 * Initialize the music null
 * container coordinates of the Music class.
 */
Music::Music() {
    music = nullptr;
}

/*
 * The constructor
 * Initialize the music
 * container coordinates of the Music class.
 *
 * @param file is the file where is the music.
 */
Music::Music(string file) {
    this->open(file);
}

/*
 * Play the music
 *
 * @param times is the times to play the music
 */
void Music::play(int times) {
    int mix_play_music = Mix_PlayMusic(music.get(), times);
    if(mix_play_music) {
        printf("Play music: %s\n", Mix_GetError());
        exit(-1);
    }
}

/*
 * Stop the music
 */
void Music::stop() {
    int mix_fade_out_music = Mix_FadeOutMusic(0);
    if(not mix_fade_out_music) {
        printf("Stop music: %s\n", Mix_GetError());
        exit(-1);
    }
}

/*
 * Open the object music
 *
 * @param file is where is the music.
 */
void Music::open(string file) {
    music = Resources::get_music(RES_FOLDER + file);
}

/*
 * Check if the music is open
 */
bool Music::is_open() {
    return music != nullptr;
}
