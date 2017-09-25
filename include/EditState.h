/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */

/**
 * @file EditState.h
 * This file contains the definition of the EditState.h class methods.
 */
#ifndef EDITSTATE_H
#define EDITSTATE_H

#include "State.h"
#include "Sprite.h"
#include "Text.h"
#include "Timer.h"
#include "Music.h"
#include "Sound.h"
#include "Fighter.h"
#include "Vector.h"

#include <vector>
#include <utility>

using std::vector;
using std::pair;

class EditState : public State {
 private:
    vector<pair<Sprite, Vector> >backgrounds;
    Fighter *test_fighter;
    string stage;
    Music music;
    Sound sound;

    void read_level_design();
    void update_level_design();

 public:
    /**
     * The constructor.
     * Initialize the EditState object.
     *
     * @param cstage is a name.
     */
    EditState(string stage);

    /**
     * update method.
     * Edits some level design characteristics.
     * This method allows resetting the position of the fighter, creating floors
     * or stages and saving them.
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

#endif  // ifndef EDITSTATE_H
