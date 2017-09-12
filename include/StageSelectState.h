/*
 *Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 *This work is licensed under the terms of the MIT license.
 *For a copy, see <https://opensource.org/licenses/MIT>.
 *
 *Definitions of attributes and methods.
 *
 *This file contains the definitions of all methods and attributes of the class
 *StageSelectState.
 */
#ifndef INCLUDE_STAGESELECTSTATE_H_
#define INCLUDE_STAGESELECTSTATE_H_

#include "State.h"
#include "Sprite.h"
#include "Sound.h"
#include "InputManager.h"

#define N_BACKGROUNDS 2
#define FRAME_TIME 7.5

class StageSelectState : public State {
 private:
    Sprite background[N_BACKGROUNDS], planet, stage[3];
    Sound blocked, selected, changed;
    int stage_select = 0;
    bool go_to_edit;
    int n_stages;

    enum Button { LEFT, RIGHT, A, B, START, SELECT };
    bool pressed[5];

    /** Process an input of the user.
     * This function maps the buttons that are used on the menu that select a
     * stage according to constants of the InputManager class.
     */
    void process_input();

 public:
    /** Constructor.
     * This constructor builds sprites to render the options of stages to start
     * a battle.
     *
     * @param cgo_to_edit a boolean argument that represents if user selected
     * edit mode on the menu.
     */
    explict StageSelectState(bool cgo_to_edit = false);

    /** Update function.
     * This function identifies the pressed button and updates the values of the
     * selected option.
     *
     * @param delta a float variation to update menu state.
     */
    void update(float delta);

    /** Function that renders sprite.
     * This function renders the stages that can be selected by the user.
     */
    void render();

    /** Pause function.
     * Nothing to do.
     */
    void pause();

    /** Resume function.
     * Nothing to do.
     */
    void resume();

    /** Update selected stage function.
     * This function increments the integer id value of the selected stage.
     *
     * @param increment an integer value that updates the current stage.
     */
    void update_stage_select(int increment);
};

#endif  // INCLUDE_STAGESELECTSTATE_H_
