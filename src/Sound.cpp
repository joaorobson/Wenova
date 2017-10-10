/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Sound.cpp
 * Brief Description.
 */

#include "Sound.h"

#include "Config.h"
#include "Resources.h"

/**
 * Brief Description.
 */
Sound::Sound() {
    file = "";
    sound = nullptr;
	channel = 0;
}

/**
 * Brief Description.
 *
 * @param cfile
 */
Sound::Sound(string cfile) {
    file = cfile;
    this->open(cfile);
	channel = 0;
}

/**
 * Brief Description.
 *
 * @param times
 */
void Sound::play(int times) {
    channel = Mix_PlayChannel(-1, sound.get(), times);
    if (channel == -1) {
        printf("Play chunk: %s\n", Mix_GetError());
        exit(-1);
    }
}

/**
 * Brief Description.
 */
void Sound::stop() {
    Mix_HaltChannel(channel);
}

/**
 * Brief Description.
 *
 * @param cfile
 */
void Sound::open(string cfile) {
    sound = Resources::get_sound(RESOURCES_FOLDER + cfile);
}

/**
 * Brief Description.
 *
 * @returns
 */
bool Sound::is_open() {
    return sound != nullptr;
}

/**
 * Brief Description.
 *
 * @returns
 */
string Sound::get_file() {
    return file;
}
