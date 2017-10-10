/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Sound.h
 * Brief Description.
 */

#ifndef INCLUDE_SOUND_H_
#define INCLUDE_SOUND_H_

#include "SDL_mixer.h"

#include <memory>
#include <string>

using std::string;
using std::shared_ptr;

class Sound {
 private:
    shared_ptr<Mix_Chunk> sound;
    int channel;
    string file;

 public:
    Sound();
    explicit Sound(string cfile);

    void play(int times = 0);  // plays 1 time with times = 0
    void stop();
    void open(string cfile);
    bool is_open();
    string get_file();
};

#endif  // INCLUDE_SOUND_H_
