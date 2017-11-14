/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Music.cpp
 * Brief Description.
 */

#include "Music.h"

#include "Config.h"
#include "Resources.h"

/**
 * Brief Description.
 */
Music::Music() {
    music = nullptr;
}

/**
 * Brief Description.
 *
 * @param file
 */
Music::Music(string file) {
    this->open(file);
}

/**
 * Brief Description.
 *
 * @param times
 */
void Music::play(int times) {
    int mix_play_music = Mix_PlayMusic(music.get(), times);
    if (mix_play_music) {
        printf("Play music: %s\n", Mix_GetError());
        exit(-1);
    }
}

/**
 * Brief Description.
 */
void Music::stop() {
    int mix_fade_out_music = Mix_FadeOutMusic(0);
    if (!mix_fade_out_music) {
        printf("Stop music: %s\n", Mix_GetError());
        exit(-1);
    }
}

/**
 * Brief Description.
 *
 * @param file
 */
void Music::open(string file) {
    music = Resources::get_music(RESOURCES_FOLDER + file);
}

/**
 * Brief Description.
 *
 * @returns
 */
bool Music::is_open() {
    return music != nullptr;
}
