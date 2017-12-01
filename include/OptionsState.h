/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file OptionsState.h
 * This file contains the definitions of all methods and attributes of the class
 * OptionsState.
 */
#ifndef INCLUDE_OPTIONSSTATE_H_
#define INCLUDE_OPTIONSSTATE_H_

#include "Sound.h"
#include "Sprite.h"
#include "State.h"
#include "Text.h"

// maybe
// #include "Timer.h"

#include <assert.h>
#include <map>
#include <string>
#include <utility>
#include <vector>

using std::pair;
using std::map;

class OptionsState : public State {
 private:
    Sprite background; /**< Background image of menu "Options". */
    Text *title;       /**< Text title of menu "Options". */
    Sound blocked;  /**< Cancel sound activated after cancel button pressed. */
    Sound selected; /**< Select sound activated after select button pressed. */
    Sound changed;  /**< Change sound activated after cursor button pressed. */
    map<string, vector<Text *> > sub_options; /**< Map of sub options of the */
                                              /**< menu "Options". */
    vector<Text *> options; /**< Text of all options of the menu "Options". */
    vector<int> current_sub_option; /**< Vector with current options */
                                    /**< of submenu. */
    enum Button { A, B, UP, DOWN, SELECT, START };
    bool pressed[15];
    int current_option; /**< Number of current option of main Menu. */
    bool on_submenu; /**< Indicates if user is on submenu of menu "Options". */

 public:
    /**
     * Constructor.
     * This constructor builds the options and sub options to initialize the
     * attributes.
     */
    OptionsState();

    /**
     * Pause function.
     * Nothing to do.
     */
    void pause();
    /**
     * Resume function.
     * Nothing to do.
     */
    void resume();

 private:
    /**
     * Update function.
     * This function identifies the pressed button and updates the values of the
     * selected option.
     *
     * @param delta a float variation to update menu state.
     */
    void update(float delta);

    /**
     * Render function.
     * This function renders all text of the menu 'Options' and changes its
     * color
     * according to the menu tha user selected.
     */
    void render();

    /**
     * Build options function.
     * This function builds the text of all options and sub options of the menu
     * 'Options' and update the attributes that represent these options.
     */
    void build_options();

    /**
     * Process an input of the user.
     * This function maps the buttons that are used on the menu 'Option'
     * according
     * to constants of the InputManager class.
     */
    void process_input();
};

#endif  // INCLUDE_OPTIONSSTATE_H_
