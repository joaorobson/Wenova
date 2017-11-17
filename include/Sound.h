/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Sound.h
 * Control all the sounds in game.
 */

#ifndef INCLUDE_SOUND_H_
#define INCLUDE_SOUND_H_

#include <memory>
#include <string>

#include "SDL_mixer.h"
#include "easylogging++.h" //NOLINT

using std::string;
using std::shared_ptr;

class Sound {
 private:
    shared_ptr<Mix_Chunk> sound;
    int channel;
    string file;

 public:
    /**
     * The constructor.
     * Initialize the sound null
     * container coordinates of the Sound class.
     */
    Sound();

    /**
     * The constructor.
     * Initialize the sound
     * container coordinates of the Sound class.
     *
     * @param cfile is the file where is the sound
     */
    explicit Sound(string cfile);


    /**
     * Play a sound
     *
     * @param times is the times to play the sound
     */
    void play(int times = 0);  // plays 1 time with times = 0

    /**
     * Stop the sound
     */
    void stop();

    /**
     * Open the sound
     *
     * @param cfile is where is the sound.
     */
    void open(string cfile);

    /**
     * Check if the sound is open
     *
     * @return if the sound was open
     */
    bool is_open();

    /**
     * Check the file of the sound
     *
     * @return the file of the sound
     */
    string get_file();
};

#endif  // INCLUDE_SOUND_H_
