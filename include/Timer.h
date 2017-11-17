/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file Timer.h
 * Brief Description.
 */

#ifndef INCLUDE_TIMER_H_
#define INCLUDE_TIMER_H_

#include "easylogging++.h"

class Timer {
 private:
    float time;

 public:
    Timer();
    void update(float delta);
    void restart();
    float get();
    void set(float ctime);
};

#endif  // INCLUDE_TIMER_H_
