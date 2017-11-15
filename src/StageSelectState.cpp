/* Copyright (c) 2017 Wenova - Rise of Conquerors. All rights reserved.
 *
 * This work is licensed under the terms of the MIT license.
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */
/**
 * @file StageSelectState.cpp
 * This file builds and renders the stages that the user can select.
 */
#include "StageSelectState.h"

#include <string>
#include "CharacterSelectState.h"
#include "EditState.h"
#include "Game.h"
#include "MenuState.h"

#include <cstdlib>

using std::to_string;

/**
 * Constructor.
 * This constructor builds sprites to render the options of stages to start
 * a battle.
 *
 * @param cgo_to_edit a boolean argument that represents if user selected
 * edit mode on the menu.
 */
StageSelectState::StageSelectState(bool cgo_to_edit)
        : planet(Sprite("stage_select/planet.png", 8, FRAME_TIME))
        , blocked(Sound("menu/sound/cancel.ogg"))
        , selected(Sound("menu/sound/select.ogg"))
        , changed(Sound("menu/sound/cursor.ogg")) {
    go_to_edit = cgo_to_edit;
    amount_stages = 2 + (go_to_edit ? 0 : 1);
    planet.set_scale(1.5);

    for (int i = 0; i < N_BACKGROUNDS; i++) {
        background[i] =
            Sprite("stage_select/background_" + to_string(i) + ".png");
    }

    for (int i = 0; i < amount_stages; i++) {
        stage[i] = Sprite("stage_select/stage_" + to_string(i + 1) + ".png");
    }

    memset(&pressed, 0, sizeof(pressed));

    InputManager::get_instance()->map_keyboard_to_joystick(
        InputManager::MENU_MODE);
}

/**
 * Update function.
 * This function identifies the pressed button and updates the values of the
 * selected option.
 *
 * @param delta a float variation to update menu state.
 */
void StageSelectState::update(float delta) {
    process_input();

    InputManager *input_manager = InputManager::get_instance();

    if (input_manager->quit_requested()) {
        m_quit_requested = true;
        return;
    }

    if (pressed[B] or pressed[SELECT]) {
        selected.play();
        m_quit_requested = true;
        Game::get_instance().push(new MenuState(true));
        return;
    }

    if (pressed[LEFT]) {
        update_stage_select(-1);
    }

    if (pressed[RIGHT]) {
        update_stage_select(1);
    }

    if (pressed[A] or pressed[START]) {
        selected.play();
        m_quit_requested = true;

        if (stage_select == 2) {
            srand(clock());
            unsigned int thread = 0;
            stage_select =
                rand_r(&thread) % (amount_stages - (go_to_edit ? 0 : 1));
        }

        if (go_to_edit) {
            Game::get_instance().push(
                new EditState(to_string(stage_select + 1)));
        } else {
            Game::get_instance().push(
                new CharacterSelectState(to_string(stage_select + 1)));
        }
    }

    planet.update(delta);
}

/**
 * Function that renders sprite.
 * This function renders the stages that can be selected by the user.
 */
void StageSelectState::render() {
    background[0].render();
    planet.render(640 - planet.get_width() / 2, 360 - planet.get_height() / 2);
    background[1].render();

    for (int i = 0; i < amount_stages; i++) {
        stage[i].render(i * 780 - stage_select * 780);
    }
}

/**
 * Update selected stage function.
 * This function increments the integer id value of the selected stage.
 *
 * @param increment an integer value that updates the current stage.
 */
void StageSelectState::update_stage_select(int increment) {
    stage_select += increment;

    if (stage_select < 0) {
        blocked.play();
        stage_select = 0;
    } else if (stage_select > amount_stages - 1) {
        blocked.play();
        stage_select = amount_stages - 1;
    } else {
        selected.play();
    }
}

/**
 * Process an input of the user.
 * This function maps the buttons that are used on the menu that select a stage
 * according to constants of the InputManager class.
 */
void StageSelectState::process_input() {
    InputManager *input_manager = InputManager::get_instance();

    // MENU BUTTONS HERE
    vector<pair<int, int> > joystick_buttons = {
        ii(LEFT, InputManager::LEFT),   ii(RIGHT, InputManager::RIGHT),
        ii(A, InputManager::A),         ii(B, InputManager::B),
        ii(START, InputManager::START), ii(SELECT, InputManager::SELECT)};

    for (ii button : joystick_buttons) {
        pressed[button.first] =
            input_manager->joystick_button_press(button.second, 0);
    }
}

/**
 * Pause function.
 * Nothing to do.
 */
void StageSelectState::pause() {
}

/**
 * Resume function.
 * Nothing to do.
 */
void StageSelectState::resume() {
}