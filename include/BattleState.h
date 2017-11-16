/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file BattleState.h
 * Brief Description.
 */

#ifndef INCLUDE_BATTLESTATE_H_
#define INCLUDE_BATTLESTATE_H_

#include "BattleEnd.h"
#include "Fighter.h"
#include "Music.h"
#include "Sound.h"
#include "Sprite.h"
#include "State.h"
#include "Text.h"
#include "TimeCounter.h"
#include "Timer.h"
#include "Vector.h"

#include <string>
#include <utility>
#include <vector>

#define N_PLAYERS 4

using std::vector;
using std::pair;

class BattleState : public State {
 private:
    vector<pair<Sprite, Vector> > backgrounds;
    Fighter *players[N_PLAYERS];
    Music music;
    Sound sound;
    void read_level_design(string stage);
    bool game_over;
    int alive[5];
    TimeCounter *time_counter;
    BattleEnd *battleEnd;

 public:
    BattleState(string stage, vector<pair<string, string> > players_info);
    ~BattleState();

    void update(float delta);
    void render();

    void pause();
    void resume();
};

#endif  // INCLUDE_BATTLESTATE_H_
