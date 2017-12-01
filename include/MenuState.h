/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
#ifndef INCLUDE_MENUSTATE_H_
#define INCLUDE_MENUSTATE_H_

#include "State.h"
#include "Sprite.h"
#include "Text.h"
#include "Timer.h"
#include "Sound.h"
#include "Music.h"

#include <assert.h>
#include <vector>

#define N_VALUE 15 /**< Relative to button pressed*/

class MenuState : public State {
 public:
     MenuState(bool main_menu = false);
     ~MenuState();
     /**
      *function backgroundSetUp
      *sets up the elements in the background on the menu
      */
     void backgroundSetUp();
     /**
      *function optionSelection
      *defines the style of the options the player has to chose from.
      */
     void optionSelection();
     /**
      *update function.
      *updates the objects on the menu screen of the game.
      */
     void update(float delta);
     /**
      *render function.
      *Renders the objects at the game menu screen.
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
     /**
      * process_input method.
      * this method recognizes the user input button and acts accordingly.
      */
     void process_input();

 private:
     Sprite background, green_ship, red_ship, title, planet; /**< Images of
     // the greenship, redship, title and planet.*/
     Text* start_option; /**< Start option logo.*/
     Sound blocked, selected, changed; /**< States of the sound configuration.*/
     Music music; /**< Music that plays in the menu.*/
     Timer text_timer; /**< Time that it takes to change text.*/
     vector<Text*> options; /**< Texts displayed in the menu.*/
     /**
      * Buttons the controller has for input.
      */
     enum Button { A, B, Y, LEFT, RIGHT, SELECT, START, LB, RT };

     bool pressed[N_VALUE], is_holding[N_VALUE]; /**< Button State.*/
     bool start_pressed, show_text; /**< Relative to start state and text.*/
     int current_option; /**< Current selected option by the player*/
};

#endif  //  INCLUDE_MENUSTATE_H_
