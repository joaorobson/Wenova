/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 * 
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/** 
 * @file Timer.cpp
 * Implements class Timer methods.
 */

#include "Timer.h"

#include <assert.h>

#define INITIAL_TIME 0

/**
 * Initialize a timer
 */
Timer::Timer() {
    LOG(DEBUG) << "Timer initialized";
    time = INITIAL_TIME;
}

/**
 * Update the timer
 *
 * @param delta is the variation of the time 
 */
void Timer::update(float delta) {
    LOG(DEBUG) << "Timer uptaded";
    assert(delta >=0);
    time += delta;
}

/**
 * Restart the timer
 */
void Timer::restart() {
    LOG(DEBUG) << "Timer is restarting";
    time = INITIAL_TIME;
}

/**
 * Check the timer
 *
 * @return the time of the timer
 */
float Timer::get() {
    return time;
}

/**
 * Insert a timer
 *
 * @param ctime is the time to be put in timer
 */
void Timer::set(float ctime) {
    time = ctime;
}
