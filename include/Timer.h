/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Timer.h
 * Control the timer in game.
 */

#ifndef INCLUDE_TIMER_H_
#define INCLUDE_TIMER_H_

#include "easylogging++.h" //NOLINT

class Timer {
 private:
    float time; /**< The time of the timer. */

 public:
 	/**
	 * Initialize a timer
	 */
    Timer();

	/**
	 * Update the timer
	 *
	 * @param delta is the variation of the time 
	 */
    void update(float delta);

	/**
	 * Restart the timer
	 */
    void restart();

    /**
	 * Check the timer
	 *
	 * @return the time of the timer
	 */
    float get();

    /**
	 * Insert a timer
	 *
	 * @param ctime is the time to be put in timer
	 */
    void set(float ctime);
};

#endif  // INCLUDE_TIMER_H_
