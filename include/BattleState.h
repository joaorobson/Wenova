/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
#ifndef INCLUDE_BATTLESTATE_H_
#define INCLUDE_BATTLESTATE_H_

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

#include <assert.h>
#include <vector>
#include <utility>
#include <string>

#define NUMBER_PLAYERS 4 /**< Represents the number of players*/
#define NUMBER_VALUE 5 /**< Relative to the players*/

using std::vector;
using std::pair;

class BattleState : public State{
 public:
     BattleState(string stage, vector< pair<string, string> > players_info);
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
      *Render Function.
      *This function renders the  background.
      */
     void render();
     /**
      *Pause function.
      *Nothing to do.
      */
     void pause();
     /**
      *Resume Function.
      *Nothing to do.
      */
     void resume();

 private:
     vector<pair<Sprite, Vector> > backgrounds; /**< Images of the background.*/
     Fighter* players[NUMBER_PLAYERS]; /**< Number of players.*/
     Music music; /**< Music that plays in the stage.*/
     Sound sound; /**< Checks if sound is on.*/
     TimeCounter *time_counter; /**< Remaining time of the battle.*/
     BattleEnd *battleEnd; /**< Refers to the end of the battle.*/
     /**
      *read_level_design function.
      *this function receives a name that indicates the selected level.
      */
     void read_level_design(string stage);
     bool game_over; /**< Relative to the state of the game, if over or not.*/
     int alive[NUMBER_VALUE]; /**< Relative to the players.*/
};

#endif  //  INCLUDE_BATTLESTATE_H_
