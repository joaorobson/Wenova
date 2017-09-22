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

#include "State.h"
#include "Text.h"
#include "Sprite.h"
#include "Sound.h"

// maybe
// #include "Timer.h"

#include <utility>
#include <map>
#include <string>
#include <vector>

using std::pair;
using std::map;

class OptionsState : public State {
 private:
    Sprite background;
    Text *title;
    Sound blocked, selected, changed;
    int current_option;
    bool on_submenu;
    map<string, vector<Text *> > sub_options;
    vector<Text *> options;
    vector<int> current_sub_option;

    /**
     * Get the option on a sub menu.
     * This function identifies which sub menu and option the user selected.
     *
     * @param option an integer argument that represents the selected option of the
     * main menu.
     *
     * @return an integer value that represents the current sub option of a sub
     * menu.
     */
     int get_current_sub_option(int option);

    enum Button { A, B, UP, DOWN, SELECT, START };
    bool pressed[15];

 public:
   /**
    * Constructor.
    * This constructor builds the options and sub options to initialize the
    * attributes.
    */
    OptionsState();

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
     * This function renders all text of the menu 'Options' and changes its color
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
     * Pause function.
     * Nothing to do.
     */
    void pause();
    /**
     * Resume function.
     * Nothing to do.
     */
    void resume();

    /**
     * Process an input of the user.
     * This function maps the buttons that are used on the menu 'Option' according
     * to constants of the InputManager class.
     */
    void process_input();
};

#endif  // INCLUDE_OPTIONSSTATE_H_
