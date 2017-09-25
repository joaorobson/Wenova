/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */

/**
 * @file BattleState.h
 * This file contains the definition of the BattleState.h class methods.
 */
#ifndef BATTLESTATE_H
#define BATTLESTATE_H

#include "State.h"
#include "Sprite.h"
#include "Text.h"
#include "Timer.h"
#include "Music.h"
#include "Sound.h"
#include "Fighter.h"
#include "Vector.h"
#include "TimeCounter.h"
#include "BattleEnd.h"

#include <vector>
#include <utility>

#define N_PLAYERS 4

using std::vector;
using std::pair;

class BattleState : public State {
private:
    vector<pair<Sprite, Vector> >backgrounds;
    Fighter *players[N_PLAYERS];
    Music music;
    Sound sound;
    void read_level_design(string stage);
    bool game_over;
    int alive[5];
    TimeCounter *time_counter;
    BattleEnd *battleEnd;

public:
    /**
     * The constructor.
     * Initialize the battle stage and the character locations.
     *
     * @param stage is the name of the stage.
     * @param vector is a vector of strings.
     * @param players_info a description.
     */
    BattleState(string stage,
                vector<pair<string, string> >players_info);

    /**
     * A Destructor.
     * Destructs a previously initialized object of this class.
     */
    ~BattleState();

    /**
     * update method.
     * Checks the current state of a started game.
     * This method checks the current state of the game and updates it.
     *
     * @param delta is a number of the type float used to update the background.
     */
    void update(float delta);

    /**
     * render method.
     * renders the background given a x and y positions.
     */
    void render();

    /**
     * pause method.
     * Not implemented.
     */
    void pause();

    /**
     * resume method.
     * Not implemented.
     */
    void resume();
};

#endif // ifndef BATTLESTATE_H
