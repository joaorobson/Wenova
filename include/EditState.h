/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file EditState.h
 * Brief Description.
 */

#ifndef INCLUDE_EDITSTATE_H_
#define INCLUDE_EDITSTATE_H_

#include "Fighter.h"
#include "Music.h"
#include "Sound.h"
#include "Sprite.h"
#include "State.h"
#include "Text.h"
#include "Timer.h"
#include "Vector.h"

#include <string>
#include <utility>
#include <vector>

using std::vector;
using std::pair;

class EditState : public State {
 private:
    vector<pair<Sprite, Vector> > backgrounds;
    Fighter* test_fighter;
    string stage;
    Music music;
    Sound sound;

    void read_level_design();
    void update_level_design();

 public:
    explicit EditState(string stage);

    void update(float delta);
    void render();

    void pause();
    void resume();
};

#endif  // INCLUDE_EDITSTATE_H_
