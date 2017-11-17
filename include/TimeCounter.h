/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */

/**
 * @file TimeCounter.h
 * This file contains the definitions of all methods and attributes of the class
 * TimeCounter.
 */
#ifndef INCLUDE_TIMECOUNTER_H_
#define INCLUDE_TIMECOUNTER_H_

#include "GameObject.h"
#include "Sprite.h"
#include "Text.h"
#include "Timer.h"

#include <assert.h>
#include <string>

using std::string;

class TimeCounter : public GameObject {
 public:
    static const int total_time = 100; /**< Const int number with duration */
                                       /**< of a battle. */
 private:
    Sprite background_clock; /**< Background image of the clock of a battle. */
    Timer timer;             /**< Timer of a battle with countdown. */
    Text time_text;          /**< Text that shows the remaining time on */
                             /**< screen during a battle. */
    float remaining_seconds; /**< Float number with the remaining time in */
                             /**< seconds. */

 public:
    /**
     * Constructor.
     * This constructor builds sprites and texts to indicate the remaining time
     * in a battle.
     */
    TimeCounter();

    /**
     * Destructor.
     * Nothing to do.
     */
    ~TimeCounter();

    /**
     * Function get end of battle.
     * This function indicates if a battle has finished or not.
     *
     * @return a boolean value accoding to the remaining time.
     */
    bool is_over();

    /**
     * Function notify collision.
     * Nothing to do.
     *
     * @param GameObject a pointer to a GameObject.
     */
    void notify_collision(const GameObject &object);

 private:
    /**
     * Function that returns remaining time.
     * This function returns a string representation of the remaining time
     * of a battle.
     *
     * @return is a string representing the remaining time.
     */
    string get_time_string();

    /**
     * Function that updates the time showed.
     * This function makes sprites variate and texts accoding to the remaining
     * time.
     *
     * @param delta a float variation to update the remaining time of a battle.
     */
    void update(float delta);

    /**
     * Function that renders a the time.
     * This function renders the text that represents the remaining
     * time of a battle.
     */
    void render();

    /**
     * Function get state dead.
     * This function returns the state dead.
     *
     * @return a boolean default value.
     */
    bool is_dead();
};

#endif  // INCLUDE_TIMECOUNTER_H_
