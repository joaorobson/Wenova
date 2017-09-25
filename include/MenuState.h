/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */

/**
 * @file MenuState.h
 * This file contains the definition of the MenuState.h class methods.
 */
#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "State.h"
#include "Sprite.h"
#include "Text.h"
#include "Timer.h"
#include "Sound.h"
#include "Music.h"

class MenuState : public State {
 private:
    Sprite background, green_ship, red_ship, title, planet;
    Text *start_option;
    Sound blocked, selected, changed;
    Music music;
    Timer text_timer;
    int current_option;
    bool start_pressed, show_text;
    vector<Text *>options;

    enum Button { A, B, Y, LEFT, RIGHT, SELECT, START, LB, RT };
    bool pressed[15], is_holding[15];

 public:
    /**
     * The constructor.
     * Initialize the game menu.
     *
     * @param main_menu is a boolean type that send true or false to the method.
     */
    MenuState(bool main_menu = false);

    /**
     * update method.
     * this method changes the state of the menu.
     * changes the state as the user navigates through the menu.
     *
     * @param cid is a number of the type integer.
     */
    void update(float delta);

    /**
     * render method.
     * this method renders the menu of the game on the screen.
     */
    void render();

    /**
     * pause method.
     * not implemented.
     */
    void pause();

    /**
     * resume method.
     * not implemented.
     */
    void resume();

    /**
     * process_input method.
     * this method recognizes the user input button and acts accordingly.
     */
    void process_input();
};

#endif  // ifndef MENU_STATE_H
