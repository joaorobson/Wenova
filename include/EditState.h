/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
#ifndef INCLUDE_EDITSTATE_H_
#define EDITSTATE_H

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
     EditState(string stage);

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
     vector<pair<Sprite, Vector> > backgrounds;
     Fighter * test_fighter;
     string stage;
     Music music;
     Sound sound;

     void read_level_design();
     void update_level_design();
};

#endif
