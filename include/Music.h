/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Music.h
 * Brief Description.
 */

#ifndef INCLUDE_MUSIC_H_
#define INCLUDE_MUSIC_H_

#include "SDL_mixer.h"
#include "easylogging++.h"

#include <memory>
#include <string>

using std::string;
using std::shared_ptr;

class Music {
 private:
    shared_ptr<Mix_Music> music;

 public:
    Music();
    explicit Music(string file);

    void play(int times = -1);
    void stop();
    void open(string file);
    bool is_open();
};

#endif  // INCLUDE_MUSIC_H_
