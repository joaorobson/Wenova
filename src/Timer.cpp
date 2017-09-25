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

//Initialize a timer
Timer::Timer() {
    time = 0;
}

//Update the timer
void Timer::update(float delta) {
    time += delta;
}

//Restart the timer
void Timer::restart() {
    time = 0;
}

//Check the timer
float Timer::get() {
    return time;
}

//Insert a timer
void Timer::set(float ctime) {
    time = ctime;
}
