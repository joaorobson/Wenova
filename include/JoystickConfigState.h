/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file JoystickConfigState.h
 * This file contains the definitions of the methods and attributes of the class
 * JoystickConfigState.
 */
#ifndef INCLUDE_JOYSTICKCONFIGSTATE_H_
#define INCLUDE_JOYSTICKCONFIGSTATE_H_

#include "State.h"
#include "Sprite.h"
#include "Text.h"
#include "Timer.h"
#include "Sound.h"

class JoystickConfigState : public State {
 private:
    Sprite background;  /**< Background image of menu "Options". */
    Sprite joystick_help;  /**< Image joystick help of menu "Options". */
    Sprite back_btn;  /**< Image of button "B" to get out of the test mode. */
    Sprite test_btn;  /**< Image of button "A" to enter on test mode. */
    Sprite keyboard;  /**< Image keyboard help of menu "Options". */
    Text *back_txt;  /**< Text "BACK" to close joystick help image. */
    Text *test_txt;  /**< Text "TEST" to enter on test mode. */
    Text *press;  /**< Text "PRESS" on test mode. */
    Text *select_text;  /**< Text "SELECT" on test mode. */
    Text *and_text;  /**< Text "AND" on test mode. */
    Text *start_text;  /**< Text "START" on test mode. */
    Text *to_go_back;  /**< Text "TO GO BACK" on test mode. */
    Sound blocked;  /**< Cancel sound activated after cancel button pressed. */
    Sound selected;  /**< Select sound activated after select button pressed. */
    Sound changed;  /**< Change sound activated after cursor button pressed. */
    bool on_test;  /**< Indicates if the user has entered at mode test on */
                   /**< menu "Options" using joystick. */
    bool is_keyboard;  /**< Indicates if user is using a keyboard. */

 public:
   /**
    * Constructor.
    * This constructor builds sprites to render the option 'JOYSTICK' located on
    * the menu 'Options' of the game.
    *
    * @param joystick_id and integer argument that represents the id of one of
    * the four joysticks that can be pluged.
    * @param ckeyboard a boolean argument that indicates if a keyboard is
    * connected.
    */
    explicit JoystickConfigState(int joystick_id, bool ckeyboard = false);

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
     * Function that updates sprites on joystick test mode.
     * This function makes sprites change color accoding to the button pressed by
     * the user on the joystick test mode located at the menu
     * "Options->Joystick->Test".
     *
     * @param delta a float variation to update joystick state.
     */
    void update(float delta);

    /**
     * Function that renders keyboard or joystick help images.
     * This function renders keyboard or joystick help images if user select one of
     * the options: 'keyboard' and 'joystick'; located at the menu 'Options'.
     * Besides that, it will render buttons on the joystick test mode.
     */
    void render();
};

#endif  // INCLUDE_JOYSTICKCONFIGSTATE_H_
