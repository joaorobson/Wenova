/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 * 
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/** 
 * @file Sound.cpp
 * Implements class Sound methods.  
 */

#include "Sound.h"
#include "Resources.h"
#include "Config.h"

/**
 * The constructor.
 * Initialize the sound null
 * container coordinates of the Sound class.
 */
Sound::Sound() {
    file = "";
    sound = nullptr;
}

/**
 * The constructor.
 * Initialize the sound
 * container coordinates of the Sound class.
 *
 * @param cfile is the file where is the sound
 */
Sound::Sound(string cfile) {
    file = cfile;
    this->open(cfile);
}

/**
 * Play a sound
 *
 * @param times is the times to play the sound
 */
void Sound::play(int times) {
    channel = Mix_PlayChannel(-1, sound.get(), times);
    /**
     * Check if sound played
     */
    if (channel == -1) {
        printf("Play chunk: %s\n", Mix_GetError());
        exit(-1);
    }
}

/**
 * Stop the sound
 */
void Sound::stop() {
    Mix_HaltChannel(channel);
}

/**
 * Open the sound
 *
 * @param cfile is where is the sound.
 */
void Sound::open(string cfile) {
    sound = Resources::get_sound(RESOURCES_FOLDER + cfile);
}

/**
 * Check if the sound is open
 */
bool Sound::is_open() {
    return sound != nullptr;
}

/**
 * Check the file of the sound
 *
 * @return the file of the sound
 */
string Sound::get_file() {
    return file;
}

