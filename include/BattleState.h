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
#include <assert.h>

#define N_PLAYERS 4
#define N_VALUE1 5

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
		  vector<pair<Sprite, Vector> > backgrounds;
		  Fighter* players[N_PLAYERS];
		  Music music;
		  Sound sound;
		  TimeCounter *time_counter;
		  BattleEnd *battleEnd;
			/**
			 *read_level_design function.
			 *this function receives a name that indicates the selected level.
			 */
			void read_level_design(string stage);
		  bool game_over;
		  int alive[N_VALUE1];
};

#endif
