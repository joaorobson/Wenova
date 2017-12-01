/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
#ifndef INCLUDE_EDITSTATE_H_
#define INCLUDE_EDITSTATE_H_

#include "State.h"
#include "Sprite.h"
#include "Text.h"
#include "Timer.h"
#include "Music.h"
#include "Sound.h"
#include "Fighter.h"
#include "Vector.h"

#include <assert.h>
#include <vector>
#include <utility>
#include <string>

using std::vector;
using std::pair;

class EditState : public State{
 public:
     EditState(string stage); /**< Updates the selected stage.*/
     /**
      *update function
      *updates the framerate given a delta argument.
      */
     void update(float delta);
     /**
      * Renders the first background of the list.
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
     Fighter * test_fighter; /**< Checks if the fighter is available.*/
     string stage; /**< Name of the stages.*/
     Music music; /**< Music that plays in the stage.*/
     Sound sound; /**< Checks if sound is on.*/

     /**
      *read_level_design function.
      *checks if the current level is loaded correctly.
      */
     void read_level_design();
     /**
      *update_level_design function.
      *updates the elements of the level being played.
      */
     void update_level_design();
};

#endif  //  INCLUDE_EDITSTATE_H_
