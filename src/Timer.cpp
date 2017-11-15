/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Timer.cpp
 * Brief Description.
 */

#include "Timer.h"

/**
 * Brief Description.
 */
Timer::Timer() {
    time = 0;
}

/**
 * Brief Description.
 *
 * @param delta
 */
void Timer::update(float delta) {
    time += delta;
}

/**
 * Brief Description.
 */
void Timer::restart() {
    time = 0;
}

/**
 * Brief Description.
 *
 * @returns
 */
float Timer::get() {
    return time;
}

/**
 * Brief Description.
 *
 * @param ctime
 */
void Timer::set(float ctime) {
    time = ctime;
}
