/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Music.h
 * Control the musics in game.
 */

#ifndef INCLUDE_MUSIC_H_
#define INCLUDE_MUSIC_H_

#include <memory>
#include <string>

#include "SDL_mixer.h"
#include "easylogging++.h" //NOLINT

using std::string;
using std::shared_ptr;

class Music {
 private:
    shared_ptr<Mix_Music> music;

 public:
 	/**
	 * The constructor.
	 * Initialize the music null
	 * container coordinates of the Music class.
	 */
    Music();

    /**
	 * The constructor
	 * Initialize the music
	 * container coordinates of the Music class.
	 *
	 * @param file is the file where is the music.
	 */
    explicit Music(string file);


	/**
	 * Play the music
	 *
	 * @param times is the times to play the music
	 */
    void play(int times = -1);

    /**
	 * Stop the music
	 */
    void stop();

	/**
	 * Open the object music
	 *
	 * @param file is where is the music.
	 */
    void open(string file);

    /**
	 * Check if the music is open
	 *
	 * @returns if the music was open
	 */
    bool is_open();
};

#endif  // INCLUDE_MUSIC_H_
