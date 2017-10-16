/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file StageSelectState.h
 * This file contains the definitions of all methods and attributes of the class
 * StageSelectState.
 */
#ifndef INCLUDE_STAGESELECTSTATE_H_
#define INCLUDE_STAGESELECTSTATE_H_

#include "State.h"
#include "Sprite.h"
#include "Sound.h"
#include "InputManager.h"

#include <assert.h>

#define N_BACKGROUNDS 2
#define FRAME_TIME 7.5

class StageSelectState : public State {
 private:
    Sprite background[N_BACKGROUNDS];  /**< Vector of sprites with the images */
                                       /**< to render the background at the */
                                       /**< menu "SELECT STAGE" and "EDIT". */
    Sprite planet;  /**< Image with the 8 frames of the planet on the */
                    /**< background of the menu "SELECT STAGE" and "EDIT". */
    Sprite stage[3];  /**< Vector with images of the 3 stages available */
                      /**< at the menu "SELECT STAGE" and "EDIT". */
    Sound blocked;  /**< Cancel sound activated after cancel button pressed. */
    Sound selected;  /**< Select sound activated after select button pressed. */
    Sound changed;  /**< Change sound activated after cursor button pressed. */
    int stage_select = 0;  /**< Int number thar represents the selected stage */
                           /**< choosed by the user. */
    bool go_to_edit;  /**< Bool value that indicates if user is on edit mode */
                      /**< of a stage. */
    int amount_stages;  /**< Int number of the amount of stages that user can */
                   /**< select according if he's on edit mode or not. */

    enum Button {
          LEFT,  /**< enum value of the left button cursor. */
          RIGHT,  /**< enum value of the right button cursor. */
          A,  /**< enum value of the button "A". */
          B,  /**< enum value of the button "B". */
          START,  /**< enum value of the button "START". */
          SELECT  /**< enum value of the button "SELECT". */
         };
    bool pressed[5];  /**< Bool vector that represents the pressed button */
                      /**< according to the enum Button. */

    /**
     * Process an input of the user.
     * This function maps the buttons that are used on the menu that select a
     * stage according to constants of the InputManager class.
     */
    void process_input();

 public:
    /**
     * Constructor.
     * This constructor builds sprites to render the options of stages to start
     * a battle.
     *
     * @param cgo_to_edit a boolean argument that represents if user selected
     * edit mode on the menu.
     */
    explicit StageSelectState(bool cgo_to_edit = false);

    /**
     * Update function.
     * This function identifies the pressed button and updates the values of the
     * selected option.
     *
     * @param delta a float variation to update menu state.
     */
    void update(float delta);

    /**
     * Function that renders sprite.
     * This function renders the stages that can be selected by the user.
     */
    void render();

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
     * Update selected stage function.
     * This function increments the integer id value of the selected stage.
     *
     * @param increment an integer value that updates the current stage.
     */
    void update_stage_select(int increment);
};

#endif  // INCLUDE_STAGESELECTSTATE_H_
