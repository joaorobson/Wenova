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
    Sprite background,  /**< Sprite of the background. */
           green_ship,  /**< Sprite of the green ship. */
           red_ship,  /**<  Sprite of the red ship. */
           title,  /**< Sprite of the title. */
           planet;  /**< Sprite of the planet. */
    Text *start_option;  /**< Pointer to the start option. */
    Sound blocked,  /**< Sounds is blocked. */
          selected,  /**< Sound is selected. */
          changed;  /**< Soud is changed. */
    Music music;  /**<  Sound effect to be played. */
    Timer text_timer;  /**< Text of the time that is displayed. */
    int current_option;  /**< Current selected option by its integer. */
    bool start_pressed,  /**< Bool value that indicates if the start was */
                        /**< pressed. */
         show_text;  /**< Bool value that indicates whether to show text or */
                      /**< not. */
    vector<Text *>options;  /**<Vector of text options. */

    enum Button { A,  /**< enum value of the A button. */
                  B,  /**< enum value of the B button. */
                  Y,  /**< enum value of the Y button. */
                  LEFT,  /**< enum value of the LEFT button cursor. */
                  RIGHT,  /**< enum value of the RIGHT button cursor. */
                  SELECT,  /**< enum value of the SELECT button. */
                  START,  /**< enum value of the START button. */
                  LB,  /**< enum value of the LB button. */
                  RT   /**<enum value of the RT button. */
                };
    bool pressed[15],  /**< Bool that indicates if a button is pressed. */
         is_holding[15];  /**< Bool that indicates if the button is held */
                           /**< pressed. */

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
